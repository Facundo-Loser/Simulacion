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

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <eosim/utils/beventmap.hpp>
#include <eosim/utils/ceventvector.hpp>
#include <eosim/utils/distvector.hpp>
#include <eosim/utils/entityqueue.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/utils/entityqueuelifo.hpp>
#include <eosim/utils/entityqueueordered.hpp>

/**
 * \defgroup utils_group Collections
 * <br>
 * <p>Another common feature is the access methods. All containers provide random access to its elements. They are
 * indexed by an int (CEventVector, DistVector and EntityQueue) or by a key (BEventMap). For example:
 * <br>
 * <br>
 * <code class="fragment">
 * Entity* ent = queue[5]; <code class="comment">//gets the 5º element in queue</code><br>
 * BEvent* bev = map[“llegada”]; <code class="comment">//gets the BEvent whose name is “llegada” from bev</code>
 * </code>
 * <br>
 * <br></p>
 * <p>Also you can remove elements by giving the proper type of index. In case of indexing outside the container,
 * EOSimulator immediately aborts displaying an error message.</p>
 * <p>All containers are created empty and ready to use, but when it comes to destructors things are a little 
 * bit complicated. As we said above, most model attributes could be created statically or dynamically but is 
 * responsibility of the user to delete them. On the other hand, entities must be created dynamically and 
 * EOSimulator deletes them. EntityQueue and its subclasses delete every pointer they store, because they assumed
 * that all entities are created dynamically. CEventVector, DistVector and BEventMap don’t make any assumptions
 * so the programmer takes charge. For more information about container see [4].</p>
*/

#endif

