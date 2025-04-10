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

#ifndef DISTVECTOR_HPP_
#define DISTVECTOR_HPP_

#include <eosim/dist/distribution.hpp>
#include <vector>

/** \ingroup utils_group
 * \@{
*/
/** \class eosim::utils::DistVector include\eosim\utils\distvector.hpp <eosim/utils/distvector.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief   Vector of Distributions
 
 * This container stores Distributions in a vector. It is used by DistManager to register Distributions.
*/



namespace eosim {
	
namespace utils {

	class DistVector {
	private:
		std::vector<dist::Distribution*> elems;
	public:
		/**
		* \brief The constructor creates an empty DistVector.
		*/
		DistVector ();
		/**
		* \brief The destructor of DistVector. This operation doesn’t delete any Distributions stored
		*/
		~DistVector ();
		/**
		* \brief This operation adds elem at the end of the vector.
		*/
		void push (dist::Distribution* elem);
		/**
		* \brief This operation remove the element whose position in the vector is i.
		*/
        void remove (unsigned int i);
		/**
		* \brief This operation returns the Distribution whose position in the vector is i.
		*/
        dist::Distribution*& operator[] (unsigned int i);
		/**
		* \brief This operation returns the size of the vector.
		*/
		unsigned int size();	
	};
}

}

#endif

