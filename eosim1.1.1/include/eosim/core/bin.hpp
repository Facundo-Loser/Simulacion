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

#ifndef BIN_HPP_
#define BIN_HPP_

/** \class eosim::core::Bin include\eosim\core\bin.hpp <eosim/core/bin.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Abstract Bin
 
 * This is the parent class of all Bins.
*/

namespace eosim {

namespace core {

	class Bin {
	protected:
		double quantity;
		/**
		* \brief The constructor of Bin.
		*/
		Bin(double quantity);
	public:
		/**
		* \brief The destructor of Bin.
		*/
		virtual ~Bin();
		/**
		* \brief This operation acquires amount units of the bin.
		*/
		void acquire (double amount);
		/**
		* \brief This operation returns if there is at least amount units of bin available.
		*/
		bool isAvailable (double amount);
		/**
		* \brief This operation returns the actual amount of bins available.
		*/
		double getQuantity();
	};

}

}

#endif

