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

#ifndef CORE_HPP_
#define CORE_HPP_

#include <eosim/core/bcalendar.hpp>
#include <eosim/core/bevent.hpp>
#include <eosim/core/bin.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/core/ccalendar.hpp>
#include <eosim/core/cevent.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/core/experiment.hpp>
#include <eosim/core/model.hpp>
#include <eosim/core/nonrenewable.hpp>
#include <eosim/core/renewable.hpp>


/**
 * \defgroup modeling_group Modeling Clases
 
 * <p>EOSimulator is divided in four modules: Core, Dist, Statics and Utils. In order to build
 * a simulation, you have to implement subclasses of Core’s abstract classes. Those abstract classes are Model,
 * BEvent, CEvent, Entity and EntityComp (if needed). You may use collections defined in Utils, pseudo-random 
 * number generators or distributions from Dist or output data collector from Statics.</p>
 * <h3>Model Building</h3>
 * <p> This is a main activity in the process of simulating a system. EOSimulator provides the user with five 
 * abstract classes that have to be derived properly to build a specific system. For most models you have to 
 * implement:
 * <ul>
 *		<li>one subclass of eosim::core::Model,</li>
 *		<li>one subclass of eosim::core::BEvent for each bounded event in your system,</li>
 *		<li>one subclass of eosim::core::CEvent for each conditional event in your system if you are using three
			phase approach,</li>
 *		<li>one subclass of eosim::core::Entity for each kind of entity in your system</li>
 *		<li>as many eosim::core::EntityComp subclasses as priority queues your system have.</li>
 * </ul>
 * </p>
 * <p>Although, there are some implementation issues that you must pay attention while modeling your system with 
 * EOSimulator, otherwise it won’t run properly or it won’t run at all. If you don’t follow these instructions and
 * try to execute a simulation, it might abort displaying an error message.</p>
*/

/**
 * \defgroup simuling_group Running Simulations
 * <br>
 * <p>In this module we will learn how to simulate a model using the facilities provided by the library. Besides,
 * we will describe the errors detected by EOSimulator.</p>
 * <h3>Running a simulation</h3>
 * <p>The process of simulate models is not as trivial as it appears. It is very important to design set of runs 
 * varying seeds in those streams used by the model. Otherwise all the experimentation done with the model will
 * not be statistically valid. Remember, one simulation run is not enough to draw any conclusions about a system.</p>
 * Luckily, EOSimulator makes this running process quite easy. The core::Experiment class handles the execution of
 * a simulation. It contains a calendar, an executive and the streams.</p>
 * <h4>Making one run</h4>
 * <p>To run a simulation you have to write a program. In this program, create an instance of your system model 
 * and an experiment. Then connect them with the operation core::Model::connectToExp. In that operation, the model
 * is initialized (with the operation core::Model::init) and connected to the experiment. Then use Experiment::run
 * to run the simulation. This operation makes the initial schedules in the model (core::Model::doInitialSchedules)
 * and simulates the model. For example:
 * <br>
 * <br>
 * <code class="fragment">
 * using namespace eosim::core; <br>
 * int main () {<br>
 * &nbsp;&nbsp;&nbsp;&nbsp; Model my_model;<br>
 * &nbsp;&nbsp;&nbsp;&nbsp; Experiment exp;<br>
 * &nbsp;&nbsp;&nbsp;&nbsp; m.connectToExp(e); <code class="comment">// the experiment is connected to the model</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp; e.run(5); <code class="comment">// we simulate for 5 time units</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp; <code class="comment">// do some report</code><br>
 * }</code>
 * <br></p>
 * <p>After the simulation is finished generally the data collected is reported. For more information see
 * \ref statics_group "Data Collectors".</p>
 * <h4>Making multiple runs</h4>
 * <p>As we said above, one run is not enough to draw conclusions. So in order to make more runs, after the
 * simulation is finished, create a new model and experiment. Then connect them and set a new seed in the 
 * experiment using core::Experiment::setSeed. This operation change the seed of every registered distribution in
 * the model, and it let you have a different run (the default seed is 251182). Finally, run the simulation
 * (core::Experiment::run).</p>
 * <br>
 * <br>
 * <code class="fragment">
 * using namespace eosim::core; <br>
 * int main () {<br>
 * &nbsp;&nbsp;&nbsp;&nbsp; for(int i = 0; i < 4; i++) { <code class="comment">// we will make 4 runs</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Model my_model; <code class="comment">// a new Model is created for every iteration</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Experiment exp; <code class="comment">// a new Experiment is created for every iteration</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; m.connectToExp(e); <code class="comment">// the experiment is connected to the model</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; e.run(5); <code class="comment">// we simulate for 5 time units</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <code class="comment">// do some report</code><br>
 * &nbsp;&nbsp;&nbsp;&nbsp; }<br>
 * }</code>
 * <br>
 * <p>But why we didn’t keep the old experiment and model? Another possibility may be keep them, set a new seed
 * and simulate again. This is possible because Experiment doesn’t reset the simulation time. Check if the system
 * you are modeling let you do that.</p>
 * <p>We could create a new model and connect it the old experiment. But, in the old experiment there may be some
 * entities which are scheduled to arrive or to leave the system. If an entity is schedule to leave, it may return
 * some units of bins causing errors in the output or even aborts the simulation. If we make a new experiment and
 * connect it with an old model, the queues of the model will full of entities. In this case the model has already
 * started (and if it can reach steady state) it may be stable. But, the clocks of the entities waiting in a queue
 * have not been updated , so they still contain older values and cause errors collecting waiting times.</p>
*/

#endif

