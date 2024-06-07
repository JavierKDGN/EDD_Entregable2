#pragma once

#include <iostream>
#include <string>
#include <vector>

const int CONSTANTE_PRIMO = 37;

//Acumulacion polinomial
//O(n) n: largo de la string
size_t hash_id(const std::string& id, size_t table_size) {
	size_t hash_val = 0;
	size_t potencia = 1;

	for (char c : id) {
		hash_val += c * potencia;
		potencia *= CONSTANTE_PRIMO;
	}

	return hash_val % table_size;
}

//Hash de cadena
//O(n) n: largo de la string
size_t hash_username(const std::string& user, size_t table_size) {
	size_t hash_val = 0;
	for (char c : user) {
		hash_val = CONSTANTE_PRIMO * hash_val + c;
	}
	return hash_val % table_size;
}