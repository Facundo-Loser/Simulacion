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

#ifndef OBSERVATION_HPP_
#define OBSERVATION_HPP_

#include <eosim/statics/histogram.hpp>

/** \ingroup statics_group
 * \@{
*/
/** \class eosim::statics::Observation include\eosim\statics\observation.hpp <eosim/statics/observation.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.1.0
 *  \date    2005
 *  \brief  Observation Histogram
 
 * This is histograms is used to store values of discrete observations, such us waitting times.
 * Basically it defines a <b>observed value vs. quantity of observations</b> chart (counts the number of times a value was observed).
*/


namespace eosim {

namespace statics {
	class Observation: public Histogram {
	public:
		/**
		* \brief The constructor of Observation; the kind of histogram is appended at the end of the name.
		*/
		Observation(std::string name);
		/**
		* \brief This operation log a value in the histogram.
		*/
		void log(double value);
	};

}

}

/**
 * \@}
*/

#endif

