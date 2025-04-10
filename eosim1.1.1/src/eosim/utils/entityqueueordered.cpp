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

#include <eosim/utils/entityqueueordered.hpp>
#include <cassert>

using namespace eosim::core;
using namespace eosim::utils;
using namespace std;


EntityQueueOrdered::EntityQueueOrdered(EntityComp* comp): comp(comp) {}

EntityQueueOrdered::~EntityQueueOrdered() {
    for (deque<Entity*>::iterator i = elems.begin(); i != elems.end(); i++) {
        delete *i;
    }
}

void EntityQueueOrdered::push(Entity* ent) {
    /**
	* \note The queue is implemented using a std::deque. That give us O(1) when accessing an element and inserting in the back and front. But O(n) when inserting in the midle. 
	* \note We use binary search to find were to insert, but the insertion is the bottle neck of this operation.
	*/
	if (elems.empty() || comp->compare(ent, elems[0]))
        elems.push_front(ent);
    else if (comp->compare(elems[elems.size()-1], ent))
        elems.push_back(ent);
    else {
        unsigned int i = 0;
        unsigned int j = elems.size();
        for (; i != j - 1; ) {
            if (comp->compare(ent, elems[(i+j)/2]))
                j = (i + j) / 2;
            else
                i = (i + j) / 2;
        }
        deque<Entity*>::iterator it = elems.begin();
        it += i+
        1;
        elems.insert(it, ent);
    }
}

Entity* EntityQueueOrdered::pop() {
	/**
	* \warning The queue is must not be empty.
	*/
    assert(elems.size() > 0 && "EntityQueueOrdered::pop: Error removing the first element of a EntityQueueOrdered");
    Entity* e = elems.front();
    elems.pop_front();
    return e;
} 

void EntityQueueOrdered::remove(unsigned int i) {
	/**
	* \warning i must be within the limits of the queue.
	*/
    assert(i < elems.size() && "EntityQueueOrdered::remove: Error removing an Entity from an EntityQueueOrdered");
    elems.erase(elems.begin() + i);
}

bool EntityQueueOrdered::empty() {
    return elems.empty();
}

Entity* EntityQueueOrdered::operator[] (unsigned int i) {
	/**
	* \warning i must be within the limits of the queue.
	*/
    assert(i < elems.size() && "EntityQueueOrdered::operator[]: Error indexing in an EntityQueueOrdered");
    return elems[i];
}

unsigned int EntityQueueOrdered::size() {
    return elems.size();
}

