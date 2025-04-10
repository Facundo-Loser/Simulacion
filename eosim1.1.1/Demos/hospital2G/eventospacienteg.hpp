#ifndef EVENTOS_PACIENTE_G_HPP_
#define EVENTOS_PACIENTE_G_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

// identificador del evento fijo PacienteFeederG
const std::string pacienteFG = "PacienteFeederG";


class PacienteFeederG: public eosim::core::BEvent {
public:
	// constructor
	PacienteFeederG(eosim::core::Model& model);
	// destructor
	~PacienteFeederG();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

// identificador del evento fijo SalidaPaciente
const std::string salidaPG = "SalidaPaciente";


class SalidaPacienteG: public eosim::core::BEvent {
public:
	// constructor
	SalidaPacienteG(eosim::core::Model& model);
	// destructor
	~SalidaPacienteG();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

// identificador del evento fijo SalidaPaciente
const std::string killPG = "matarPaciente";

class MatarPacienteG: public eosim::core::BEvent {
public:
	// constructor
	MatarPacienteG(eosim::core::Model& model);
	// destructor
	~MatarPacienteG();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

#endif

