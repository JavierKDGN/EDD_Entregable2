#pragma once

#include <string>
#include <vector>
#include "dataset.h"

//Implementacion de lista ligada para la tabla hash cerrada, usando booleano para ver si esta la casilla ocupada
struct NodoHash {
	std::string key;
	UserInfo value;
	bool deleted;

	NodoHash(const std::string& key, const UserInfo& value) {
		this->key = key;
		this->value = value;
		this->deleted = false;
	}
};

class HashCerradoLinear {

};

class HashCerradoCuadratico {

};

class HashCerradoDoble {

};