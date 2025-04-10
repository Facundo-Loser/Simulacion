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

#ifndef BCALENDAR_HPP_
#define BCALENDAR_HPP_

#include <eosim/core/entity.hpp>
#include <eosim/utils/entityqueueordered.hpp>

/** \ingroup simuling_group
 * \@{
*/
/** \class eosim::core::BCalendar include\eosim\core\bcalendar.hpp <eosim/core/bcalendar.hpp>
 * \author Sebastián Alaggia
 * \version 1.0.1
 * \date    2005
 * \brief  B Events Calendar
 * <p>This class handles the B Events Calendar. The class main responsibility is to schedule entities for a
 * certain time to a certain bounded event. It also handles the simulation time.</p>
*/



namespace eosim {

namespace core {

	class BCalendar {
	private:
        double simTime, endSim;
        utils::EntityQueueOrdered ents;
	public:
		/**
		* \brief The constructor creates an empty BCalendar ready to operate.
		*/
		BCalendar ();
		/**
		* \brief The destructor deletes all the entities scheduled.
		*/
		~BCalendar ();
		/**
		* \brief This operation performs both A phase and B phase.
		*/
		void bPhase ();
		/**
		* \brief This operation returns true if the simulation is terminated.
		*/
		bool isStopped();
		/**
		* \brief This operation schedules who at the simulation’s actual time plus offset. It is assumed that who knows to which event is scheduled.
		*/
		void schedule (double offset, Entity* who);
		/**
		* \brief This operation sets the simulation’s end time. All simulations starts at 0.
		*/
		void setEndTime (double when);
		/**
		* \brief This operation returns the simulation’s actual time.
		*/
        double getSimTime();
	};
	
}

}

/**
 * \@}
*/

#endif

