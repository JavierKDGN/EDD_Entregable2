#include <iostream>

#include "load_data.h"
#include "UserInfo.h"
#include "HashAbierto.h"
#include "HashCerradoLinear.h"
#include "HashCerradoCuadratico.h"
#include "HashCerradoDoble.h"
#include "HashSTD.h"

#define SIZE_HASH 25001

int main(void) {
	HashAbierto TablasAbiertas(SIZE_HASH);
	HashCerradoLinear TablasLinear(SIZE_HASH);
	HashCerradoCuadratico TablasCuadratico(SIZE_HASH);
	HashCerradoDoble TablasDoble(SIZE_HASH);
	HashSTD TablasSTD;
	load_data("universities_followers.csv", TablasAbiertas, TablasLinear, TablasCuadratico, TablasDoble,TablasSTD);
	
	TablasCuadratico.get_from_username("BerriosCavieres")->print();
	TablasCuadratico.remove_from_username("BerriosCavieres");
	TablasCuadratico.get_from_username("BerriosCavieres")->print();



}