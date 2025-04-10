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

#ifndef UNIFORMDIST_HPP_
#define UNIFORMDIST_HPP_

#include <eosim/dist/distribution.hpp>

/** \ingroup dist_group
 * \@{
 * \class eosim::dist::UniformDist include\eosim\dist\uniformdist.hpp <eosim/dist/uniformdist.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Uniform Distribution
 
 * This class sample values from a uniform distribution.
*/


namespace eosim {
	
namespace dist {

	class UniformDist: public Distribution {
	private:
		double low, upper;
	public:
		/**
		* \brief The constructor creates a UniformDist with lower bound low, upper bound upper and whose whose generator’s type is gen.
		*/
		UniformDist (GenType gen, double low, double upper);
		/**
		* \brief The destructor of UniformDist.
		*/
		~UniformDist ();
		/**
		* \brief This operation samples a value from the distribution.
		*/
		double sample ();
	};

}

}

/**
 * \@}
*/

#endif

