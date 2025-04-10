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

#ifndef CCALENDAR_HPP_
#define CCALENDAR_HPP_

#include <eosim/core/cevent.hpp>
#include <eosim/utils/ceventvector.hpp>

/** \ingroup simuling_group
 * \@{
*/
/** \class eosim::core::CCalendar include\eosim\core\ccalendar.hpp <eosim/core/ccalendar.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  C Events Calendar
 
 * This class handles the simulation’s C phase. In the three phase approach, after every B phase all conditional event are executed.
*/

namespace eosim {

namespace core {

	class CCalendar {
	private:
		utils::CEventVector cEvs;
	public:
		/**
		* \brief The constructor creates an empty CCalendar ready to operate.
		*/
		CCalendar ();
		/**
		* \brief The destructor of CCalendar.
		*/
		~CCalendar ();
		/**
		* \brief This operation executes all the registered CEvents.
		*/
		void cPhase ();
		/**
		* \brief This operation register cEv in the CCalendar.
		*/
		void registerCEvent (CEvent* cEv);
	};

}

}

/**
 * \@}
*/

#endif

