#ifndef HOSPITAL_SIMPLE_G_HPP_
#define HOSPITAL_SIMPLE_G_HPP_

#include <eosim/core/model.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/graphic.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <utility>
#include <vector>
#include "eventospacienteg.hpp"

/*
Este es el modelo de simulacion del ejemplo del hospital simple presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 2 fases y con salida grafica
*/


// Este struct es la representacion grafica de una cam
typedef struct cama_tipo{
	std::pair<double,double> pos;
	eosim::graphic::Sprite spr;
	bool libre;

	cama_tipo(eosim::graphic::Display& disp, const char* file,std::pair<double,double> position): pos(position), spr(disp, file, pos.first, pos.second) {}
} camaStruct;

class HospitalSimpleG: public eosim::core::Model {
private:
	// tasa de arribos de los pacientes
	double tasaArribos;
	// tiempo de estadia de los pacientes
	double tiempoEstadia;
	// evento de arribo de los pacientes y alimentador (fijo)
	PacienteFeederG pF;
	// evento de salida de los pacientes (fijo)
	SalidaPacienteG sP;
	// evento de salida de los pacientes (fijo)
	MatarPacienteG mP;
	// evento de condicionado para el dibujado
	eosim::graphic::RefreshGraphic rG;


public:
	// Display del modelo
	eosim::graphic::Display disp;


	// constantes graficas
	const std::pair<double, double> pacienteIcon;
	const std::pair<double, double> camaIcon;
	const std::pair<double, double> filaEspera;
	const std::pair<double, double> puertaEntrada;
	const std::pair<double, double> puertaSalida;
	const std::pair<double, double> salida;
	const std::pair<double, double> camaIzq;

	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;
	// distribucion aleatoria de estadia de pacientes (exponencial)
	eosim::dist::NegexpDist estadia;
	// cola de espera por camas
	eosim::utils::EntityQueueFifo cola;
	// camas del hospital
	eosim::core::Renewable camasBin;

	std::vector<camaStruct> camas;


	// constructor del modelo
	HospitalSimpleG(unsigned int cantCamas, double tasaArribos, double tiempoEstadia);
	// destructor del modelo
	~HospitalSimpleG();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};

#endif

