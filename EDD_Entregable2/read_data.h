#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "UserInfo.h"
#include "hash_abierto.h"
#include "hash_cerrado.h"
#include "hash_std.h"

void load_data(const std::string& filename /*,
	HashAbierto& hash_abierto,
	HashCerradoLinear& hash_linear,
	HashCerradoCuadratico& hash_cuadratico,
	HashCerradoDoble& hash_doble,
	HashSTD& hash_std*/) {

	std::ifstream file(filename);
	std::vector<std::string> filas;
	std::string linea;

	if (!file.is_open()) {
		std::cerr << "Error: no se pudo abrir el archivo " << filename << std::endl;
		exit(1);
	}

	// Ignorar la primera fila
	std::getline(file, linea);

	//Leer el archivo linea por linea
	while (std::getline(file, linea)) {
		std::vector<std::string> campos;
		
		std::stringstream aux(linea);
		std::string segmento;

		while (std::getline(aux, segmento, ','))
		{
			campos.push_back(segmento);
		}

		const std::string university = campos[0];
		const std::string user_id = campos[1];
		const std::string user_name = campos[2];
		const size_t number_tweets = std::stoul(campos[3]);
		const size_t friends_count = std::stoul(campos[4]);
		const size_t followers_count = std::stoul(campos[5]);
		const std::string created_at = campos[6];

		UserInfo usuario = { university, user_id, user_name, number_tweets, friends_count, followers_count, created_at };

		//Insertar en tablas hash: POR HACER

	}

}
