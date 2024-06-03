#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int CONSTANTE_PRIMO = 37;

//Acumulacion polinomial
size_t hash1(const std::string& id, size_t table_size) {
	size_t hash_val = 0;
	size_t i = 0;

	for (char c : id) {
		hash_val += c * pow(CONSTANTE_PRIMO, i);
	}

	return hash_val;
}

//Hash de cadena
size_t hash2(const std::string& user, size_t table_size) {
	size_t hash_val = 0;
	for (char c : user) {
		hash_val = CONSTANTE_PRIMO * hash_val + c;
	}
	return hash_val % table_size;
}