#ifndef POISSONDIST_HPP_
#define POISSONDIST_HPP_

#include <eosim/dist/distribution.hpp>

/** \ingroup dist_group
 * \@{
*/
/** \class eosim::dist::PoissonDist include\eosim\dist\poissondist.hpp <eosim/dist/poissondist.hpp>
 *  \author Sebastián Alaggia
 *  \version 1.0.1
 *  \date    2005
 *  \brief  Poisson Distribution
 
 * This class sample values from a Poisson distribution.
*/


namespace eosim {
	
namespace dist {

	class PoissonDist: public Distribution {
	private:
		double m;
	public:
		/**
		* \brief The constructor creates a PoissonDist with parameter m and whose generator’s type is gen.
		*/
		PoissonDist (GenType gen, double m);
		/**
		* \brief The destructor of PoissonDist.
		*/
		~PoissonDist ();
		/**
		* \brief This operation samples a value the distribution.
		*/
		double sample ();
	};

}

}

/**
 * \@}
*/

#endif

