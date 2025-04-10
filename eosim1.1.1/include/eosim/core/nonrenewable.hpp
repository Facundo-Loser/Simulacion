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

#ifndef NONRENEWABLE_HPP_
#define NONRENEWABLE_HPP_

#include <eosim/core/bin.hpp>

/** \class eosim::core::NonRenewable include\eosim\core\nonrenewable.hpp <eosim/core/nonrenewable.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Nonrenewable Bin
 
 * This class represent bins which are consumable, like coffee. This kind of bins are consume while they are used. So you can use them and add some more before it is depleted. It inherits the acquire operation from its parent class, Bin.
*/


namespace eosim {

namespace core {

	class NonRenewable: public Bin {
	public:
		/**
		* \brief The constructor creates a NonRenewable bin with a quantity units.
		*/
		NonRenewable (double quantity);
		/**
		* The destructor of NonRenewable.
		*/
		~NonRenewable ();
		/**
		* \brief This operation add amount units to the bin.
		*/
		void addBin (double amount);	
	};

}

}

#endif

