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

#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include <string>
#include <map>
#include <utility>


/** \ingroup statics_group
 * \@{
*/
/** \class eosim::statics::Histogram include\eosim\statics\histogram.hpp <eosim/statics/histogram.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.1.0
 *  \date    2005
 *  \brief  Abstract Histogram

 * <p>This is the parent class of all Histograms. It contains the basics operations of all histograms but you 
 * can’t use it directly. Histograms store punctual values, but the pair (x1, y1) is logged and then the pair 
 * (x1, y2) is logged the histogram record the pair (x1, y1 + y2).</p>
*/


namespace eosim {

namespace core {
    class Model;
}

namespace statics {


	
	class Histogram {
    protected:
        double count,total,sosq;
        std::map< double, double > cell;
		std::pair< double, double > min;
		std::pair< double, double > max;
        std::string name;
        Histogram(std::string name);
		/**
		* \brief This is an auxiliary operation used to print histograms.
		
		* Basically the operations Histogram::table and Histogram::print are wrappers for this operation.
		*/
        std::string printH(unsigned int cantCell, bool graphic);
		/**
		* \brief This operations register x and y in the histogram. 
		*/
        void log(double x, double y);
    public:
		/**
		* \brief The destructor of Histogram.
		*/
        virtual ~Histogram();
		/**
		* \brief This operation erases every value registered in the histogram.
		*/
        void reset();
		/**
		* \brief This operation prints the histogram in the standard output. cantCell indicates how many bars have you histogram.
		*/
        void print(unsigned int cantCell);
		/**
		* \brief This operation prints the histogram in path file. cantCell indicates how many bars have you histogram.
		*/
        void print(unsigned int cantCell, const char* path);
		/**
		* \brief This operation prints a table with the values stored in the histogram in the standard output . cantCell indicates how many rows have you table.
		*/
        void table(unsigned int cantCell);
		/**
		* \brief This operation prints a table with the values stored in the histogram in path file.
		*/
        void table(unsigned int cantCell, const char* path);
		/**
		 * \brief This operation returns 1 if the histogram is empty. 
		*/
        bool empty();
		/**
		* \brief This operation returns the variance registered in the histogram.
		*/
        double getVariance();
		/**
		* \brief This operation returns the mean value registered in the histogram.
		*/
        double getMean();
		/**
		* \brief This operation returns the histogram’s name.
		*/
        std::string getName();
    };

}

}

/**
 * \@}
*/

#endif

