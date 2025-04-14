#include "autoservicio.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

Autoservicio::Autoservicio(unsigned int cantMaquinasCafe, double tasaArribos, double tiempoEstadia):
    tasaArribos(tasaArribos),
    tiempoEstadia(tiempoEstadia),
    cF(*this),
    iS(*this),
    sC(*this),
    arribos(MT19937, tasaArribos),
    estadia(MT19937, 27, 1.5),
    maquinaCafe(1, 1),
    tEspera("Tiempos de Espera"),
    lCola("Largos Medios de Colas", *this),
    umaquinaCafe("Utilizacion prom servidor", *this) {}

Autoservicio::~Autoservicio() {}

void Autoservicio::init() {
    // regsitro los eventos
    registerBEvent(&cF);
    registerCEvent(&iS);
    registerBEvent(&sC);

    // registro las distribuciones
    registerDist(&arribos);
    registerDist(&estadia);
}

void Autoservicio::doInitialSchedules() {
    schedule(0.0, new eosim::core::Entity(), clienteF);
}
