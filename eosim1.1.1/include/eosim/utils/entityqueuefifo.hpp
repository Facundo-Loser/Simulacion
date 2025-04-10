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

#ifndef ENTITYQUEUEFIFO_HPP_
#define ENTITYQUEUEFIFO_HPP_

#include <eosim/utils/entityqueue.hpp>
#include <deque>


/** \ingroup utils_group
 * \@{
*/
/** \class eosim::utils::EntityQueueFifo include\eosim\utils\entityqueuefifo.hpp <eosim/utils/entityqueuefifo.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief   Fifo Queue of Entities
 
 * This is a fifo queue of entities.
*/



namespace eosim {
	
namespace utils {

	class EntityQueueFifo: public EntityQueue {
	private:
        std::deque<core::Entity*> elems;
    public:
		/**
		* \brief The constructor creates an empty EntityQueueFifo.
		*/
        EntityQueueFifo();
		/**
		* \brief The destructor of EntityQueueFifo.
		*/
        ~EntityQueueFifo();
		/**
		* \brief This operation adds ent at the end of queue.
		*/
        void push(core::Entity* ent);
		/**
		* \brief This operation returns and remove the first entity in the queue.
		*/
        core::Entity* pop();
		/**
		* \brief This operation removes the entity whose position is i.
		*/
        void remove(unsigned int i);
		/**
		* \brief This operation returns 1 if the queue is empty.
		*/
        bool empty();
		/**
		* \brief This operation returns the entity whose position is i.
		*/
        core::Entity* operator[] (unsigned int i);
		/**
		* \brief This operation returns the size of the queue.
		*/
		unsigned int size();	
	};

}

}

#endif

