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

#include <eosim/utils/ceventvector.hpp>
#include <cassert>

using namespace eosim::utils;
using namespace eosim::core;
using namespace std;


CEventVector::CEventVector () {}

CEventVector::~CEventVector () {
	/**
	* \note This operation doesn’t delete any CEvents stored.
	*/
}

void CEventVector::push (CEvent* elem) {
    elems.push_back(elem);
}

void CEventVector::remove (unsigned int i) {
	/**
	* \warning i must be within the limits of the vector.
	*/
	assert(i < elems.size() && "CEventVector::remove: Error removing a CEvent from a CEventVector");
    elems.erase(elems.begin() + i);
}

CEvent* CEventVector::operator[] (unsigned int i) {
	/**
	* \warning i must be within the limits of the vector.
	*/
    assert(i < elems.size() && "CEventVector::operator[]: Error indexing in a CEventVector");
    return elems[i];
}

unsigned int CEventVector::size() {
    return elems.size();
}

