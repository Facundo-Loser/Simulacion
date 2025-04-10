#ifndef MACHINE_HPP_
#define MACHINE_HPP_

#include <eosim/core/entity.hpp>

class Machine: public eosim::core::Entity{
private:
    int number;
public:
	Machine(int number): number(number) {}
	int getNumber() {return number; }
	~Machine() {}
};

#endif

