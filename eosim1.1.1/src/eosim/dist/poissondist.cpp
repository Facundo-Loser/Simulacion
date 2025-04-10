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

#include <eosim/dist/poissondist.hpp>
#include <cmath>


using namespace eosim::dist;


PoissonDist::PoissonDist(GenType gen, double m):
                         Distribution(gen), m(m) {} 

PoissonDist::~PoissonDist() {}

double PoissonDist::sample() {
	/**
	* \note The value is calculated iteratively.
	*/
    double rnd, p;
    unsigned int x;
    rnd = generator->nextDouble();
    p = exp(-m);
    x = 0;
    for (double f = p ;rnd > f; f += p) {
        x++;
        p *= (m/x);
    }
    return x;
}

