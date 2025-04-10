#include "events.hpp"
#include "repair.hpp"
#include "machine.hpp"

#include <iostream>

using namespace eosim::core;



EndWork::EndWork(eosim::core::Model& model): BEvent(endW, model) {}

EndWork::~EndWork() {}

void EndWork::eventRoutine(eosim::core::Entity* who) {
	Repair& r = (Repair&)owner;
    // una maquina se rompe y se la pone en la cola para remover sus partes defectuosas
	r.toRemove.push(who);
	std::cout << r.getSimTime() << "\tSe rompio la maquina " << ((Machine*)who)->getNumber() << '\n';
}


StartRemove::StartRemove(eosim::core::Model& model): CEvent(model) {}

StartRemove::~StartRemove() {}

void StartRemove::eventRoutine() {
	Repair& r = (Repair&)owner;
    // por cada maquina a la que se le deben quitar partes se busca un mecanico libre
	for(;!r.toRemove.empty() && r.mechanics.isAvailable(1);) {
        // se pone a trabar al mecanico
		r.mechanics.acquire(1);
		Machine* m = (Machine*)r.toRemove.pop();
        // se muestrea el tiempo de que se demora en remover las partes defectuosas
		double time = r.removal.sample();
        // como la distribucion es normal es necesario repetir la muestra hasta que se tenga un valor positivo
		for(; time < 0; time = r.removal.sample());
        // se agenda la finalizacion de la actividad
		r.schedule(time, m, endRv);
		std::cout << r.getSimTime() << "\tSe comenzo a remover las piezas de la maquina " << m->getNumber() << '\n';
	}
}


EndRemove::EndRemove(eosim::core::Model& model): BEvent(endRv, model) {}

EndRemove::~EndRemove() {}

void EndRemove::eventRoutine(eosim::core::Entity* who) {
	Repair& r = (Repair&)owner;
    // se toma la maquina a la que se le han removido las partes defecutosas y se la pone a reparar
	r.toRepair.push(who);
	std::cout << r.getSimTime() << "\tSe termino de remover las piezas de la maquina " << ((Machine*)who)->getNumber() << '\n';
}


StartRepair::StartRepair(eosim::core::Model& model): CEvent(model)  {}

StartRepair::~StartRepair() {}

void StartRepair::eventRoutine() {
	Repair& r = (Repair&)owner;
    // por cada maquina a reparar se busca que se tenga el equipo necesario para comenzar la reparacion
	for(;!r.toRepair.empty() && r.equipment.isAvailable(1);) {
		r.equipment.acquire(1);
		Machine* m = (Machine*)r.toRepair.pop();
        // se muestrea el tiempo de que se demora en repara la maquina
		double time = r.repair.sample();
        // como la distribucion es normal es necesario repetir la muestra hasta que se tenga un valor positivo
		for(; time < 0; time = r.repair.sample());
        // se agenda la finalizacion de la actividad
		r.schedule(time, m, endRp);
		std::cout << r.getSimTime() << "\tSe comenzo a reparar la maquina " << m->getNumber() << '\n';
	}
}


EndRepair::EndRepair(eosim::core::Model& model): BEvent(endRp, model) {}

EndRepair::~EndRepair() {}

void EndRepair::eventRoutine(eosim::core::Entity* who) {
    // una vez terminda la reparacion se deja libre al mecanico y las herramientas que este utilizo
	Repair& r = (Repair&)owner;
	r.mechanics.returnBin(1);
	r.equipment.returnBin(1);
    // se agenda la nueva rotura de la maquina
	r.schedule(r.breakDown.sample(), who, endW);
	std::cout << r.getSimTime() << "\tSe termino de reparar la maquina " << ((Machine*)who)->getNumber() << '\n';
}
