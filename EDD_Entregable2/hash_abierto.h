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
	std::vector<Nodo*> username_table;
	std::vector<Nodo*> id_table;

	//Cantidad de elementos en la tabla hash
	size_t username_table_size;
	size_t id_table_size;

	//Capacidad maxima de la tabla hash
	size_t capacity;
	

private:
	void insert_username(const std::string& key, const UserInfo& value) {
		//Obtener el indice de la tabla hash
		size_t index;
		
		index = hash2(key, capacity);
		
		//Crear un nuevo nodo
		Nodo* new_node = new Nodo(key, value);

		//Si la posicion en la tabla hash esta vacia, insertar el nodo
		if (username_table[index] == nullptr) {
			username_table[index] = new_node;
		}
		else {
			//Si la posicion en la tabla hash no esta vacia, insertar el nodo al final de la lista ligada
			Nodo* current = username_table[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new_node;
		}

		//Incrementar el tamano de la tabla hash
		username_table_size++;
	}

	void insert_id(const std::string& key, const UserInfo& value) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash1(key, capacity);

		//Crear un nuevo nodo
		Nodo* new_node = new Nodo(key, value);

		//Si la posicion en la tabla hash esta vacia, insertar el nodo
		if (id_table[index] == nullptr) {
			id_table[index] = new_node;
		}
		else {
			//Si la posicion en la tabla hash no esta vacia, insertar el nodo al final de la lista ligada
			Nodo* current = id_table[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new_node;
		}

		//Incrementar el tamano de la tabla hash
		id_table_size++;
	}

	

public:
	HashAbierto(size_t capacity) {
		this->capacity = capacity;
		this->username_table_size = 0;
		this->id_table_size = 0;
		this->username_table = std::vector<Nodo*>(capacity, nullptr);
		this->id_table = std::vector<Nodo*>(capacity, nullptr);

	}

	void insert(const std::string& key_id, const std::string& key_username, const UserInfo& value) {
		insert_id(key_id, value);
		insert_username(key_username, value);

	}

	//Buscar un elemento en la tabla hash, key es la clave
	UserInfo get_from_username(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash2(key, capacity);

		Nodo* current = username_table[index];
		while (current != nullptr) {
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}

		//Si no se encontro el nodo, lanzar una excepcion
		throw std::runtime_error("Error: key not found");
	}

	UserInfo get_from_id(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash1(key, capacity);

		Nodo* current = id_table[index];
		while (current != nullptr) {
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}

		//Si no se encontro el nodo, lanzar una excepcion
		throw std::runtime_error("Error: key not found");
	}

	void remove_from_username(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash2(key, capacity);

		//Buscar el nodo en la lista ligada
		Nodo* current = username_table[index];
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
			username_table[index] = current->next;
		}
		else {
			previous->next = current->next;
		}
		delete current;

		//Decrementar el tamano de la tabla hash
		username_table_size--;
	}

	//Eliminar un elemento en la tabla hash, key es la clave
	void remove_from_id(const std::string& key) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash1(key, capacity);

		//Buscar el nodo en la lista ligada
		Nodo* current = id_table[index];
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
			id_table[index] = current->next;
		}
		else {
			previous->next = current->next;
		}
		delete current;

		//Decrementar el tamano de la tabla hash
		id_table_size--;
	}
};