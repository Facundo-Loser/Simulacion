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

#include <eosim/core/entity.hpp>
#include <eosim/core/bevent.hpp>
#include <cassert>

using namespace eosim::core;


Entity::Entity (): bEv(0), clock(0) {}

Entity::~Entity () {}

void Entity::setBEvent (BEvent* bEv) {
	/**
	* \note Entities have to know to which event they are scheduled. The BCalendar only schedule the entity to a certain time, not to a certain event.
	*/
    /**
	* \warning The programmer should not use this operation, it is invoked directly by EOSimulator.
	* \warning If setBEvent is invoked with null, the simulation aborts immediately displaying an error message. 
	*/
    assert(bEv != 0 && "Entity::setBEvent: Error assigning a BEvent");
    this->bEv = bEv;
}

void Entity::setClock (double clock) {
    this->clock = clock;
}

double Entity::getClock () {
    return clock;
}

void Entity::processEvent () {
    bEv->eventRoutine(this);
}

