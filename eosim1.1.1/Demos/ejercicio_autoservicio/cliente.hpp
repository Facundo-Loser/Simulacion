#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <eosim/core/bevent.hpp>
#include <eosim/core/cevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

// PLANIFICADO
const std::string clienteF = "ClienteFeeder";
class ClienteFeeder : public eosim::core::BEvent {
    public:
        ClienteFeeder(eosim::core::Model& model);
        ~ClienteFeeder();
        void eventRoutine(eosim::core::Entity* who);
};

// CONDICIONAL
const std::string inicioS = "InicioServicio";
class InicioServicio : public eosim::core::CEvent {
    public:
        InicioServicio(eosim::core::Model& model);
        ~InicioServicio();
        void eventRoutine();
};

// PLANIFICADO
const std::string salidaC = "SalidaCliente";
class SalidaCliente : public eosim::core::BEvent {
    public:
        SalidaCliente(eosim::core::Model& model);
        ~SalidaCliente();
        void eventRoutine(eosim::core::Entity* who);
};

#endif // CLIENTE_H_
