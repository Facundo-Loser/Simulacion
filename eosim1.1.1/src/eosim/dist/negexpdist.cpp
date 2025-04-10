#include <eosim/dist/negexpdist.hpp>
#include <cmath>

using namespace eosim::dist;


NegexpDist::NegexpDist(GenType gen, double m): Distribution(gen), m(m) {} 

NegexpDist::~NegexpDist() {}

double NegexpDist::sample() {
	/**
	* \note The method used for sampling is the inverse transform method.
	*/
    return -log (generator->nextDouble())* m;
}

