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

#ifndef EXPERIMENT_HPP_
#define EXPERIMENT_HPP_

#include <string>
#include <eosim/core/bcalendar.hpp>
#include <eosim/core/ccalendar.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/dist/distmanager.hpp>
#include <eosim/dist/distribution.hpp>

/** \ingroup simuling_group
 * \@{
*/
/** \class eosim::core::Experiment include\eosim\core\experiment.hpp <eosim/core/experiment.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Experiment Manager
 
 * <p>This class handles the execution of a simulation. It is a main class in EOSimulator. While Model is defines
 * the system, Experiment handles the runs.</p>
*/


namespace eosim {

namespace core {

    class Model;

	class Experiment {
	private:
		bool running;
		dist::DistManager distMan;
		BCalendar bCal;
		CCalendar cCal;
		Model* currModel;
	public:
		/**
		* \brief The constructor creates an Experiment.
		*/
		Experiment ();
		/**
		* \brief The destructor deletes all the entities scheduled.
		*/
		~Experiment();
		/**
		* \brief This operation simulates the connected model until simTime.
		*/
		void run (double simTime);
		/**
		* \brief This operation links an experiment to model.
		*/
		void setModel (Model* model);
		/**
		* \brief This operation schedules who at the simulation’s actual time plus offset.
		*/
		void schedule (double offset, Entity* who);
		/**
		* \brief This operation uses seed to assign a new seed to all distribution registered in the model.
		*/
		void setSeed (unsigned long seed);
		/**
		* \brief This operation register dist in the experiment.
		*/
		void registerDist (dist::Distribution* dist);
		/**
		* \brief This operation register cEv in the experiment.
		*/
		void registerCEvent (CEvent* cEv);
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

