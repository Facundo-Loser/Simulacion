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

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

/** \ingroup modeling_group
 * \@{
*/
/** \class eosim::core::Entity include\eosim\core\entity.hpp <eosim/core/entity.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Entity
 
 * <p>This is the parent class of all entities. Entity is a class that represents objects or components of the
 * system whose activities are modeled. EOSimulator provides a primitive entity which has both a BEvent and a time
 * stamp that indicates the entity’s last bounded event, the clock. If your model needs a more specific entity, 
 * just implement a new subclass.</p>
 * <p>There’s a particular issue when it comes to entities: <b>All entities of a system must be created 
 * dynamically, even global or permanent entities. And only temporary entities must be deleted when they
 * leave the system.</b></p>
 * <p>That's because of the way that EOSimulator containers are implemented. Entity containers
 * have pointers to its elements, in order to avoid copies. When their destructor is called, it destroys every
 * entity stored. When a simulation ends, every entity is scheduled or waiting in a queue, so they are in an
 * EOSimulator’s container. Entity containers have pointers to its elements, in order to avoid copies. When their
 * destructor is called, it destroys every entity stored. This policy is imposed by EOSimulator
 * but it must be controlled by the user (see Collections).</p>
*/


namespace eosim {

namespace core {

    class BEvent;    

	class Entity {
    private:
		BEvent* bEv;
		double clock;
	public:
		/**
		* \brief The constructor creates an Entity. Remember, all entities must be created dynamically, even global entities.
		*/
		Entity ();
		/**
		* \brief The destructor of Entity.
		*/
		virtual ~Entity ();
		/**
		* \brief This operation sets the entity’s next BEvent to bEv.
		* \note Entities have to know to which event they are scheduled. The BCalendar only schedule the entity to a certain time, not to a certain event. If setBEvent is invoked with null, the simulation aborts immediately displaying an error message.
		* \warning The programmer should not use this operation, it is invoked directly by EOSimulator.
		*/
		void setBEvent (BEvent* bEv);
		/**
		* \brief This operation sets the time when the next BEvent is going to occur. 
		* \warning The programmer should not use this operation, it is invoked directly by EOSimulator.
		*/
		void setClock (double clock);
		/**
		* \brief Returns the time of the last entity’s B event.
		*/
		double getClock ();
		/**
		* \brief This operation process the routine of the entity’s actual BEvent. 
		* \warning The programmer should not use this operation, it is invoked directly by EOSimulator.
		*/
		void processEvent ();
	};

}

}

/** \ingroup modeling_group
 * \class eosim::core::EntityComp include\eosim\core\entity.hpp <eosim/core/entity.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Entities Abstract Comparator
 
 * <p>EntityComp is the parent class of all Entity Comparators and it is the only EOSimulator’s abstract
 * class that is used optionally. Its main operation is EntityComp::compare, which compare two entities. These
 * comparators are user defined classes. There are used to create priority queues according to the needs of the
 * programmer.</p>
*/


namespace eosim {

namespace core {

	class EntityComp {
	public:
		/**
		* The constructor creates an EntityComp.
		*/
		EntityComp () {}
		/**
		* The destructor of EntityComp.
		*/
		virtual ~EntityComp () {}
		/**
		* This abstract operation compares e1 and e2. This is the main operations of Comparators. The programmer has to give a method to this operation to implement a specific comparator.
		*/
		virtual bool compare (Entity* e1, Entity* e2) = 0;
	};
    
}

}

/**
 * \@}
*/

#endif

