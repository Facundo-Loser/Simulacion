/*
	EOSimulator 1.1.1 - Event Oriented Simulator
	Copyright (C) 2006  Sebastián Alaggia, Bruno Martínez, Antonio Mauttone, Fernando Pardo, María Urquhart

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

//#include <eosim/graphic/Display.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <agg_rendering_buffer.h>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_renderer_scanline.h>
#include <agg_rounded_rect.h>
#include <agg_conv_transform.h>
#include <agg_span_image_filter_rgba.h>
#include <agg_scanline_u.h>
#include <agg_span_interpolator_linear.h>
#include <agg_pixfmt_rgba.h>
#include <agg_conv_contour.h>
#include <agg_font_freetype.h>
#include <map>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/intrusive_ptr.hpp>
#include <map>
using namespace std;
using namespace boost;

typedef agg::pixfmt_rgba32 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_rgba component_order;
typedef agg::renderer_base<pixfmt> base_renderer;
typedef agg::renderer_scanline_aa_solid<base_renderer> solid_renderer;
typedef agg::rasterizer_scanline_aa<> scanline_rasterizer;
typedef agg::renderer_scanline_bin_solid<base_renderer> renderer_bin;
typedef agg::span_allocator<color_type> span_alloc_type;
typedef agg::span_interpolator_linear<> interpolator_type;
typedef agg::span_image_filter_rgba_bilinear<color_type, component_order, interpolator_type> span_gen_type;
typedef agg::renderer_scanline_aa<base_renderer, span_gen_type> renderer_type;
typedef agg::font_engine_freetype_int32 font_engine_type;
typedef agg::font_cache_manager<font_engine_type> font_manager_type;

void intrusive_ptr_add_ref(SDL_Surface* p)
{
    p->refcount++;
}

void intrusive_ptr_release(SDL_Surface* p)
{
    SDL_FreeSurface(p);
}

namespace eosim {

namespace graphic {

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    const unsigned int rmask = 0xFF;
    const unsigned int gmask = 0xFF00;
    const unsigned int bmask = 0xFF0000;
    const unsigned int amask = 0xFF000000;
#else //SDL_BIG_ENDIAN
    const unsigned int rmask = 0xFF000000;
    const unsigned int gmask = 0xFF0000;
    const unsigned int bmask = 0xFF00;
    const unsigned int amask = 0xFF;
#endif

    struct Display::impl : boost::noncopyable {
        int width;
        int height;
        double simperclock;
        list<Sprite::impl*> sprites;
        list<TextSprite::impl*> textSprites;
        typedef list<Sprite::impl*>::iterator it_sprites;
        typedef list<TextSprite::impl*>::iterator it_tsprites;

        SDL_Surface* screen;
        intrusive_ptr<SDL_Surface> window;
        intrusive_ptr<SDL_Surface> fondo;
        agg::rendering_buffer rbwindow;
        map<string, intrusive_ptr<SDL_Surface> > surfaceCache;

        font_engine_type             m_feng;
        font_manager_type            m_fman;
        agg::conv_curve<font_manager_type::path_adaptor_type> m_curves;
        agg::conv_contour<agg::conv_curve<font_manager_type::path_adaptor_type> > m_contour;

        impl(int width, int height)
            : width(width), height(height)
            , simperclock(0.01)
            , m_fman(m_feng), m_curves(m_fman.path_adaptor()), m_contour(m_curves)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
                throw std::runtime_error(SDL_GetError());
            screen = SDL_SetVideoMode(width, height, 0, SDL_ANYFORMAT|SDL_HWSURFACE);
            if(!screen) {
                SDL_Quit();
                throw runtime_error(string("Unable to set screen: ") + SDL_GetError());
            }
            window = intrusive_ptr<SDL_Surface>(
                SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h,
                screen->format->BitsPerPixel,
                rmask, gmask, bmask, amask)
                , false);
            if (!window)
                SDL_Quit();
                runtime_error (string("Unable to set window: ") + SDL_GetError());

            rbwindow.attach((unsigned char*)window->pixels, window->w
                , window->h, window->pitch);
            SDL_WM_SetCaption("EOSimulator", 0);
        }

        ~impl() {
            SDL_Quit();
        }

        intrusive_ptr<SDL_Surface> load(char const* file)
        {
            intrusive_ptr<SDL_Surface>& sfc = surfaceCache[file];
            if (!sfc) {
                //std::cout << "loadFromDisk" << ' ' << file << '\n';
                SDL_Surface* tmp_surf = IMG_Load(file);
                if (!tmp_surf) throw runtime_error(string("Couldn't load ") + file + ": " + SDL_GetError());
                SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, tmp_surf->w, tmp_surf->h, 32, rmask, gmask, bmask, amask);
                if(!surface) {
                    SDL_FreeSurface(tmp_surf);
                    throw runtime_error(string("Couldn't convert ") + file + ": " + SDL_GetError());
                }
                SDL_BlitSurface(tmp_surf, 0, surface, 0);
                SDL_FreeSurface(tmp_surf);
                sfc = intrusive_ptr<SDL_Surface>(surface, false);
            }
            return sfc;
        }

        void draw();
    };

    struct Sprite::impl : boost::noncopyable {
        shared_ptr<Display::impl> dis;
        Display::impl::it_sprites mi_it;
        double x, y;
        MoveAction futuro;
        bool visible;

        intrusive_ptr<SDL_Surface> surface;

        impl(shared_ptr<Display::impl> dis, const char* file, double x, double y)
            : dis(dis)
            , x(x), y(y)
            , visible(1)
            , surface(dis->load(file))
        {
            mi_it = dis->sprites.insert(dis->sprites.end(), this);
        }

        ~impl() {
            dis->sprites.erase(mi_it);
        }

        void move(double offsetTime) {
            deque<MoveAction::waypoint>& wps = futuro.waypoints;
            double now = 0;
            while (!wps.empty()) {
                if (now + wps.front().time <= offsetTime) {
                    x = wps.front().x;
                    y = wps.front().y;
                    now += wps.front().time;
                    wps.pop_front();
                } else {
                    x += (wps.front().x - x) * (offsetTime - now) / (wps.front().time);
                    y += (wps.front().y - y) * (offsetTime - now) / (wps.front().time);
                    wps.front().time -= offsetTime - now;
                    break;
                }
            }
        }
    };

    struct TextSprite::impl : boost::noncopyable {
        shared_ptr<Display::impl> dis;
        Display::impl::it_tsprites mi_it;
        double x, y;
        MoveAction futuro;
        bool visible;
        std::string caption;
        double size;

        impl(shared_ptr<Display::impl> dis, const char* text, double size, double x, double y)
            : dis(dis)
            , x(x), y(y)
            , visible(1)
            , caption(text)
            , size(size)
        {
            mi_it = dis->textSprites.insert(dis->textSprites.end(), this);
        }

        ~impl() {
            dis->textSprites.erase(mi_it);
        }

        void move(double offsetTime) {
            deque<MoveAction::waypoint>& wps = futuro.waypoints;
            double now = 0;
            while (!wps.empty()) {
                if (now + wps.front().time <= offsetTime) {
                    x = wps.front().x;
                    y = wps.front().y;
                    now += wps.front().time;
                    wps.pop_front();
                } else {
                    x += (wps.front().x - x) * (offsetTime - now) / (wps.front().time);
                    y += (wps.front().y - y) * (offsetTime - now) / (wps.front().time);
                    wps.front().time -= offsetTime - now;
                    break;
                }
            }
        }
    };

    MoveAction move(double x, double y, double time) {
        return MoveAction().move(x, y, time);
    }

    Display::Display(int width, int height)
        : p_impl(new impl(width, height))
    {}

    Display::~Display()
    {}

    void Display::setTitle(const char* title){
        string tit(title);
        SDL_WM_SetCaption(("EOSimulator - " + tit).c_str(), 0);
    }

    void Display::setBackground(const char* file) {
        p_impl->fondo = p_impl->load(file);
		SDL_BlitSurface(p_impl->fondo.get(), 0, p_impl->screen, 0);
    }

    void Display::setSpeed(double sp) {
        p_impl->simperclock = sp;
    }

    double Display::getSpeed() const {
        return p_impl->simperclock;
    }

    int Display::width() const {
        return p_impl->width;
    }

    int Display::height() const {
        return p_impl->height;
    }
    void Display::advance(double simEnd) {
        double simNow = 0;
        double clockNow = SDL_GetTicks();
        while (simNow < simEnd) {
            p_impl->draw();
            double clockDelta = clockNow;
            clockNow = SDL_GetTicks();
            clockDelta = clockNow - clockDelta;
            double simDelta = clockDelta * p_impl->simperclock;
            if (simDelta > simEnd - simNow) {
                simDelta = simEnd - simNow;
                simNow = simEnd;
            } else {
                simNow += simDelta;
            }
            for (impl::it_sprites it = p_impl->sprites.begin()
                ,end = p_impl->sprites.end()
                ;it!= end
                ;++it)
            {
                (*it)->move(simDelta);
            }
            for (impl::it_tsprites it = p_impl->textSprites.begin()
                ,end = p_impl->textSprites.end()
                ;it!= end
                ;++it)
            {
                (*it)->move(simDelta);
            }

        }
    }

    Sprite::Sprite() {
    }

    Sprite::Sprite(Display& dis, const char* file, double x, double y)
        : p_impl(new Sprite::impl(dis.p_impl, file, x, y))
    {}

    void Sprite::setImage(const char* file) {
        p_impl->surface = p_impl->dis->load(file);
    }

    void Sprite::setMoves(MoveAction m) {
        p_impl->futuro = m;
    }

    void Sprite::setVisible(bool v) {
        p_impl->visible = v;
    }

    bool Sprite::getVisible() const {
        return p_impl->visible;
    }

    TextSprite::TextSprite() {
    }

    TextSprite::TextSprite(Display& dis, const char* text, double size, double x, double y)
        : p_impl(new TextSprite::impl(dis.p_impl, text, size, x, y))
    {}

    void TextSprite::setText(const char* text) {
        p_impl->caption = text;
    }

    void TextSprite::setMoves(MoveAction m) {
        p_impl->futuro = m;
    }

    void TextSprite::setVisible(bool v) {
        p_impl->visible = v;
    }

    bool TextSprite::getVisible() const {
        return p_impl->visible;
    }

    void Display::impl::draw()
    {
        SDL_PumpEvents();

        pixfmt            pixf(rbwindow);
        pixfmt            pixf_pre(rbwindow);
        base_renderer     rb(pixf);
        base_renderer     rb_pre(pixf_pre);
        solid_renderer    rs(rb);
        renderer_bin      rbin(rb);
        agg::scanline_u8 sl;
        agg::rasterizer_scanline_aa<> pf;

        if (fondo)
            SDL_BlitSurface(fondo.get(), 0, window.get(), 0);
        else
            rb.clear(agg::rgba(0, 0, 0));

        agg::glyph_rendering gren = agg::glyph_ren_agg_gray8;

        if(m_feng.load_font("timesi.ttf", 0, gren)) {
            m_feng.hinting(1);
            m_feng.flip_y(1);
            for (impl::it_tsprites it = textSprites.begin()
                ,end = textSprites.end()
                ;it!= end
                ;++it)
            {
                TextSprite::impl* tsimpl = *it;
                if (tsimpl->visible) {
                    m_feng.height(tsimpl->size);
                    m_feng.width(tsimpl->size);
                    m_contour.width(-tsimpl->size * tsimpl->size * 0.05);
                    double x  = tsimpl->x;
                    double y0 = tsimpl->y + tsimpl->size;
                    double y  = y0;
                    for (std::string::iterator letra = tsimpl->caption.begin(), last = tsimpl->caption.end(); letra != last; ++letra) {
                        const agg::glyph_cache* glyph = m_fman.glyph(*letra);
                        if (glyph) {
                            m_fman.init_embedded_adaptors(glyph, x, y);
                            rs.color(agg::rgba8(0, 0, 0));
                            agg::render_scanlines(m_fman.gray8_adaptor(),
                                m_fman.gray8_scanline(),
                                rs);
                            x += glyph->advance_x;
                            y += glyph->advance_y;
                        }
                    }
                }
            }
        }

        for (impl::it_sprites it = sprites.begin()
            ,end = sprites.end()
            ;it!= end
            ;++it)
        {
            Sprite::impl* simpl = *it;
            if (simpl->visible)
            {
                agg::rendering_buffer buffer((unsigned char*)simpl->surface->pixels,
                    simpl->surface->w, simpl->surface->h, simpl->surface->pitch);
                interpolator_type interpolator;
                span_alloc_type sa;
                span_gen_type sg(sa, buffer, agg::rgba_pre(0, 0, 0, 0), interpolator);
                renderer_type ri;
                agg::rounded_rect rec(0, 0, buffer.width(), buffer.height(), 0);

                agg::trans_affine src_mtx;
                src_mtx *= agg::trans_affine_translation(simpl->x, simpl->y);
                agg::trans_affine img_mtx = src_mtx;
                img_mtx.invert();
                interpolator.transformer(img_mtx);
                ri.attach(rb_pre, sg);
                agg::rounded_rect rrect(0, 0, buffer.width(), buffer.height(), 0);
                agg::conv_transform<agg::rounded_rect> tr(rrect, src_mtx);
                pf.add_path(tr);
                agg::render_scanlines(pf, sl, ri);

            }
        }
        SDL_BlitSurface(window.get(), 0, screen, 0);
        SDL_Flip(screen);
    }
}

};
