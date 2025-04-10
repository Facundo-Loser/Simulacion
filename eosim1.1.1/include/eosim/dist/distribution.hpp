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

#ifndef DISTRIBUTION_HPP_
#define DISTRIBUTION_HPP_

#include <eosim/dist/numbergenerator.hpp>

/** \ingroup dist_group
 * \@{
*/
/** \class eosim::dist::Distribution include\eosim\dist\distribution.hpp <eosim/dist/distribution.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Distribution abstract class
 
 * <p>Pseudo-random number generators and distribution play a critical roll in computer simulations. Good
 * generators ensure randomness between runs. So every simulation library must provide these facilities. 
 * EoSimulator implements some of the most common distributions and provides one generator, but its design allows
 * more than one generator.</p>
 * <p>EoSimulator has no fixed number of streams. When a distribution is created, a new generator of user defined
 * type is assigned to it. The generator’s type is defined by a GenType label (GenType is declared together with
 * the NumberGenerator interface). The generator is a Distribution’s private attribute. For example:
 * <br>
 * <br>
 * <code class="fragment">
 * NegExpDist my_dist(MT19937, lambda); <code class="comment">// this is a Negative Exponencial Distribution with rate lambda, created using the generator Mt19937</code><br>
 * </code>
 * <br>
 * <br></p>
 * <p>To get a sampled value from a distribution, invoke the operation Distribution::sample on any Distribution’s
 * subclass:
 * <ul>
 *		<li>LogNormalDist: LogNormal Distribution,</li>
 *		<li>NegexpDist: Negative Exponencia Distribution,</li>
 *		<li>NormalDist: Normal Distribution,</li>
 *		<li>PoissonDist: Poisson Distribution,</li>
 *		<li>UniformDist: Uniform Distribution,</li>
 *		<li>or any other user subclass.</li>
 * </ul></p>
 * <p>You can also change the generator’s seed with the operation Distribution::setSeed. EoSimulator doesn’t support
 * antithetic streams, but it can be easily implemented.</p>
*/

namespace eosim {
	
namespace core {
    class Model;
}

namespace dist {

	class Distribution {
	protected:
		NumberGenerator *generator;
	public:
		/**
		* \brief The constructor creates a Distribution whose generator’s type is gen.
		*/
		Distribution (GenType gen);
		/**
		* \brief The destructor of Distribution.
		*/
		virtual ~Distribution ();
		/**
		* \brief This abstract operation is redefine in concrete distributions and returns a sampled value.
		*/
		virtual double sample () = 0;
		/**
		* \brief This operation sets a new seed in the distribution’s number generator.
		*/
		void setSeed (unsigned long seed);
	};

}

}

/**
 * \@}
*/

#endif

