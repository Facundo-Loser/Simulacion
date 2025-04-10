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

#ifndef TIMESERIES_HPP_
#define TIMESERIES_HPP_

#include <eosim/statics/histogram.hpp>
#include <eosim/core/model.hpp>

/** \ingroup statics_group
 * \@{
*/
/** \class eosim::statics::TimeSeries include\eosim\statics\timeseries.hpp <eosim/statics/timeseries.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.1.0
 *  \date    2005
 *  \brief  Time Series Histogram
 
 * This kind of histogram shows the trends in response variables over time.
 * Basically it defines a <b>time vs. variable</b> chart (which match the evolution of the variable over time).
*/


namespace eosim {

namespace statics {

	class TimeSeries: public Histogram {
	private:
		core::Model &m;
	public:
		/**
		* \brief The constructor of TimeSeries; the kind of histogram is appended at the end of the name.
		* The model passed as an argument is the one which will be used to get the time values needed to log data in this histograms.
		*/
		TimeSeries(std::string name, core::Model &m);
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

