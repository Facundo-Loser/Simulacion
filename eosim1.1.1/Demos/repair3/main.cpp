#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "repair.hpp"
#include <iostream>
#include <string>

using namespace eosim::core;

const unsigned int repeticiones = 4;

int main() {
    std::string s;
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        Repair m(cantMech, cantEq, cantMach, breakDownTime, removalMean, removalSD, repairMean, repairSD);
		Experiment e;
		std::cout << "Arranco ...\n";
		m.connectToExp(&e);
		e.setSeed((unsigned long) i + 129);
		e.run(8*60);
        std::cout << "Termine ...\n\n\n";
        std::cin >> s;
	}
	return 0;
}
