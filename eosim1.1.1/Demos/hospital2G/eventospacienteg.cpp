#include "eventospacienteg.hpp"
#include "hospitalsimpleg.hpp"
#include "pacienteg.hpp"
#include <iostream>
#include <eosim/graphic/Display.hpp>

using namespace eosim::core;
using namespace eosim::graphic;


// en el constructor se utiliza el identificador definido en paciente.hpp
PacienteFeederG::PacienteFeederG(Model& model): BEvent(pacienteFG, model) {}

PacienteFeederG::~PacienteFeederG() {}

void PacienteFeederG::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	//std::cout << "llego un paciente en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimpleG& h = dynamic_cast<HospitalSimpleG&>(owner);
	PacienteG* p = dynamic_cast<PacienteG*>(who);
	p->spr.setVisible(1);
	if (h.camasBin.isAvailable(1)) {
		double stay = h.estadia.sample();
		h.camasBin.acquire(1);
		for (p->miCama = 0; p->miCama < h.camas.size() && !h.camas[p->miCama].libre; p->miCama++);
		h.camas[p->miCama].libre = 0;
		p->spr.setMoves(move(h.puertaEntrada.first, h.puertaEntrada.second, stay*0.05).move(h.camas[p->miCama].pos.first, h.camas[p->miCama].pos.second, stay*0.15));
		//std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
		h.schedule(stay, p, salidaPG);
	}
	else {
		// se pone al paciente recien llegado en la cola
		h.cola.push(p);
		// ponerlo en el lugar de la cola correcto
		p->spr.setMoves(move(h.filaEspera.first - (h.cola.size() - 1) * h.pacienteIcon.first / 2, h.filaEspera.second, 0));




		// se agenda el arribo del un nuevo paciente
	}
	PacienteG* next = new PacienteG(h.disp, h.filaEspera.first, h.filaEspera.second);
	next->spr.setVisible(0);
	h.schedule(h.arribos.sample(), next, pacienteFG);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
SalidaPacienteG::SalidaPacienteG(Model& model): BEvent(salidaPG, model) {}

SalidaPacienteG::~SalidaPacienteG() {}

void SalidaPacienteG::eventRoutine(Entity* who) {
	// se informa la salida de un paciente
	//std::cout << "un paciente se retira en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimpleG& h = dynamic_cast<HospitalSimpleG&>(owner);
	PacienteG* p = dynamic_cast<PacienteG*>(who);
	// el ejemplo esta pensado para correr desde el directorio bin
	p->spr.setImage("../images/curado.png");
	// se retorna la cama que el paciente ocupaba
	h.camasBin.returnBin(1);
	h.camas[p->miCama].libre = 1;
	if (!h.cola.empty()) {
		h.camasBin.acquire(1);
		//std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
		h.camas[p->miCama].libre = 0;
		double stay = h.estadia.sample();
		PacienteG* ent = dynamic_cast<PacienteG*> (h.cola.pop());
		// mover a todos para adelante
		for (unsigned int i = 0; i < h.cola.size(); i++) {
			PacienteG* tempPac = dynamic_cast<PacienteG*> (h.cola[i]);
			tempPac->spr.setMoves(move(h.filaEspera.first - i * h.pacienteIcon.first / 2, h.filaEspera.second, 0));
		}
		ent->miCama = p->miCama;
		ent->spr.setMoves(move(h.puertaEntrada.first, h.puertaEntrada.second, stay*0.05).move(h.camas[p->miCama].pos.first, h.camas[p->miCama].pos.second, stay*0.05));
		h.schedule(stay, ent, salidaPG);
	}
	// se elimina al paciente del sistema
	p->spr.setMoves(move(h.puertaSalida.first, h.puertaSalida.second, 3).move(h.salida.first, h.salida.second, 3));
	h.schedule(6, p, killPG);
}

MatarPacienteG::MatarPacienteG(Model& model): BEvent(killPG, model) {}

MatarPacienteG::~MatarPacienteG() {}

void MatarPacienteG::eventRoutine(Entity* who) {
	delete who;
}
