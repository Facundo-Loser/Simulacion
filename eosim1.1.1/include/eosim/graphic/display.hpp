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

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>

/** \ingroup graphic_group
 * \@{
*/
/** \fn eosim::graphic::MoveAction eosim::graphic::move(double x, double y, double time)
 * \author Bruno Martínez, Fernando Pardo and Sebastián Alaggia
 * \version 1.1.1
 * \date    2005
 * \brief  Creates a move action which will move an object from its actual position to (x,y) in a number of time units.
*/
namespace eosim {

namespace graphic {

    struct MoveAction;


	MoveAction move(double x, double y, double time);

}

}

/**
 * \@}
*/

/** \ingroup graphic_group
 * \@{
*/
/** \class eosim::graphic::Display \include\eosim\graphic\Display.hpp  <eosim/graphic/Display.hpp>
 * \author Bruno Martínez, Fernando Pardo and Sebastián Alaggia
 * \version 1.1.1
 * \date    2005
 * \brief  Display window
 * <p>This class brings a graphical environment to the programmer so he can develop a 2D graphical simulation. To use it
 * an instance of Display must be created as a Model's attribute. Only one instance of Display can be created per run. The
 * window created will be opened while the instance persists.</p> 
 * <p>To synchronize the display with the simulation Display::advance is implemented. We have to invoke this operation every
 * time the simulation advance the time, which is the responsibility of RefreshGraphic Event.</p>
 * <p>During the run many objects and messages should appear in order to see how the simulation is running, for that there
 * are Sprite y TextSprite (for graphics and text). These elements are linked to a display (in the constructor), and  they
 * will appear in the display until there are no references to them, excepting those from the display.</p>
*/
namespace eosim {

namespace graphic {

	class Display : boost::noncopyable {
    public:
        struct impl;
		/**
		* \brief The constructor creates a Display with a window with the specified size.
		*/
        Display(int width, int height);
		/**
		* \brief The destructor of Display.
		*/
        ~Display();
		/**
		* \brief This operation sets the title of the window where the simulation is displayed.
		*/
        void setTitle(const char* title);
		/**
		* \brief This operation sets the background image in the simulation.
		* The supported file formats are BMP, PNM, XPM, XCF, PCX, GIF, JPG, TIF, PNG y LBM. Otherwise the background is
		* black.
		*/
        void setBackground(const char* file);
		/**
		* \brief This operation changes the rate between real time and simulation time. Real time is measure in miliseconds.
		*/
        void setSpeed(double sp);
		/**
		* \brief This operation returns the rate between real time and simulation time.
		*/
        double getSpeed() const;
		/**
		* \brief This operation returns the width of the window where the simulation is displayed.
		*/
        int width() const;
		/**
		* \brief This operation returns the height of the window where the simulation is displayed.
		*/
        int height() const;
		/**
		* \brief This operation advance simulation the simulation time in the graphical simulation. 
		* <p>This operation advances the simulation time in offsetTime time unit. It must be called on each time beat, so
		* that the moves of the sprites is synchronized with the simulation time.</p>
		*/
        void advance(double offsetTime);
    private:
        boost::shared_ptr<impl> p_impl;
        friend class Sprite;
        friend class TextSprite;
    };

}

}

/**
 * \@}
*/

/** \ingroup graphic_group
 * \@{
*/
/** \class eosim::graphic::Sprite \include\eosim\graphic\Display.hpp <eosim/graphic/Display.hpp>
 * \author Bruno Martínez, Fernando Pardo and Sebastián Alaggia
 * \version 1.1.1
 * \date    2005
 * \brief  Image Sprite
 * <p>Both Sprite and TextSprite represents objects or text which can be added to the Display (see \ref Sprite::Sprite 
 * "constructor", moved arround the window (see Sprite::setMoves), change shape or message (see Sprite::setImage and 
 * TextSprite::setText), and be removed from the window. The persistency of a Sprite (or TextSprite) is due to number
 * of referencies to them. When they are only referenced by their display, they are deleted and remove from the window.</p>
 
*/

namespace eosim {

namespace graphic {

	class Sprite {
    public:
        struct impl;
		/**
		* \brief This operation creates a Sprite with undefined state. It is an error to invoke any operation except assign
		* it to another Sprite.
		*/
        Sprite();
		/**
		* \brief This is a constructor of Sprite.
		* <p> It returns a Sprite assigned to dis. The Sprite is drawn with the image which is in file, placed in (x,y).
		*/
        Sprite(Display& dis, const char* file, double x, double y);
		/**
		* \brief This operation asigns an image to the Sprite. The supported file formats are BMP, PNM, XPM, XCF, PCX, GIF,
		* JPG, TIF, PNG y LBM.
		*/
        void setImage(const char* file);
		/**
		* \brief This operation assigns a move sequence to a Sprite.
		* <p>To move a Sprite we assign a MoveAction to it. A MoveAction has a position and a time. When it is assigned, the 
		* Sprite will move from its actual position to the assigned position in the assigned time (waypoint). For example:
		*
		* <code class="fragment">my_sprite.setMoves(move(2,4,6));</code>
		*
		* will move my_sprite from its actual position to (2,4) in 6 time units (it will reach (2,4) in t + 6 if t is the
		* time when Sprite::setMoves is invoked). </p>
		* <p>It is also possible to assign a sequence of waypoints with this function:
		*
		* <code class="fragment">my_sprite.setMoves(move(2,4,6).move(0,0,8));</code>
		*
		* here the Sprite will go first to (2,4) then to (0,0) in 14 time units (6 to (2,4) then to 8 to (0,0)).
		* <p>Once those waypoints have been assigned, Display::advance moves sprites and textSprites for their assigned 
		* waypoints continously, until there are no more moves assigned. A new invocation of this operation will remove old
		* waypoints and the movement will start from the object actual position.</p>
		*/
        void setMoves(MoveAction m);
		/**
		* \brief This operation makes the Sprite visible.
		*/
        void setVisible(bool v);
		/**
		* \brief This operation returns true if the Sprite is visible.
		*/
        bool getVisible() const;
    private:
        boost::shared_ptr<impl> p_impl;
    };

}

}

/**
 * \@}
*/

/** \ingroup graphic_group
 * \@{
*/
/** \class eosim::graphic::TextSprite \include\eosim\graphic\Display.hpp <eosim/graphic/Display.hpp>
 * \author Bruno Martínez, Fernando Pardo and Sebastián Alaggia
 * \version 1.1.1
 * \date    2005
 * \brief  Text Sprite
 * \note In order to use this Sprite the font <b>timesi.ttf</b> must be in the application directory.
*/

namespace eosim {

namespace graphic {

	class TextSprite {
    public:
        struct impl;
		/**
		* \brief This operation creates a Sprite with undefined state. It is an error to invoke any operation except assign
		* it to another Sprite.
		*/
        TextSprite();
		/**
		* \brief This is a constructor of Sprite.
		* <p> It returns a Sprite assigned to dis. The Sprite is drawn with a text, placed in (x,y).
		*/
        TextSprite(Display& dis, const char* text, double size, double x, double y);
		/**
		* \brief This operation asigns a text to the Sprite.
		*/
        void setText(const char* text);
		/**
		* \brief This operation assigns a move sequence to a TextSprite (see Sprite::setMoves).
		*/
        void setMoves(MoveAction m);
		/**
		* \brief This operation makes the Sprite visible.
		*/
        void setVisible(bool v);
		/**
		* \brief This operation returns true if the Sprite is visible.
		*/
        bool getVisible() const;
     private:
        boost::shared_ptr<impl> p_impl;
    };


}

}
/**
 * \@}
*/

/** \ingroup graphic_group
 * \@{
*/
/** \struct eosim::graphic::MoveAction \include\eosim\graphic\Display.hpp <eosim/graphic/Display.hpp>
 * \author Bruno Martínez, Fernando Pardo and Sebastián Alaggia
 * \version 1.1.1
 * \date    2005
 * \brief  Movement Action of a Sprite
 * <p>This struct is used to assign movements to the sprites. The function MoveAction::move is used to add more moves to an
 * Sprite.</p>
*/

namespace eosim {

namespace graphic {

	struct MoveAction {
    struct waypoint {
        double x;
        double y;
        double time;
    };
    std::deque<waypoint> waypoints;
    MoveAction& move(double x, double y, double time) {
        waypoint w = {x, y, time};
        waypoints.push_back(w);
        return *this;
    }
};

}

}
/**
 * \@}
*/

#endif

