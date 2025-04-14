#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include <iostream>
#include <fstream>

#include "cliente.hpp"
#include "autoservicio.hpp"

const unsigned int repeticiones = 4;

unsigned int cantMaquinas = 1;
double tasaArribos = 1.0 / 30.0;

int main() {
    std::string s;
    using namespace eosim::core;
    for (int i = 0; i < repeticiones; i++) {
        Autoservicio m(cantMaquinas, tasaArribos, 27.0);
        Experiment e;
        std::cout << "Comienza la Simulacion!" << std::endl;
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(1000.0);
        std::cout << "Termina la Simulacion!" << std::endl;
        m.lCola.print(10);
		std::cout << '\n';
		m.tEspera.print(52);
		std::cout << '\n';
		m.umaquinaCafe.print(10);
		std::cin >> s;
    }
    return 0;
}
