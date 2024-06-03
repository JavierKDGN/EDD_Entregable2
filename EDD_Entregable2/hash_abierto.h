#pragma once

#include <string>
#include <vector>
#include "UserInfo.h"
#include "funciones_hash.h"


class HashAbierto {
private:
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

private:
	//Vector de punteros a nodos, que representan una posicion en la tabla hash 
	std::vector<Nodo*> table;

	//Cantidad de elementos en la tabla hash
	size_t size;

	//Capacidad maxima de la tabla hash
	size_t capacity;
	
	//Indica si la tabla hash es de nombres de usuario o de contrasenas
	bool isUsername;

public:
	HashAbierto(size_t capacity, bool isUsername) {
		this->capacity = capacity;
		this->size = 0;
		this->table = std::vector<Nodo*>(capacity, nullptr);
		this->isUsername = isUsername;
	}

	//insrtar un elemento en la tabla hash, key es la clave y value es la informacion del usuario
	void insert(const std::string& key, const UserInfo& value) {
		//Obtener el indice de la tabla hash
		size_t index;
		if (isUsername) {
			index = hash2(key, capacity);
		}
		else {
			index = hash1(key, capacity);
		}

		//Crear un nuevo nodo
		Nodo* new_node = new Nodo(key, value);

		//Si la posicion en la tabla hash esta vacia, insertar el nodo
		if (table[index] == nullptr) {
			table[index] = new_node;
		}
		else {
			//Si la posicion en la tabla hash no esta vacia, insertar el nodo al final de la lista ligada
			Nodo* current = table[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new_node;
		}

		//Incrementar el tamano de la tabla hash
		size++;
	}

	//Buscar un elemento en la tabla hash, key es la clave
	UserInfo search(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		if (isUsername) {
			index = hash2(key, capacity);
		}
		else {
			index = hash1(key, capacity);
		}

		//Buscar el nodo en la lista ligada
		Nodo* current = table[index];
		while (current != nullptr) {
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}

		//Si no se encontro el nodo, lanzar una excepcion
		throw std::runtime_error("Error: key not found");
	}

	//Eliminar un elemento en la tabla hash, key es la clave
	void remove(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		if (isUsername) {
			index = hash2(key, capacity);
		}
		else {
			index = hash1(key, capacity);
		}

		//Buscar el nodo en la lista ligada
		Nodo* current = table[index];
		Nodo* previous = nullptr;
		while (current != nullptr) {
			if (current->key == key) {
				break;
			}
			previous = current;
			current = current->next;
		}

		//Si no se encontro el nodo, lanzar una excepcion
		if (current == nullptr) {
			throw std::runtime_error("Error: key not found");
		}

		//Eliminar el nodo
		if (previous == nullptr) {
			table[index] = current->next;
		}
		else {
			previous->next = current->next;
		}
		delete current;

		//Decrementar el tamano de la tabla hash
		size--;
	}
};