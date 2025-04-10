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

#include <eosim/core/bcalendar.hpp>

using namespace eosim::core;
using namespace eosim::utils;


class ClockComp: public EntityComp {
public:
    ClockComp() {}
    ~ClockComp() {}
    bool compare (Entity* e1, Entity* e2) { return e1->getClock() < e2->getClock(); }
    
};

ClockComp c;

BCalendar::BCalendar ():  simTime(0), endSim(0), ents(EntityQueueOrdered(&c)) {
}

BCalendar::~BCalendar () {
/**
* \warning  It is assumed that all the entities had been created dynamically, so every entity stored is deleted.
*/
}

void BCalendar::bPhase () {
	/**
	* First, the simulation time is advanced to the time of the first scheduled event.
	*/
	simTime = ents[0]->getClock();
	/**
	*  Then BCalendar process all events which are scheduled at the actual simulation time.
	*/
    for (; simTime <= endSim && !ents.empty() && ents[0]->getClock() == simTime;) {
        Entity* temp = ents.pop();
        temp->processEvent();
    }    
}

bool BCalendar::isStopped() {
	return simTime <= endSim && !ents.empty();
}

void BCalendar::schedule (double offset, Entity* who) {
	who->setClock(simTime + offset);
    ents.push(who);
}

void BCalendar::setEndTime (double when) {
	endSim = when;
}

double BCalendar::getSimTime() {
	return simTime;
}

