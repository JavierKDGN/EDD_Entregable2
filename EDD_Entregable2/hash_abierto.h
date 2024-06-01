#pragma once

#include <string>
#include <vector>
#include "dataset.h"

//Implementacion de lista ligada para la tabla hash
struct Nodo {
	std::string key;
	UserInfo value;
	Nodo* next;

	Nodo(const std::string& key, const UserInfo& value) {
		this->key = key;
		this->value = value;
		this->next = nullptr;
	}
};

class HashAbierto {
private:
	//Vector de punteros a nodos, que representan una posicion en la tabla hash 
	std::vector<Nodo*> table;
	//Cantidad de elementos en la tabla hash
	size_t size;
	//Capacidad maxima de la tabla hash
	size_t capacity;
	
	size_t open_hash_id(const std::string& key) {
		//hasheo abierto para una cadena de numeros
	}

	size_t open_hash_username(const std::string& key) {
		//hasheo abierto para usuarios que pueden contener letras y numeros
	}

public:
	size_t hash(const std::string& key) {
		//Esta funcion determina si se esta hasheando un ID numerico o un username, y aplica la funcion hash privada correspondiente

	}

	void rehash() {
		//Rehashing de la tabla hash cuando se llena mas del 70% de su capacidad

	}

	Nodo* find(const std::string& key) {
		//Busca un nodo en la tabla hash a partir de una clave key y retorna un puntero al nodo si lo encuentra, o nullptr si no lo encuentra
	}
};