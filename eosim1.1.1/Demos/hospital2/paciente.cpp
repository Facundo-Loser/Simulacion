#include "paciente.hpp"
#include "hospitalsimple.hpp"
#include <iostream>
using namespace eosim::core;



// en el constructor se utiliza el identificador definido en paciente.hpp
// en el constructor se utiliza el identificador definido en pacientefeeder.hpp
PacienteFeeder::PacienteFeeder(Model& model): BEvent(pacienteF, model) {}

PacienteFeeder::~PacienteFeeder() {}

void PacienteFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	std::cout << "llego un paciente en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
	if (h.camas.isAvailable(1)) {
        // logeo para utilizacion de camas
        h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());
		h.camas.acquire(1);
		std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
		h.tEspera.log(h.getSimTime() - who->getClock());
		h.schedule(h.estadia.sample(), who, salidaP);
	}
	else {
        // se acumulan datos en los histogramas
        h.lCola.log(h.cola.size());
		// se pone al paciente recien llegado en la cola
		h.cola.push(who);
	}
    // se agenda el arribo del un nuevo paciente
	h.schedule(h.arribos.sample(), new Entity(), pacienteF);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
SalidaPaciente::SalidaPaciente(Model& model): BEvent(salidaP, model) {}

SalidaPaciente::~SalidaPaciente() {}

void SalidaPaciente::eventRoutine(Entity* who) {
	// se informa la salida de un paciente
	std::cout << "un paciente se retira en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);

	// logeo para utilizacion de camas
        h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());

	// se retorna la cama que el paciente ocupaba
	h.camas.returnBin(1);
	if (!h.cola.empty()) {

        // logeo para utilizacion de camas
        h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());

		h.camas.acquire(1);
		std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
        h.lCola.log(h.cola.size());
		Entity* ent = h.cola.pop();
		h.tEspera.log(h.getSimTime() - ent->getClock());
		h.schedule(h.estadia.sample(), ent, salidaP);
	}
	// se elimina al paciente del sistema
	delete who;
}


RobaCamas::RobaCamas(Model& model): BEvent(robaCama, model) {}

RobaCamas::~RobaCamas() {}

void RobaCamas::eventRoutine(Entity* who) {
    HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);

    if (h.robar) {
        // robar 2 camas
        // primero chequear que ahya 2 camas disponibles para robar
        if (h.camas.isAvailable(2)) {
            h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());
            h.camas.acquire(2);
            std::cout << "Se robaron 2 camas**************************" << std::endl;
            h.cantVecesRobo++;
            h.robar = false; // la prox vez le toca devolver

            // genero el tiempo que va a retener las camas
            double tiempoDeRobo = h.usoRoboCamas.sample();
            // agendo el prox evento (en este caso devolver las camas)
            h.schedule(tiempoDeRobo, who, robaCama);
        } else {
            // no hay camas disponibles -> intento robar de nuevo en 10.0
            std::cout << "No se pudieron robar 2 camas**************************" << std::endl;
            h.schedule(10.0, who, robaCama); // intenta de nuevo en 10 unidades de tiempo
        }
    } else {
        // le toca devolver las camas
        std::cout << "Se devuelven 2 camas**************************" << std::endl;
        h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());
        h.camas.returnBin(2);
        h.robar = true; // la prox vez le toca robar
        // vuelve a intentar robar en 10.0 unidades de tiempo
        //h.schedule(10.0, who, robaCama);

        while (!h.cola.empty() && h.camas.isAvailable(1)) {
            h.lCola.log(h.cola.size());
            Entity *ent = h.cola.pop();
            h.uCamas.log(h.camas.getMax() - h.camas.getQuantity());
            h.camas.acquire(1);
            h.schedule(h.estadia.sample(), ent, salidaP);
        }
        h.schedule(10.0, who, robaCama);
    }

    //delete who;
}
