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

#ifndef BEVENTMAP_HPP_
#define BEVENTMAP_HPP_

#include <eosim/core/bevent.hpp>
#include <map>
#include <string>

/** \ingroup utils_group
 * \@{
*/
/** \class eosim::utils::BEventMap include\eosim\utils\beventmap.hpp <eosim/utils/beventmap.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief   Mapping of B Events
 
 * This container stores BEvents, using their name as key. It is used by Model to register BEvent.
*/


namespace eosim {

namespace utils {

	class BEventMap {
	private:
		std::map<std::string, core::BEvent*> elems;
	public:
		/**
		* \brief The constructor creates an empty BEventMap.
		*/
		BEventMap ();
		/**
		* \brief The destructor of BEventMap.
		*/
		~BEventMap ();
		/**
		* \brief This operation adds elem to the map.
		*/
		void put (core::BEvent* elem);
		/**
		* \brief This operation remove the element whose name is key.
		*/
        void remove (std::string key);
		/**
		* \brief This operation finds the BEvent whose name is key.
		*/
        core::BEvent* operator[] (std::string key);
		/**
		* \brief This operation returns the size of the map.
		*/
		unsigned int size();	
	};

}

}

#endif

