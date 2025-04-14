#include "autoserviciosimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
#include <eosim/dist/normaldist.hpp>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

AutoservicioSimple::AutoservicioSimple(double tasaArribos, double tiempoEstadia):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								arribos(MT19937, tasaArribos),
								estadia(MT19937, 25.0, 1.5),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this) {}

AutoservicioSimple::~AutoservicioSimple() {}

void AutoservicioSimple::init() {
	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void AutoservicioSimple::doInitialSchedules() {
}
