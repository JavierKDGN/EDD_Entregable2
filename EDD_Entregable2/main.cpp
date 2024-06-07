#include <iostream>

#include "read_data.h"
#include "UserInfo.h"
#include "HashAbierto.h"
#include "HashCerradoLinear.h"
#include "hash_std.h"

#define SIZE_HASH 25001

int main(void) {
	HashAbierto TablasAbiertas(SIZE_HASH);
	HashCerradoLinear TablasCerradas(SIZE_HASH);
	HashSTD TablasSTD;
	load_data("universities_followers.csv", TablasAbiertas, TablasCerradas,TablasSTD);
	
	TablasCerradas.get_from_username("BerriosCavieres")->print();
}