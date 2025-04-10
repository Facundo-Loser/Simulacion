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

#include <eosim/utils/beventmap.hpp>
#include <cassert>

using namespace eosim::utils;
using namespace eosim::core;
using namespace std;


BEventMap::BEventMap () {}

BEventMap::~BEventMap () {
	/**
	* \note This operation doesn’t delete any BEvents stored.
	*/
}

void BEventMap::put (BEvent* elem) {
	/**
	* \warning The name of the element stored must be unique.
	*/
    assert(elems.find(elem->getName()) == elems.end() && "BEventMap::put: Error inserting a BEvent in a BEventMap");
    elems[elem->getName()] = elem;
}

void BEventMap::remove (string key) {
	/**
	* \warning There must be a BEvent registered whose name is equal to key.
	*/
	assert(elems.find(key) != elems.end() && "BEventMap::remove: Error removing a BEvent from a BEventMap");
    elems.erase(key);
}

BEvent* BEventMap::operator[] (string key) {
	/**
	* \note The use of this operation is either bMap[key] or bMap.operator[](key). If the map is empty or there isn’t any element whose name is key, the simulation aborts immediately displaying an error message.
	*/
    /**
	* \warning The map must be not empty and there must be a BEvent whose name is equal to key.
	*/
	BEvent* ret = elems[key];
    assert(ret != 0 && ret->getName() == key && "BEventMap::operator[]: Error indexing in a BEventMap with an unregister key");
    return ret;
}

unsigned int BEventMap::size() {
    return elems.size();
}	

