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

#ifndef BEVENT_HPP_
#define BEVENT_HPP_

#include <string>

/** \ingroup modeling_group
 * \@{
*/
/** \class eosim::core::BEvent include\eosim\core\bevent.hpp <eosim/core/bevent.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  B Events
 
 * <p>This is the parent class of all B events. A BEvent (bounded event) is an relevant point of time which is
 * going to occur at a certain time to a certain group of entities.</p>
 * <p>BEvent is an abstract class which represents a bounded event that is relevant to a system. BEvents are 
 * stateless objects; they must not have any attribute that change over a simulation. They are just treated as a 
 * sample of code which is executed by the entities. Remember that BEvents are Model’s attributes.</p>
 * <p>Like in Model, to create a subclass of BEvent you must implement three methods:
 * <ul>
 *		<li>a constructor,</li>
 *		<li>a destructor,</li>
 *		<li>and BEvent::eventRoutine.</li>
 * </ul>
 * </p>
 * <p>Every BEvent has a name and belongs to a Model. BEvent::name is very important because it is the key used by
 * Model to schedule an entity. Besides, BEvents have the attribute BEvent::owner to have access to its model.
 * These parameters appear in BEvent constructor and it must be called at the constructor of any subclass. It
 * could be a good idea to keep all names in a separate header file in order to make fewer mistakes scheduling
 * entities. <b>BEvents have to be registered using Model::registerBEvent,</b> otherwise when scheduling an entity
 * to a certain BEvent, it won't be found an error will be raised.</p>
 * <p>BEvent::eventRoutine is the main operation of this class. It defines every action taken in that particular
 * point in time. BEvents acts over one specific entity and may change the state of the model. If one event 
 * creates or deletes an Entity, see the rules decripted in the documentation of that class.</p>
*/


namespace eosim {

namespace core {

    class Model;
    class Entity;
    
	class BEvent {
    private:
		/**
		* \brief The name of the BEvent.
		* \note Is very important that this attribute is unique and well defined, because it is used in Model::schedule to assign the right bound event to an entity.
		*/
		std::string name;
	protected:
		/**
		* \brief The Model to whom this event belongs.
		* \ note This attribute give visibility to the model in order to modify its state.
		*/
		Model& owner;
	public:
		/**
		* \brief The constructor creates a BEvent with name name which belongs to the Model owner.
		*/
		BEvent (std::string name, Model& owner);
		/**
		* \brief The destructor of BEvent.
		*/
		virtual ~BEvent ();
		/**
		* \brief This operation returns the event’s name.
		*/
        std::string getName();
		/**
		* \brief This abstract operation brings an uniform interface to BEvents routines.
		* \note  In order to model an specific event, the programmer has to give an specific method to this operation. If the event needs to have access to its model, use the attribute owner.
		*/
		virtual void eventRoutine (Entity* who) = 0;
	};
	
}

}

/**
 * \@}
*/

#endif

