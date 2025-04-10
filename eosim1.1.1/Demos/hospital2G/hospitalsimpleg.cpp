#include "hospitalsimpleg.hpp"
#include "pacienteg.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;
using namespace eosim::graphic;

using namespace std;

HospitalSimpleG::HospitalSimpleG(unsigned int cantCamas, double tasaArribos, double tiempoEstadia):
	tasaArribos(tasaArribos), tiempoEstadia(tiempoEstadia), pF(*this), sP(*this), mP(*this), rG(*this, disp), disp(800,600),
	pacienteIcon(32,50), camaIcon(50,55), filaEspera(358,70), puertaEntrada(517,70), puertaSalida(369,418),
	salida(369,600), camaIzq(67,267), arribos(MT19937, tasaArribos), estadia(MT19937, tiempoEstadia),
	camasBin(cantCamas, cantCamas)
{
	disp.setSpeed(0.02);
	double distEntreCamas = (disp.width() - 2 * camaIzq.first - camaIcon.first) / (cantCamas - 1);
	for (unsigned int i = 0; i < cantCamas; i++) {
		pair<double, double> position(camaIzq.first + distEntreCamas * i, camaIzq.second);
        // el ejemplo esta pensado para correr desde el directorio bin
		camaStruct c(disp,"../images/cama.png", position);
		c.libre = 1;
		camas.push_back(c);
	}
}

HospitalSimpleG::~HospitalSimpleG() {}

void HospitalSimpleG::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);
	registerBEvent(&mP);

	// registro los eventos C
	registerCEvent(&rG);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void HospitalSimpleG::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new PacienteG(disp, filaEspera.first, filaEspera.second), pacienteFG);
	// pongo los primeros detalles de la simulacion grafica
	// el ejemplo esta pensado para correr desde el directorio bin
	disp.setBackground("../images/fondo.png");
}

