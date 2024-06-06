#pragma once

#include <string>
#include <vector>
#include "UserInfo.h"
#include "funciones_hash.h"

//Implementacion de lista ligada para la tabla hash cerrada, usando booleano para ver si esta la casilla ocupada
struct NodoHash {
	std::string key;
	UserInfo value;
	bool deleted;
	NodoHash* next;

	NodoHash(const std::string& key, const UserInfo& value) {
		this->key = key;
		this->value = value;
		this->deleted = false;
	}
};

class HashCerradoLinear {
private:
	size_t elem;
	//Vector de punteros a nodos, que representan una posicion en la tabla hash 
	std::vector<NodoHash*> username_table;
	std::vector<NodoHash*> id_table;

	size_t username_table_size;
	size_t id_table_size;

	//Capacidad maxima de la tabla hash
	size_t capacity;
	size_t hashUsername(const std::string& username) const {
        return hash2(username, username_table_size);
    }

    size_t hashID(const std::string& id) const {
        return hash1(id, id_table_size);
    }
public:
	HashCerradoLinear(size_t cap): capacity(cap), username_table_size(cap), id_table_size(cap), elem(0) {
        username_table.resize(username_table_size, nullptr);
        id_table.resize(id_table_size, nullptr);
    }
    int size() const {
        return elem;//retorna los elementos
    }
    bool lleno() const {//revisa si esta lleno
		if(elem >= capacity){
			return true;
		}else{
			return false;
		}
    }
	bool insertar(const std::string& username, const std::string& id, const UserInfo& value) {
        if (elem >= capacity) {
            return false; // revisa si esta lleno antes de seguir
        }
        // tabal username
        size_t index = hashUsername(username);
        NodoHash* newNodo = new NodoHash(username, value);
        if (username_table[index] == nullptr) {
            username_table[index] = newNodo;
        } else {
            NodoHash* actual = username_table[index];
            while (actual->next) {
                actual = actual->next;
            }
            actual->next = newNodo;
        }
        // tabla id
        index = hashID(id);
        newNodo = new NodoHash(id, value);
        if (username_table[index] == nullptr) {
            id_table[index] = newNodo;
        } else {
            NodoHash* current = id_table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newNodo;
        }
        elem++;
        return true;
    }
	UserInfo* buscarConUsername(const std::string& username) {
        size_t index = hashUsername(username);
        NodoHash* actual = username_table[index];
        while (actual) {
            if (actual->key == username) {
                return &actual->value;// retorna el username de tipo UserInfo si lo encuentra
            }
            actual = actual->next;//hace el cambio
        }
        return nullptr;
    }
	UserInfo* buscarConID(const std::string& id) {
        size_t index = hashID(id);
        NodoHash* actual = id_table[index];
        while (actual) {
            if (actual->key == id && !actual->deleted) {
                return &actual->value;// retorna el id de tipo UserInfo si lo encuentra
            }
            actual = actual->next;
        }
        return nullptr;
    }
	bool EliminarConUsername(const std::string& username) {
        size_t index = hashUsername(username);
        NodoHash* actual = username_table[index];
        NodoHash* prev = nullptr;
        while (actual) {
            if (actual->key == username && !actual->deleted) {
                actual->deleted = true;//marca el nodo como eliminado
                if (prev) {
                    prev->next = actual->next;
                } else {
                    username_table[index] = actual->next;
                }
                elem--;
                return true;
            }
            prev = actual;
            actual = actual->next;
        }
        return false;
    }
    bool EliminarConID(const std::string& id) {
        size_t index = hashID(id);
        NodoHash* actual = id_table[index];
        NodoHash* prev = nullptr;
        while (actual) {
            if (actual->key == id && !actual->deleted) {
                actual->deleted = true;//marca el nodo como eliminado
                if (prev) {
                    prev->next = actual->next;
                } else {
                    id_table[index] = actual->next;
                }
                elem--;
                return true;
            }
            prev = actual;
            actual = actual->next;
        }
        return false;
    }
};

class HashCerradoCuadratico {

};

class HashCerradoDoble {

};