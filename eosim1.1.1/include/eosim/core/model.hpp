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

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>
#include <eosim/core/entity.hpp>
#include <eosim/dist/distribution.hpp>
#include <eosim/utils/beventmap.hpp>
#include <eosim/utils/ceventvector.hpp>

/** \ingroup modeling_group simuling_group
 * \@{
*/
/** \class eosim::core::Model include\eosim\core\model.hpp <eosim/core/model.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  System Model
 
 * <p>This is the parent class of all models. A Model is a model of the system that you are going to simulate. 
 * It is a main class in EOSimulator. While Model defines the system, Experiment handles the runs. In order to 
 * define an specific model, you have to implement methods to the operations Model::init and Model::doInitialSchedules. You 
 * may need to define attributes such as queues, events, distributions, global entities and histograms.</p>
 * <p>Model is an abstract class which represents a model of the system that we are going to simulate. It contains
 * attributes such as bounded and conditional events, global entities, waiting queues, arrival distributions,
 * service distributions and output data collectors. This class is responsible of:
 * <ul>
 *		<li>containing and registering every attribute,</li>
 *		<li>defining the initial state of the system,</li>
 *		<li>give access to those attributes which are required for both bounded and conditional events.</li>
 * </ul>
 * </p>
 * <p>As we said above, Model is an abstract class. So, to create a specific model, we have to implement a subclass
 * of Model. To do that we must declare every attribute and implement four methods: 
 * <ul>
 *		<li>a constructor,</li>
 *		<li>a destructor,</li>
 *		<li>Model::init,</li>
 *		<li>and Model::doInitialSchedules.</li>
 * </ul>
 * </p>
 * <p>Attributes such as events (BEvents or CEvents), distributions (subclases Distribution), containers (typicaly
 * subclases of EntityQueue) and data collector (subclases of Histogram) have to be created, stored and deleted by
 * the model. The library just keeps references to those attributes and doesn’t delete any of them. Besides, these
 * attributes could be created either statically or dynamically. For entities things are a little different (see
 * Entity).</p>
 * <p>Then, we have to give a method to Model::init. In this operation we must create (if we haven’t done it yet)
 * and register attributes using the register operations defined in Model. The behaviour of the atribute depends
 * on its type.</p>
 * <p>Finally, Model::doInitialSchedules defines the system initial state. Here you schedule the first entities
 * to the corresponding bounded events. To schedule an entity use Model::schedule with the entity, the time 
 * when it is schedule (indicated by a time offset) and the name of the event. The last parameter is very important,
 * it is the key used by the model to find the right event. On return, the entity is inside the calendar, pointing
 * to the BEvent that it was scheduled and with the time when the event is going to happened.</p>
*/


namespace eosim {

namespace statics {
    class Histogram;
}

namespace core {

    class BEvent;
    class CEvent;
    class Experiment;
	
	class Model {
	private:
		Experiment* exp;
		utils::BEventMap bEvs;

	public:
		/**
		* \brief The constructor creates a primitive Model.
		* \note Its recommended that in the constructor of an specific model all attributes are created.
		* \note Remember that all entities must be created dynamically, even global entities.
		*/
		Model();
		/**
		* The destructor of Model.
		*/
		virtual ~Model();
		/**
		* \brief This operation initialize a model.
		* \note In this abstract operation, every model’s attribute (events, distributions, bins and histograms) has to be created (if they aren’t created yet) and registered. Those attributes which are not registered won’t work properly.
		* \note This operation is invoked when a model is connected to an experiment.
		*/
		virtual void init () = 0;
		/**
		* \brief This operation sets the model's initial state.
		* \note In this abstract operation the programmer has to schedule the firsts entities.
		* \note It is invoked when a model is connected to an experiment.
		*/
		virtual void doInitialSchedules () = 0;
		/**
		* \brief This operation connects a model to the experiment exp.
		*/
		void connectToExp (Experiment *exp);
		/**
		* \brief This operation register bEv in the model.
		*/
		void registerBEvent (BEvent* bEv);
		/**
		* \brief This operation register cEv in the model.
		*/
		void registerCEvent (CEvent* cEv);
		/**
		* \brief This operation register dist in the model.
		*/
		void registerDist (dist::Distribution* dist);
		/**
		* \brief This operation schedules who to the BEvent which name is what at the simulation’s actual time plus offset t.
		*/
		void schedule (double offset, Entity* who, std::string what);
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

