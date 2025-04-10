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

#include <eosim/core/bin.hpp>
#include <cassert>

using namespace eosim::core;

Bin::Bin(double quantity): quantity(quantity) {
    /**
	 * \warning A bin must be created with a non negative quantity.
	*/
	assert(quantity >= 0 && "Bin::Bin: Error creating a bin");
}

Bin::~Bin() {}

void Bin::acquire (double amount) {
    /**
	 * \warning To acquire certain amount of a bin you must be sure that there is enoght units of the bin to satisfy your request.
	*/
	assert(amount <= quantity && "Bin::acquiere: Error aquiring a bin"); 
	quantity -= amount;
}

bool Bin::isAvailable (double amount) {
 return quantity >= amount;
}

double Bin::getQuantity() {
	return quantity;
}
