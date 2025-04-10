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

#ifndef ENTITYQUEUE_HPP_
#define ENTITYQUEUE_HPP_

#include <eosim/core/entity.hpp>

/** \ingroup utils_group
 * \@{
*/
/** \class eosim::utils::EntityQueue include\eosim\utils\entityqueue.hpp <eosim/utils/entityqueue.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief   Interface for Queue of Entities
 
 * This interface defines the behavior of all queues of entities in EOSimulator.
*/

namespace eosim {
	
namespace utils {

	class EntityQueue {
	public:
		/**
		* \brief The constructor creates an empty EntityQueue.
		*/
        EntityQueue() {};
		/**
		* \brief The destructor of EntityQueue.
		* \attention It assumed that all entities in a simulation are created dynamically, so when an EntityQueue is destroyed it deletes every entity stored.
		*/
        virtual ~EntityQueue() {};
		/**
		* \brief This operation adds ent in the queue.
		* \note The position where ent is inserted depends on the realization of the interface.
		*/
        virtual void push(core::Entity* ent) = 0;
		/**
		* \brief This operation returns and remove the first entity in the queue.
		*/
        virtual core::Entity* pop() = 0;
		/**
		* \brief This operation removes the entity whose position is i.
		*/
        virtual void remove(unsigned int i) = 0;
		/**
		* \brief This operation returns 1 if the queue is empty.
		*/
        virtual bool empty() = 0;
		/**
		* \brief This operation returns the entity whose position is i.
		* \note The use of this operation is either eQue[i] or eQue.operator[](i).
		*/
        virtual core::Entity* operator[] (unsigned int i) = 0;
		/**
		* \brief This operation returns the size of the queue.
		*/
		virtual unsigned int size() = 0;	
	};

}

}

#endif

