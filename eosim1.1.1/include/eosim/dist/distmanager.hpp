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

#ifndef DISTMANAGER_HPP_
#define DISTMANAGER_HPP_

#include <eosim/dist/numbergenerator.hpp>
#include <eosim/utils/distvector.hpp>

/** \ingroup simuling_group
 * \@{
*/
/** \class eosim::dist::DistManager include\eosim\dist\distmanager.hpp <eosim/dist/distmanager.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Distribution Manager
 
 * This class handles a set of distributions. Its main responsibility is to perform operations to the whole set. It contains a seed generator to assign new seeds for the distributions registered.
*/


namespace eosim {
	
namespace dist {

	class DistManager {
	private:
		NumberGenerator* seedGenerator;
		utils::DistVector dVect;
	public:
		/**
		* \brief The constructor creates an empty DistManager with a seed generator of type seedGenerator.
		*/
		DistManager (GenType seedGenerator);
		/**
		* \brief The destructor of DistManager.
		*/
		~DistManager ();
		/**
		* \brief This operation sets a new seed to every distribution registered.
		*/
		void setSeed (unsigned long seed);
		/**
		* \brief This operation register d in the DistManager.
		*/
		void registerDist (Distribution* d);
	};
	
}

}

/**
 * \@}
*/

#endif

