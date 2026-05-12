#include <stdio.h>
#include <stdlib.h>

typedef struct{
	const int item;
	const int recyc;
	int state;
} items;

int main(){
	items seringue, gants, ecarteur, lampe, grattoir, compresse, perceuse, pince;
	seringue.item = 1;
	seringue.recyc = 0;
	
	gants.item = 2;
	gants.recyc = 0;
	
	ecarteur.item = 3;
	ecarteur.recyc = 1;
	
	lampe.item = 4;
	lampe.recyc = 1;
	
	grattoir.item = 5;
	grattoir.recyc = 1;
	
	compresse.item = 6;
	compresse.recyc = 0;
	
	perceuse.item = 7;
	perceuse.recyc = 1;
	
	pince.item = 8;
	pince.recyc = 1;
}
