#ifndef AUTOSERVICIO_H_
#define AUTOSERVICIO_H_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/dist/normaldist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include "cliente.hpp"

class Autoservicio: public eosim::core::Model {
    private:
        double tasaArribos;
        double tiempoEstadia;
        ClienteFeeder cF;
        InicioServicio iS;
        SalidaCliente sC;
    public:
        eosim::dist::NegexpDist arribos;
        eosim::dist::NormalDist estadia;
        eosim::utils::EntityQueueFifo cola;
        eosim::core::Renewable maquinaCafe;
        eosim::statics::Observation tEspera;
        eosim::statics::TimeWeighted lCola;
        eosim::statics::TimeWeighted umaquinaCafe; // utilizacion maquina cafe

        Autoservicio(unsigned int cantMaquinasCafe, double tasaArribos, double tiempoEstadia);
        ~Autoservicio();

        void init();
        void doInitialSchedules();
};

#endif // AUTOSERVICIO_H_
