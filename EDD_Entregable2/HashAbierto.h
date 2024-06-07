#pragma once

#include <string>
#include <vector>
#include "UserInfo.h"
#include "funciones_hash.h"


//Referencia : https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/

class HashAbierto {
private:
	//Implementacion de lista ligada para la tabla hash
	struct Nodo {
		UserInfo* user;
		Nodo* next;

		Nodo(const UserInfo& value) {
			this->user = new UserInfo(value);
			this->next = nullptr;
		}
	};

	struct HashMap {
		std::vector<Nodo*> tabla;
		size_t size;

		HashMap(size_t capacity) {
			this->tabla = std::vector<Nodo*>(capacity, nullptr);
			this->size = 0;
		}
	};

private: 
	HashMap *username_table;
	HashMap *id_table;
	size_t capacity;

	void _insert(HashMap& hash_map, const UserInfo& user, const size_t index) {

		if (hash_map.tabla[index] == nullptr) {
			hash_map.tabla[index] = new Nodo(user);
			hash_map.size++;
		}
		else {
			Nodo* current = hash_map.tabla[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new Nodo(user);
			hash_map.size++;
		}
	}

	UserInfo* _get(HashMap& hash_map, const std::string& key, const size_t index) {
		Nodo* current = hash_map.tabla[index];
		while (current != nullptr) {
			if (current->user->user_id == key || current->user->user_name == key) {
				return current->user;
			}
			current = current->next;
		}

		//Si no se encontro el nodo, lanzar una excepcion
		std::cout << "Usuario no encontrado" << std::endl;
		throw std::runtime_error("Error: key not found");
	}

	void _remove(HashMap& hash_map, const std::string& key, const size_t index) {
		//Buscar el nodo en la lista ligada
		Nodo* current = hash_map.tabla[index];
		Nodo* previous = nullptr;
		while (current != nullptr) {
			if (current->user->user_id == key || current->user->user_name == key) {
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
			hash_map.tabla[index] = current->next;
		}
		else {
			previous->next = current->next;
		}
		delete current;

		//Decrementar el tamano de la tabla hash
		hash_map.size--;
	}
	
public:
	HashAbierto(size_t capacity) {
		this->capacity = capacity;
		this->username_table = new HashMap(capacity);
		this->id_table = new HashMap(capacity);
	}

	//O(n)
	void insert(const UserInfo& user) {
		size_t index_id = hash_id(user.user_id, capacity);
		size_t index_username = hash_username(user.user_name, capacity);

		_insert(*id_table, user, index_id);
		_insert(*username_table, user, index_username);

	}

	//Buscar un elemento en la tabla hash
	//O(n)
	UserInfo *get_from_username(const std::string& username) {
		//Obtener el indice de la tabla hash
		size_t index;
		index = hash_username(username, capacity);
		
		return _get(*username_table, username, index);
	}

	//O(n)
	UserInfo *get_from_id(const std::string& user_id) {
		size_t index;
		index = hash_id(user_id, capacity);

		return _get(*id_table, user_id, index);
	}

	//O(n)
	void remove_from_username(const std::string& username) {
		size_t index;
		index = hash_username(username, capacity);

		_remove(*username_table, username, index);
	}

	//Eliminar un elemento en la tabla hash
	//O(n)
	void remove_from_id(const std::string& user_id) {
		size_t index;
		index = hash_id(user_id, capacity);

		_remove(*id_table, user_id, index);
	}
};