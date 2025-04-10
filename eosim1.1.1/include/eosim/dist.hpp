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

#ifndef DIST_HPP_
#define DIST_HPP_

#include <eosim/dist/distmanager.hpp>
#include <eosim/dist/distribution.hpp>
#include <eosim/dist/lognormaldist.hpp>
#include <eosim/dist/ccalendar.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/dist/normaldist.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <eosim/dist/numbergeneratorfactory.hpp>
#include <eosim/dist/poissondist.hpp>
#include <eosim/dist/uniformdist.hpp>

/**
 * \defgroup dist_group Distributions
 * <br>
 * <p>EOSimulator’s Distribution Module contains facilities for random number generation and distribution sampling.</p>
 * <p>In this module we have encapsulated pseudo-random generators and distribution sampling. All distributions
 * are subclasses of Distribution, an abstract class which defines the behavior of every distribution in
 * EOSimulator. Every distribution has a pseudo-random number generator, defined by the interface NumberGenerator.</p>
 * <p>Finally NumberGeneratorFactory creates NumberGenerators according to the corresponding GenType label. This
 * design allows the user to define both new generators and distribution.</p>
*/

#endif

