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

#ifndef NEGEXPDIST_HPP_
#define NEGEXPDIST_HPP_

#include <eosim/dist/distribution.hpp>

/** \ingroup dist_group
 * \@{
*/
/** \class eosim::dist::NegexpDist include\eosim\dist\negexpdist.hpp <eosim/dist/negexpdist.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Negative Exponential Distribution
 
 * This class sample values from a negative exponential distribution.
*/


            

namespace eosim {
	
namespace dist {

	class NegexpDist: public Distribution {
	private:
		double m;
	public:
		/**
		* \brief The constructor creates a NegexpDist with mean m and whose generator’s type is gen.
		*/
		NegexpDist (GenType gen, double m);
		/**
		* \brief The destructor of NegexpDist.
		*/
		~NegexpDist ();
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

