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

#include <eosim/statics/timeseries.hpp>
#include <eosim/core/model.hpp>
#include <cassert>

using namespace eosim::statics;

TimeSeries::TimeSeries(std::string name, eosim::core::Model &m) : m(m), Histogram(name + " - Time Series Histogram") {}

void TimeSeries::log(double value) {
	/**
	 * \note The value is logged with the actual simulation time.
	 * Remember that histograms acummulate values with the same x's.
	*/
	Histogram::log(m.getSimTime(), value);
}

