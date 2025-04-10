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

#ifndef CEVENTVECTOR_HPP_
#define CEVENTVECTOR_HPP_

#include <eosim/core/cevent.hpp>
#include <vector>

/** \ingroup utils_group
 * \@{
*/
/** \class eosim::utils::CEventVector include\eosim\utils\ceventvector.hpp <eosim/utils/ceventvector.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief   Vector of C Events
 
 * This container stores CEvents in a vector. It is used by CCalendar to register CEvent.
*/


namespace eosim {

namespace utils {

	class CEventVector {
	private:
		std::vector<core::CEvent*> elems;
	public:
		/**
		* \brief The constructor creates an empty CEventVector.
		*/
		CEventVector ();
		/**
		* \brief The destructor of CEventVector. This operation doesn’t delete any CEvents stored
		*/
		~CEventVector ();
		/**
		* \brief This operation adds elem at the end of the vector.
		*/
		void push (core::CEvent* elem);
		/**
		* \brief This operation remove the element whose position in the vector is i.
		*/
        void remove (unsigned i);
		/**
		* \brief This operation returns the CEvent whose position in the vector is i.
		* \note The use of this operation is either cVect[i] or cVect.operator[](i).
		*/
        core::CEvent* operator[] (unsigned int i);
		/**
		* \brief This operation returns the size of the vector.
		*/
		unsigned int size();	
	};
}

}

#endif

