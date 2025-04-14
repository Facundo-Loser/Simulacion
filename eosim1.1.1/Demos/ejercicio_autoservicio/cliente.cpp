#include "autoservicio.hpp"
#include "cliente.hpp"
#include <iostream>

// PLANIFICADO
ClienteFeeder::ClienteFeeder(eosim::core::Model& model) : BEvent(clienteF, model) {}

ClienteFeeder::~ClienteFeeder() {}

void ClienteFeeder::eventRoutine(eosim::core::Entity* who) {
    std::cout << "llego un cliente en " << who->getClock() << "\n";
    Autoservicio& a = dynamic_cast<Autoservicio&>(owner);

    // poner el nuevo cliente en cola
    a.lCola.log(a.cola.size());
    a.cola.push(who);

    // genero el prox arribo
    a.schedule(a.arribos.sample(), new eosim::core::Entity(), clienteF);
}

// CONDICIONAL
InicioServicio::InicioServicio(eosim::core::Model& model) : CEvent(model) {}

InicioServicio::~InicioServicio() {}

void InicioServicio::eventRoutine() {
    Autoservicio& a = dynamic_cast<Autoservicio&>(owner);
    while (!a.cola.empty() && a.maquinaCafe.isAvailable(1)) {
        // admitir el prox cliente de la cola
        eosim::core::Entity* ent = a.cola.pop();

        // adquirir recurso
        a.umaquinaCafe.log(a.maquinaCafe.getMax() - a.maquinaCafe.getQuantity()); // logeo para utilizacion maq cafe
        a.maquinaCafe.acquire(1);

        a.tEspera.log(a.getSimTime() - ent->getClock()); // logeo para espera en cola
        std::cout << "Un cliente comenzo a  usar a maq de cafe" << a.getSimTime() << std::endl;

        // setear el tiempo para cuando sale
        a.schedule(a.estadia.sample(), ent, salidaC);
    }
}

// PLANIFICADO
SalidaCliente::SalidaCliente(eosim::core::Model& model) : BEvent(salidaC, model) {}

SalidaCliente::~SalidaCliente() {}

void SalidaCliente::eventRoutine(eosim::core::Entity* who) {
    std::cout << "un cliente se retira en " << who->getClock() << "\n";
    Autoservicio& a = dynamic_cast<Autoservicio&>(owner);

    a.umaquinaCafe.log(a.maquinaCafe.getMax() - a.maquinaCafe.getQuantity()); // logeo para utilizacion maq cafe

    a.maquinaCafe.returnBin(1);
    delete who;
}
