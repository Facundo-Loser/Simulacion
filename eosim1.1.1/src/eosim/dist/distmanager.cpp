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

#include <eosim/dist/distmanager.hpp>
#include <eosim/dist/numbergeneratorfactory.hpp>

using namespace eosim::dist;
using namespace eosim::utils;


DistManager::DistManager (GenType seedGenerator): seedGenerator(NumberGeneratorFactory::make(seedGenerator)) {}

DistManager::~DistManager () {
	/**
	* \note This operation don’t delete any registered distribution.
	*/
    delete seedGenerator;
}

void DistManager::setSeed (unsigned long seed) {
	/**
	* \note It uses both seed and its seed generator for assigning new seed to every registered distribution.
	*/
    seedGenerator->setSeed(seed);
    for ( unsigned int i = 0; i < dVect.size(); i++) {
        dVect[i]->setSeed(seedGenerator->nextLong());
    }
}

void DistManager::registerDist (Distribution* d) {
    dVect.push(d);
}

