#ifndef REPAIR_HPP
#define	REPAIR_HPP

#include "events.hpp"
#include "machine.hpp"
#include <vector>
#include <eosim/core/model.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/dist/normaldist.hpp>
#include <eosim/utils/entityqueuefifo.hpp>

/*
Este es el modelo de simulacion del ejemplo de la fabrica presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 3 fases
*/


class Repair: public eosim::core::Model {
private:
    // evento fijo de rotura de maquina
	EndWork eW;
    // evento fijo de finalizacion del quitado de partes defectuosas
	EndRemove eRv;
    // evento fijo de finalizacion de reparacion de la maquina
	EndRepair eRp;
    // evento condicional de comienzo del quitado de partes defectuosa
	StartRemove sRv;
    // evento condicional de comienzo de reparacion de la maquina
	StartRepair	sRp;
    // coleccion de maquinas de la fabrica
	std::vector<Machine*> machine;
public:
	int numMachinesBroken;
    // conjunto de mecanicos del modelo
    eosim::core::Renewable mechanics;
    // stock de equipamiento del modelo
	eosim::core::Renewable equipment;

	// disbribucion aleatoria de los tiempos de rotura de las maquinas
    eosim::dist::NegexpDist breakDown;
    // disbribucion aleatoria de los tiempos de remocion de partes defectuosas
	eosim::dist::NormalDist removal;
    // disbribucion aleatoria de los tiempos de reparacion
	eosim::dist::NormalDist repair;

    // cola de maquinas a las que se les deben quitar partes
	eosim::utils::EntityQueueFifo toRemove;
    // cola de maquinas a reparar
	eosim::utils::EntityQueueFifo toRepair;

	// constructor del modelo
    Repair(int cantMech, int cantEq, int cantMach, double breakDownTime,
		double removalMean, double removalSD, double repairMean, double repairSD);
    // destructor del modelo
	~Repair();
    // inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
    void init();
    // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
    void doInitialSchedules();
};


#endif



