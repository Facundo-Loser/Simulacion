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

#ifndef NUMBERGENERATORFACTORY_HPP_
#define NUMBERGENERATORFACTORY_HPP_

#include <eosim/dist/numbergenerator.hpp>

/** \ingroup dist_group
 * \@{
*/
/** \class eosim::dist::NumberGeneratorFactory include\eosim\dist\numbergeneratorfactory.hpp <eosim/dist/numbergeneratorfactory.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Random Number Generator Factory
 
 * This class is a factory of random number generator classes. It returns a new generator whose type is type.
*/


namespace eosim {
	
namespace dist {

	class NumberGeneratorFactory {
	public:
		/**
		* \brief It returns a pointer to a new generator whose type is type.
		* \note Every generator is identified by a GenType label. The generator returned has to be deleted by the programmer. In order to add new generators the code of this function has to be rewritten and GenType has to be updated by adding a new label for the generator.
		*/
        static NumberGenerator* make(GenType type); 
	};

}

}

/**
 * \@}
*/

#endif

