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

#include <eosim/core/renewable.hpp>
#include <cassert>

using namespace eosim::core;


Renewable::Renewable(double quantity, double max): Bin(quantity), max(max) {
	/**
	* \warning The quantity must be less or equal than max, and max must be greater or equal than zero.
	*/
    assert(quantity <= max &&  "Renewable::Renewable: Error creating a Renewable bin");
}

Renewable::~Renewable() {}

void Renewable::returnBin (double amount) {
	/**
	* \warning The amount returned plus the actual quantity of the bin must be less or equal the bin’s capacity.
	*/
    assert(amount + quantity <= max && "Renewable::returnBin: Error returning Renewable bins"); 
    quantity += amount;
}

double Renewable::getMax() {
	return max;
}
