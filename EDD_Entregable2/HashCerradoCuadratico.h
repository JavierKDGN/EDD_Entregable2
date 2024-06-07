#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "UserInfo.h"
#include "funciones_hash.h"

//Referencia: https://www.geeksforgeeks.org/quadratic-probing-in-hashing/

class HashCerradoCuadratico {
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
    HashMap* username_table;
    HashMap* id_table;
    size_t capacity;

    // Función de hash cuadrática
    size_t hash_quad(size_t index, size_t attempt) const {
        return (index + attempt * attempt) % capacity;
    }

    void _insert(HashMap& hash_map, const UserInfo& user, size_t index) {
        if (hash_map.size >= capacity) {
            std::cout << "Tabla llena" << std::endl;
            throw std::out_of_range("Tabla llena");
            return;
        }

        size_t attempt = 0;
        size_t j = index;
        while (hash_map.tabla[j] != nullptr) {
            j = hash_quad(index, attempt);
            attempt++;
        }
        hash_map.tabla[j] = new UserInfo(user);
        hash_map.size++;
    }

    UserInfo* _get(HashMap& hash_map, const std::string& key, size_t index) {
        size_t i = 0;
        size_t start_index = index;
        size_t new_index;
        do {
            new_index = (start_index + i * i) % capacity;
            if (hash_map.tabla[new_index] != nullptr) {
                if (hash_map.tabla[new_index]->user_id == key || hash_map.tabla[new_index]->user_name == key) {
                    return hash_map.tabla[new_index];
                }
            }
            i++;
        } while (i < capacity && (start_index != new_index || i == 1));
    }

    void _remove(HashMap& hash_map, const std::string& key, size_t index) {
        size_t i = 0;
        size_t start_index = index;
        size_t new_index;
        do {
            new_index = (start_index + i * i) % capacity;
            if (hash_map.tabla[new_index] != nullptr) {
                if (hash_map.tabla[new_index]->user_id == key || hash_map.tabla[new_index]->user_name == key) {
                    delete hash_map.tabla[new_index];
                    hash_map.tabla[new_index] = nullptr;
                    hash_map.size--;
                    return;
                }
            }
            i++;
        } while (i < capacity && (start_index != new_index || i == 1));
    }


public:
    HashCerradoCuadratico(size_t capacity) {
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

    UserInfo* get_from_id(const std::string& user_id) {
        size_t index = hash_id(user_id, capacity);
        return _get(*id_table, user_id, index);
    }

    UserInfo* get_from_username(const std::string& username) {
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
