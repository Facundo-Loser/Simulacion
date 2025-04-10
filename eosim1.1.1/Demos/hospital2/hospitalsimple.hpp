#ifndef HOSPITAL_SIMPLE_HPP_
#define HOSPITAL_SIMPLE_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include "paciente.hpp"
#include <eosim/dist/normaldist.hpp>

/*
Este es el modelo de simulacion del ejemplo del hospital simple presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 2 fases
*/

class HospitalSimple: public eosim::core::Model {
private:
	// tasa de arribos de los pacientes
	double tasaArribos;
	// tiempo de estadia de los pacientes
	double tiempoEstadia;
	// evento de arribo de los pacientes y alimentador (fijo)
	PacienteFeeder pF;
	// evento de salida de los pacientes (fijo)
	SalidaPaciente sP;

	RobaCamas rC;

public:
	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;
	// distribucion aleatoria de estadia de pacientes (exponencial)
	eosim::dist::NegexpDist estadia;
	// cola de espera por camas
	eosim::utils::EntityQueueFifo cola;
	// camas del hospital
	eosim::core::Renewable camas;
	// acumulador de datos sobre los tiempos de espera en las colas
	eosim::statics::Observation tEspera;
	// acumulador de datos sobre el largo medio de la cola
	eosim::statics::TimeWeighted lCola;

	eosim::statics::TimeWeighted uCamas;

	eosim::dist::NormalDist usoRoboCamas; // para generar el tiempo del robo de las camas

	// constructor del modelo
	HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia);
	// destructor del modelo
	~HospitalSimple();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};

#endif

