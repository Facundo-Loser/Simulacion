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

#include <eosim/graphic/refreshgraphic.hpp>
#include <eosim/core/model.hpp>
#include <sstream>

using namespace std;
using namespace eosim::core;
using namespace eosim::graphic;

RefreshGraphic::RefreshGraphic(Model& model, Display& disp): CEvent(model), d(disp), lastTime(0) {}

RefreshGraphic::~RefreshGraphic() {}

void RefreshGraphic::eventRoutine() {
	double actTime = owner.getSimTime();
	ostringstream os;
	/**
	* \note This operation will show the simulation time in the title of the Display window. For that it uses the function
	* Display::setTitle.
	*/
	os << "Simulation Time = " << actTime;
	d.setTitle(os.str().c_str());
	d.advance(actTime - lastTime);
	lastTime = actTime;
}

