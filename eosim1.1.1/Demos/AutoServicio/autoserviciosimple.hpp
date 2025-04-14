#ifndef AUTOSERVICIO_SIMPLE_HPP_
#define AUTOSERVICIO_SIMPLE_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/dist/normaldist.hpp>
#include "Cliente.hpp"


class AutoservicioSimple: public eosim::core::Model {
    private:
        double tasaArribos;
        double tiempoEstadia;

        // ClienteFeeder cF;
        // SalidaCliente fd;
    public:
        // distribucion aleatoria de arribos de clientes (exponencial)
        eosim::dist::NegexpDist arribos;
        // distribucion aleatoria de estadia de clientes(Normal)
        eosim::dist::NormalDist estadia;

        eosim::utils::EntityQueueFifo cola;

        // hace falta modelar los recursos??

        // acumulador de datos sobre los tiempos de espera en las colas
        eosim::statics::Observation tEspera;
        // acumulador de datos sobre el largo medio de la cola
        eosim::statics::TimeWeighted lCola;

        // constuctor:
        AutoservicioSimple(double tasaArribos, double tiempoEstadia);
        ~AutoservicioSimple();
        // inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
        void init();
        // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
        void doInitialSchedules();

};

#endif // AUTOSERVICIO_SIMPLE_HPP_
