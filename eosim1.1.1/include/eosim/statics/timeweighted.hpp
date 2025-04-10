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

#ifndef TIMEWEIGHTER_HPP_
#define TIMEWEIGHTER_HPP_

#include <eosim/statics/histogram.hpp>

/** \ingroup statics_group
 * \@{
*/
/** \class eosim::statics::TimeWeighted include\eosim\statics\timeweighted.hpp <eosim/statics/timeweighted.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.1.0
 *  \date    2005
 *  \brief  Time Weighted Histogram
 
 * This kind of histogram shows the values reached by response variables, and the time these values sustain.
 * Basically it defines a <b>observed value vs. time observed</b> chart (how much time a variable sustained a given value throughout the simulation).
*/


namespace eosim {

namespace statics {

	class TimeWeighted: public Histogram {
	private:
		double lastTime;
		core::Model &m;
	public:
		/**
		* \brief The constructor of TimeWeighted; the kind of histogram is appended at the end of the name.
		* The model passed as an argument is the one which will be used to get the time values needed to log data in this histograms.
		*/
		TimeWeighted(std::string name, core::Model &m);
		/**
		* \brief This operation log a value in the histogram.
		*/
		void log(double v);
	};

}

}

/**
 * \@}
*/

#endif

