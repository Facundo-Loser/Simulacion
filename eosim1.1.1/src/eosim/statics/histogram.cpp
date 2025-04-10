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

#include <eosim/statics/histogram.hpp>
#include <eosim/core/model.hpp>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>


using namespace eosim::statics;
using namespace std;

const int largoLinea = 80;
const int largoDouble = 8;
const int largoAster = largoLinea - 2*(largoDouble + 2) - 1;

Histogram::Histogram(string name): count(0), total(0), sosq(0), name(name) {
}

void Histogram::log(double x, double y) {
	/**
	* \note The histogram store punctual values, but if an two pairs with the same x-value are logged, the pair stored records the sum of y-values.
	*/
	if (cell.find(x) == cell.end()) {
		cell[x] = 0;
	}
	cell[x] += y;
	count += y;
    total += y*x;
    sosq += x*x*y;

	if (cell.size() == 1) {
		max.first = x;
		min.first = x;
	} else {
		if (x > max.first || x < min.first) {
			if (x > max.first)
				max.first = x;
			else
				min.first = x;
		}
	}
}

string printBar(double bar, double maxBar) {
	ostringstream out;
	out << ' ';
	int lenBar = (int)floor((bar / maxBar) * (double)largoAster);
	for (int k = 0; k < lenBar; k++) 
		out << '*';
	for (int k = 0; k < largoAster - lenBar; k++) 
		out << ' ';
	return out.str();
}

string Histogram::printH(unsigned int cantCell, bool graphics) {
	/**
	* \note This is an auxiliar operation of Histogram::table and Histogram::print.
	* This an expensive operation, because it has to go through all logged observations. 
	*/
	ostringstream out;
	if (cell.size() != 0) {
		double m = getMean();
		double v = getVariance();

		out << name << "\n";
		out << "procesed = " << count << "\n";
		out << "mean = " << m << "\tvariance = " << v << "\tsd = " << sqrt(v) << "\n";

		if (cantCell > 0) {
			/**
			* \note If cantCell is less or equal than zero, the values stored in the histogram won't be shown.
			*/
			double width = (max.first - min.first) / (double)cantCell;
			vector<double> aux(cantCell, 0.0);

			min.second = cell.begin()->second;
			max.second = min.second;
			unsigned int i = 0;

			/**
			 * \bug There was a bug when the histogram is printed, more specifically when an auxiliar vector (used to print the histogram)
			 * is assigned. This bug is corrected.
			*/
			for (map<double, double>::const_iterator it = cell.begin(); it != cell.end(); it++){
				if ((it->first - min.first) > (i + 1) * width) {
					if (aux[i] > max.second || aux[i] < min.second) {
						if (aux[i] > max.second)
							max.second = aux[i];
						else
							min.second = aux[i];
					}
					i = (unsigned int) floor ((it->first - min.first) / width);
					i = i >= aux.size() ? aux.size() - 1: i;
				}
				aux[i] += it->second;
			}

			out << "minX = " << min.first << "\tmaxX = " << max.first << "\n";
			out << "minY = " << min.second << "\tmaxY = " << max.second << "\n\n";

			for (i = 0; i < cantCell; i++){
				out << setw(largoDouble) << min.first + width * i;
				if (graphics) {
					out << printBar(aux[i], max.second);
				}
				out << "  ";
				out << setw(largoDouble) << aux[i];
				out << "\n";
			}
		}
	} else {
		/**
		* \note If the histogram is empty no data will be shown.
		*/
		out << "No Data available\n";
	}
    return out.str();
}

Histogram::~Histogram() {}

void Histogram::reset() {
    count = total = sosq = 0;
	cell.erase(cell.begin(), cell.end());
}

void Histogram::print(unsigned int cantCell) {
	cout << printH(cantCell, 1);
}

void Histogram::print(unsigned int cantCell, const char* path) {
    ofstream out (path);
    out << printH(cantCell, 1);
}

void Histogram::table(unsigned int cantCell) {
    cout << printH(cantCell, 0);
}

void Histogram::table(unsigned int cantCell, const char* path) {
    ofstream out (path);
    out << printH(cantCell, 0);
}

bool Histogram::empty() {
	return count > 0;
}

double Histogram::getVariance() {
	/**
	* \note If the histogram is empty, the variance returned is 0.
	*/
	return (count > 1) ? (sosq-total*getMean())/(count-1): 0;
}

double Histogram::getMean() { 
	/**
	* \note If the histogram is empty, the variance returned is 0.
	*/
	return count != 0 ? total / count : 0;
}

string Histogram::getName() { 
    return name;
}

