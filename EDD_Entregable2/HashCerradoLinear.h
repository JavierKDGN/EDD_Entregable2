#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "UserInfo.h"
#include "funciones_hash.h"

//Referencia: https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/

class HashCerradoLinear {
private:
	struct HashMap {
		std::vector<UserInfo*> tabla;
		size_t size;

		HashMap(size_t capacity) {
			this->tabla = std::vector<UserInfo*>(capacity, nullptr);
			this->size = 0;
		}
	};

private:
	HashMap *username_table;
	HashMap *id_table;
	size_t capacity;

	void _insert(HashMap& hash_map, const UserInfo& user, size_t index) {
		if (hash_map.size >= capacity) {
			std::cout << "Tabla llena" << std::endl;
			throw std::out_of_range("Tabla llena");
			return;
		}

		if (hash_map.tabla[index] == nullptr) {
			hash_map.tabla[index] = new UserInfo(user);
			hash_map.size++;
		}
		else {
			size_t i = index;
			while (hash_map.tabla[i] != nullptr) {
				i = (i + 1) % capacity;
			}
			hash_map.tabla[i] = new UserInfo(user);
			hash_map.size++;
		}
	}

	UserInfo *_get(HashMap& hash_map, const std::string& key, size_t index) {
		size_t i = index;
		size_t start_index = index;
		//Para datos repetidos, si se quiere encontrar una clave repetida se revisa hasta que es encontrada despues de 1 vuelta
		do {
			if (hash_map.tabla[i] != nullptr) {
				if (hash_map.tabla[i]->user_id == key || hash_map.tabla[i]->user_name == key) {
					return hash_map.tabla[i];
				}
			}
			i = (i + 1) % capacity;
		} while (i != start_index);
		
	}

	void _remove(HashMap& hash_map, const std::string& key, size_t index) {
		size_t i = index;
		size_t start_index = index;
		//Para datos repetidos, si se quiere encontrar una clave repetida se revisa hasta que es encontrada despues de 1 vuelta
		do {
			if (hash_map.tabla[i] != nullptr) {
				if (hash_map.tabla[i]->user_id == key || hash_map.tabla[i]->user_name == key) {
					delete hash_map.tabla[i];
					hash_map.tabla[i] = nullptr;
					hash_map.size--;
					return;
				}
			}
			i = (i + 1) % capacity;
		} while (i != start_index);

	}

public:
	HashCerradoLinear(size_t capacity) {
		this->username_table = new HashMap(capacity);
		this->id_table = new HashMap(capacity);
		this->capacity = capacity;
	}

	void insert(const UserInfo& user) {
		size_t index_id = hash_id(user.user_id, capacity);
		size_t index_username = hash_username(user.user_name, capacity);

		_insert(*id_table, user, index_id);
		_insert(*username_table, user, index_username);
	}

	UserInfo *get_from_id(const std::string& user_id) {
		size_t index = hash_id(user_id, capacity);
		return _get(*id_table, user_id, index);
	}

	UserInfo *get_from_username(const std::string& username) {
		size_t index = hash_username(username, capacity);
		return _get(*username_table, username, index);
	}

	void remove_from_id(const std::string& user_id) {
		size_t index = hash_id(user_id, capacity);
		_remove(*id_table, user_id, index);
	}

	void remove_from_username(const std::string& username) {
		size_t index = hash_username(username, capacity);
		_remove(*username_table, username, index);
	}
};
