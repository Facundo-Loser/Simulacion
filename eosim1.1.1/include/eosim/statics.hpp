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

#ifndef STATICS_HPP_
#define STATICS_HPP_

#include <eosim/statics/histogram.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/statics/timeseries.hpp>
#include <eosim/statics/timeweighted.hpp>

/**
 * \defgroup statics_group Data Collectors
 * <br>

 * <p>Another important part of simulation software is output data collectors. They are used to collect data 
 * from simulation’s output parameters. Later, these data are analyzed statistically. The data collectors
 * provided by EOSimulator are histograms.</p> 
 * <p><b>Histograms store bidimentional data (x,y) in tables ordered uniquely by x, and are accumulated in the y.</b>
 * For example if (x1, y1) and (x1, y2) are logged (using the corresponding log operation) in the histogram, the
 * stored value is (x1, y1 + y2). This data collector also calculates the mean value and the standard deviation of
 * the collected data.</p>
 * <p>There are three kinds of histograms in EOSimulator, all of them subclases of eosim::statics::Histogram which
 * defines the behavior of every histogram in EOSimulator:
 * <ul>
 *		<li>eosim::statics::Observation: This histogram store observations; the number of times that the value x has
 * been measured in a variable,</li>
 *		<li>eosim::statics::TimeSeries: This histogram records the evolution of a variable over time; a serie of values
 * over time,</li>
 *		<li>eosim::statics::TimeWeighted; This histogram records the how much time has a variable sustained a given 
 * value.</li>
 * </ul>
 * </p>
 * <p>Besides of store data, histograms can be displayed in diferent formats:
 * <ul>
 *		<li>table: a table of values separeted by tabs using eosim::statics::Histogram::table;</li>
 *		<li>graphical: an horizontal asterix-bar graph with the values eosim::statics::Histogram::print.</li>
 * </ul>
 * Both formats could be written in the standard output or in a file.</p>
*/

#endif

