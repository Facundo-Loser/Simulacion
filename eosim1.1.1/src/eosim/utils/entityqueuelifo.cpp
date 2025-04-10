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

#include <eosim/utils/entityqueuelifo.hpp>
#include <cassert>

using namespace eosim::core;
using namespace eosim::utils;
using namespace std;


EntityQueueLifo::EntityQueueLifo() {}

EntityQueueLifo::~EntityQueueLifo() {
    for (deque<Entity*>::iterator i = elems.begin(); i != elems.end(); i++) {
        delete *i;
    }
}

void EntityQueueLifo::push(Entity* ent) {
    elems.push_front(ent);
}

Entity* EntityQueueLifo::pop() {
	/**
	* \warning The queue is must not be empty.
	*/
    assert(elems.size() > 0 && "EntityQueueLifo::pop: Error removing the first element of a EntityQueueLifo");
    Entity* e = elems.front();
    elems.pop_front();
    return e;
} 

void EntityQueueLifo::remove(unsigned int i) {
	/**
	* \warning i must be within the limits of the queue.
	*/
    assert(i < elems.size() && "EntityQueueLifo::remove: Error removing an Entity from an EntityQueueLifo");
    elems.erase(elems.begin() + i);
}

bool EntityQueueLifo::empty() {
    return elems.empty();
}

Entity* EntityQueueLifo::operator[] (unsigned int i) {
	/**
	* \warning i must be within the limits of the queue.
	*/
    assert(i < elems.size() && "EntityQueueLifo::operator[]: Error indexing in a EntityQueueLifo");
    return elems[i];
}

unsigned int EntityQueueLifo::size() {
    return elems.size();
}

