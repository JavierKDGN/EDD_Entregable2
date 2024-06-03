#include <iostream>

#include "read_data.h"
#include "hash_abierto.h"

int main(void) {
	HashAbierto TablaUsuarios(10001, true);
	HashAbierto TablaID(100, false);
	load_data("universities_followers.csv", TablaUsuarios);
	TablaUsuarios.search("LangmeierSchulz").print();
	TablaUsuarios.remove("LangmeierSchulz");
	TablaUsuarios.search("LangmeierSchulz");
	TablaUsuarios.remove("LangmeierSchulz");
	TablaUsuarios.search("LangmeierSchulz");
	TablaUsuarios.remove("LangmeierSchulz");



}