#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalSimple::HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								pF(*this),
								sP(*this),
								arribos(MT19937, tasaArribos),
								estadia(MT19937, tiempoEstadia),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this),
								uCamas("Utilizacion prom servidor", *this),
								usoRoboCamas(MT19937, 120.0, 2.0),
								rC(*this),
								cantVecesRobo(0),
								robar(true) {}


HospitalSimple::~HospitalSimple() {}

void HospitalSimple::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);
	registerBEvent(&rC);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);

	registerDist(&usoRoboCamas);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
	schedule(0.0, new Entity(), robaCama);
}

