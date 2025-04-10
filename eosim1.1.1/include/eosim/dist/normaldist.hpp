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

#ifndef NORMALDIST_HPP_
#define NORMALDIST_HPP_

#include <eosim/dist/distribution.hpp>

/** \ingroup dist_group
 * \@{
*/
/** \class eosim::dist::NormalDist include\eosim\dist\normaldist.hpp <eosim/dist/normaldist.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Normal Distribution
 
 * This class sample values from a normal distribution.
*/

            


namespace eosim {
	
namespace dist {

	class NormalDist: public Distribution {
	private:
		double m, sd;
	public:
		/**
		* \brief The constructor creates a NormalDist with mean m, standard deviation sd and whose generator’s type is gen.
		*/
		NormalDist (GenType gen, double m, double sd);
		/**
		* \brief The destructor of NormalDist.
		*/
		~NormalDist ();
		/**
		* \brief This operation samples a value the distribution.
		*/
		double sample ();
	};

}

}

/**
 * \@}
*/

#endif

