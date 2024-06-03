#include <iostream>

#include "read_data.h"
#include "hash_abierto.h"
#include "hash_std.h"

#define SIZE_HASH 10001

int main(void) {
	HashAbierto TablasAbiertas(SIZE_HASH);
	HashSTD TablasSTD;
	load_data("universities_followers.csv", TablasAbiertas, TablasSTD);
	
		
}