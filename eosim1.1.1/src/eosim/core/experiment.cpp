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

#include <eosim/core/experiment.hpp>
#include <eosim/core/model.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <cassert>

using namespace eosim::core;
using namespace eosim::dist;


Experiment::Experiment (): running(0), distMan(MT19937), currModel(0) {}

Experiment::~Experiment() {
/**
* \warning  It is assumed that all entities were created dynamically, so every entity stored is deleted. 
*/
}

void Experiment::run (double simTime) {
	/**
	* \note Experiment could simulate any Model which use event method or three phase approach. The simulation actual time is not reseted after a run, the first run starts at zero, but next runs starts when the previous finished.
	*/
    /**
	* \warning  The experiment must be connected to a model.
	*/
	assert(currModel != 0 && "Experiment::run: Error running a simulation");
    running = 1;
    bCal.setEndTime(simTime);
    for (; (running); running = bCal.isStopped()) {
        bCal.bPhase();
        cCal.cPhase();
    }
    running = 0;
}

void Experiment::setModel (Model* model) {
	/**
	* \note This operation is automatically invoked by EOSimulator, the programmer shouldn’t use it.
	*/
    /**
	* \warning The model must be not null.
	*/
	assert(model != 0 && "Experiment::setModel: Error setting a Model");
    currModel = model;
    setSeed(251182);
}

void Experiment::schedule (double offset, Entity* who) {
	/**
	* \note It is assumed that who knows to which event it is scheduled.
	*/
    bCal.schedule(offset, who);
}

void Experiment::setSeed (unsigned long seed) {
	/**
	* \note To obtain different runs, set different seeds in the experiment.
	*/
    /**
	* \warning The experiment must be connected to a model.
	*/
    assert(currModel != 0 && "Experiment::setSeed: Error assigning a new seed to the experiment");
    distMan.setSeed(seed);
}

void Experiment::registerDist (Distribution* dist) {
	/**
	* \note The programmer shouldn’t invoke this operation because it’s invoked automatically by EOSimulator.
	*/
    /**
	* \warning The experiment must be connected to a model.
	*/
    assert(currModel != 0 && "Experiment::registerDist: Error registering a Distribution");
    distMan.registerDist(dist);
}

void Experiment::registerCEvent (CEvent* cEv) {
	/**
	* \note The programmer shouldn’t invoke this operation because it’s invoked automatically by EOSimulator.
	*/
    /**
	* \warning The experiment must be connected to a model.
	*/
    assert(currModel != 0 && "Experiment::registerCEvent: Error registering a CEvent");
    cCal.registerCEvent(cEv);
}

double Experiment::getSimTime() {
    return bCal.getSimTime();
}

