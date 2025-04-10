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

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <eosim/graphic/Display.hpp>
#include <eosim/graphic/refreshgraphic.hpp>

/**
 * \defgroup graphic_group Graphic Simulations
 
 * <p>Graphical Simulations are very usefull for validation, it gives a view of the system which is difficult to obtain using
 * only the data collecte during several simulations. EOSimulator (since version 1.1.1) support 2D iconic animation of 
 * simulation, based on <b><a href="http://www.boost.org/">Boost C++ Libraries</a>, <a href="http://www.libsdl.org/index.php">
 * SDL</a>, <a href="http://www.libsdl.org/projects/SDL_image/"> SDL_image</a>, <a href="http://www.antigrain.com/">
 * Antigrain Geometry</a></b> and <b><a href="http://www.freetype.org/">FreeType</a></b>. This part of the library was mainly developed as part of a Degree Thesis of Sebasti&aacute;n
 * Alaggia, Bruno Mart&iacute;nez and Fernando Pardo.</p>
 * <p>For developing graphical simulations, EOSimulator provides three clases and a CEvent:
 * <ul>
 *		<li>eosim::graphic::Display: This class defines the environment to develop a graphical simulation: a window, a 
			container of the objects that will be drawn and moved during the simulation. You can put a background image in 
			the window to create a "more realistic" simulation</li>
 *		<li>eosim::graphic::Sprite: A sprite is an object that could be drawn and move in the window. Sprites are drawn by
			assigning them an image file.</li>
 *		<li>eosim::graphic::TextSprite: Is the same concept that display, but with written text.</li>
 *		<li>eosim::graphic::RefreshGraphic: This is a CEvent which will synchronize the display with the calendar. This 
 *			CEvent must be the last one registered in a graphical model.</li>
 * </ul>
*/


#endif

