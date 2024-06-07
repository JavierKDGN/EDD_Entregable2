#include <iostream>

#include "read_data.h"
#include "UserInfo.h"
#include "HashAbierto.h"
#include "HashCerradoLinear.h"
#include "HashCerradoCuadratico.h"
#include "hash_std.h"

#define SIZE_HASH 25001

int main(void) {
	HashAbierto TablasAbiertas(SIZE_HASH);
	HashCerradoLinear TablasLinear(SIZE_HASH);
	HashCerradoCuadratico TablasCuadratico(SIZE_HASH);
	HashSTD TablasSTD;
	load_data("universities_followers.csv", TablasAbiertas, TablasLinear, TablasCuadratico,TablasSTD);
	
	TablasAbiertas.get_from_username("BerriosCavieres")->print();
	TablasAbiertas.remove_from_username("BerriosCavieres");
	TablasAbiertas.get_from_username("BerriosCavieres")->print();

}