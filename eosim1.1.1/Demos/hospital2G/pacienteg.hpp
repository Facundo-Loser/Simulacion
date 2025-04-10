#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <eosim/core/entity.hpp>
#include <eosim/graphic/Display.hpp>

class PacienteG: public eosim::core::Entity {
public:
	eosim::graphic::Sprite spr;
	unsigned int miCama;
	// el ejemplo esta pensado para correr desde el directorio bin
	PacienteG(eosim::graphic::Display& disp, double posx, double posy) : spr(disp,"../images/enfermo.PNG", posx, posy) {}
	~PacienteG() {}

};

#endif

