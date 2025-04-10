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

#include <eosim/core/model.hpp>
#include <eosim/statics/histogram.hpp>
#include <eosim/core/bevent.hpp>
#include <eosim/core/cevent.hpp>
#include <eosim/core/experiment.hpp>
#include <eosim/dist/distribution.hpp>
#include <cassert>

using namespace eosim::core;
using namespace eosim::dist;
using namespace eosim::utils;
using namespace eosim::statics;


Model::Model(): exp(0) {}

Model::~Model() {}

void Model::connectToExp (Experiment *exp) {
	/**
	* \warning The model must not be connected to an experiment.
	*/
    assert(exp != 0 && "Model::connectToExp: Error connecting the model to an experiment");
    this->exp = exp;
    exp->setModel(this);
    init();
	doInitialSchedules();
}

void Model::registerBEvent (BEvent* bEv) {
	/**
	* \note If a BEvent is not register to its model, entity will not be scheduled to that event. 
	*/
    /**
	* \warning The model must be connected to an experiment and bEv must be not null.
	*/
    assert(exp != 0 && bEv != 0 && "Model::registerBEvent: Error registering a BEvent");
    bEvs.put(bEv);
}

void Model::registerCEvent (CEvent *cEv) {
	/**
	* \note If a CEvent is not register into its model, it won’t be executed during the simulation.
	*/
    /**
	* \warning The model must be connected to an experiment and cEv must be not null.
	*/
    assert(exp != 0 && cEv != 0 && "Model::registerCEvent: Error registering a CEvent");
    exp->registerCEvent(cEv);
}

void Model::registerDist (Distribution* dist) {
	/**
	* \note If a Distribution is not register into its model, it’s seed won’t be changed by the operation Experiment::setSeed.
	*/
    /**
	* \warning The model must be connected to an experiment and dist must be not null.
	*/
    assert(exp != 0 && dist != 0 && "Model::registerDist: Error registering a Distribution");
    exp->registerDist(dist);
}

void Model::schedule (double offset, Entity* who, std::string what) {
	/**
	* \warning The model must be connected to an experiment, who must be not null, and there must be a bEvent registered with the name what.
	*/
	assert(exp != 0 && who != 0 && offset >= 0 && "Model::schedule: Error scheduling an Entity");
    BEvent* b = bEvs[what];
    who->setBEvent(b);
    exp->schedule (offset, who);
}

double Model::getSimTime() {
	/**
	* \warning The model must be connected to an experiment.
	*/
    assert(exp != 0 && "Model::getSimTime: Error getting the actual simulation time");
    return exp->getSimTime();
}

