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

#ifndef REFRESH_GRAPHIC_HPP_
#define REFRESH_GRAPHIC_HPP_

#include <eosim/core/cevent.hpp>
#include <eosim/graphic/Display.hpp>

/** \ingroup graphic_group
 * \@{
*/
/** \class eosim::graphic::RefreshGraphic \include\eosim\graphic\RefreshGraphic.hpp  <eosim/graphic/RefreshGraphic.hpp>
 * \author Sebastián Alaggia
 * \version 1.1.1
 * \date    2006
 * \brief  C Event which refresh the graphics of a Display.
 * <p>This is an auxiliary class used to invoke Display::advance. In RefreshGraphic::eventRoutine the time beat is calculated,
 * and the Display is advanced correctly.</p>
 * \Note To make a graphical model this event must be the last registered CEvent in the model.
*/

namespace eosim {

namespace graphic {

	class RefreshGraphic: public eosim::core::CEvent {
	private:
		Display& d;
		double lastTime;
	public:
		/**
		* \brief This is the constructor a RefreshGraphic, linked to a model and to the Display which will be advanced.
		*/
		RefreshGraphic(eosim::core::Model& model, Display& disp);
		/**
		* \brief The destructor of RefreshGraphic
		*/
		~RefreshGraphic();
		/**
		* \brief In this operation the time beat is calculated and the Display is advanced.
		*/
		void eventRoutine();
	};

}

}

/**
 * \@}
*/

#endif

