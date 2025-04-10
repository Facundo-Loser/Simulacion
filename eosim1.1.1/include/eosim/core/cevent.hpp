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

#ifndef CEVENT_HPP_
#define CEVENT_HPP_


/** \ingroup modeling_group
 * \@{
*/
/** \class eosim::core::CEvent include\eosim\core\cevent.hpp <eosim/core/cevent.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  C Events
 
 * <p>This is the parent class of all C events. A CEvent (conditional event) only occur when the model meets
 * certain conditions (resources availability, queue positions, etc).</p>
 * <p>CEvent is an abstract class which represents a conditional event that is relevant to a system. CEvents are
 * stateless objects and Model’s attributes as well as BEvent.</p>
 * <p>To create a subclass of CEvent you must implement three methods:
 * <ul>
 *		<li>a constructor,</li>
 *		<li>a destructor,</li>
 *		<li>and CEvent::eventRoutine.</li>
 * </ul>
 * CEvents are very much like BEvents, the only difference is that BEvents occur at a certain time to a certain
 * group of entities. But, CEvents occur when its model meets certain conditions such as resources availability.
 * That’s why BEvent::eventRoutine is applied to an entity and CEvent::eventRoutine is applied to its model. 
 * <b>CEvents have to be registered using Model::registerCEvent;</b> an unregistered CEvent will not have any 
 * effect in its model, but it won't rise an error (simply it won't be executed).</p>
 * <p>All CEvents belong to a Model, they have the attribute CEvent::owner to have access to its model. This 
 * parameter appear in CEvent constructor and it must be called at the constructor of any subclass.</p>
 * <p>CEvent::eventRoutine defines every action taken in this particular point in time. CEvents acts over many
 * unspecific entities, and may change the state of the model. If one event creates or deletes an Entity, see
 * the rules decripted in the documentation of that class.</p>
*/


namespace eosim {

namespace core {

    class Model;    

	class CEvent {
	protected:
		Model& owner;
	public:
		/**
		* \brief The constructor creates a CEvent which belongs to the Model owner. 
		*/
		CEvent (Model& owner);
		/**
		* \brief The destructor of CEvent. 
		*/
		virtual ~CEvent ();
		/**
		* \brief This abstract operation brings an uniform interface to CEvents routines.
		* \note  In order to model an specific event, the programmer have to give an specific method to this operation. If the event needs to have access to its model, use the attribute owner. Keep in mind that CEvents acts to an specific model, not to an specific entity.
		*/
		virtual void eventRoutine () = 0;

	};
	
}

}

/**
 * \@}
*/

#endif

