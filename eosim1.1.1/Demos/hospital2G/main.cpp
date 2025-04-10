#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalsimpleg.hpp"
#include "constantes.hpp"

#include <iostream>
#include <fstream>

const unsigned int repeticiones = 1;


int main () {
	std::string s;
    using namespace eosim::core;
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        HospitalSimpleG m(cantCamas, tasaArribos, tiempoEstadia);
        Experiment e;
        std::cout << "Arranco ...\n";
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(720.0);
        std::cout << "Termine ...\n\n\n";
        std::cin >> s;
    }
    return 0;
}

