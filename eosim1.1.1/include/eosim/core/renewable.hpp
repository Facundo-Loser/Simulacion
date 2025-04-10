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

#ifndef RENEWABLE_HPP_
#define RENEWABLE_HPP_

#include <eosim/core/bin.hpp>

/** \class eosim::core::Renewable include\eosim\core\renewable.hpp <eosim/core/renewable.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Renewable Bin
 
 * This class represent bins which are renewable, like chairs. This kind of bins are returned after they are used. So you can use them and return them after used. It inherits the acquire operation from its parent class, Bin.
*/




namespace eosim {

namespace core {

	class Renewable: public Bin {
	private:
		double max;
	public:
		/**
		* \brief The constructor creates a Renewable bin with quantity units and max capacity. If quantity is greater or equal than max and max is less or equal than zero, the simulation aborts immediately displaying an error message. 
		*/
		Renewable (double cuantity, double max);
		/**
		* \brief The destructor of Renewable.
		*/
		~Renewable ();
		/**
		* \brief This operation return amount units to the bin.
		*/
		void returnBin (double amount);	
		/**
		* \brief This operation returns the maximum capacity of the bin.
		*/
		double getMax();
	};
	
}

}

#endif

