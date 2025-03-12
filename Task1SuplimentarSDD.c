//1. Structura si functii
//Se consideră prima literă din numele vostru, și prima literă din prenumele vostru.
//Sa se construiască un articol care să conțină cele două litere.
//Exemplu: Alin Zamfiroiu->A si Z.Articolul Magazin :
//struct Magazin {
//	int cod;
//	char* denumire;
//	int nrProduse;
//	float* preturi;
//}
//Articolul trebuie să aibă logica.Articolul trebuie sa fie un substantiv.Articolul trebuie sa aibă
//cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
//Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de
//voi.Funcția returnează obiectul citit.
//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o
//	medie sau o suma, un maxim, un minim...sau orice altceva)
//	Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
//	noua valoare este primita ca parametru.
//	Realizați o funcție care afișează un obiect de tipul creat.Afișarea se face la console, și sunt
//	afișate toate informațiile.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Gogoasa {
	int cod;
	char* denumire;
	char* glazura;
	float pret;
	float costFabricare;
	char marime;
};
typedef struct Gogoasa Gogoasa;

Gogoasa citireGogoasa() {
	Gogoasa g;
	printf("Cod: ");
	scanf("%d", &g.cod);

	printf("Denumire: ");
	char buffer[20];
	scanf("%s", buffer);
	g.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(g.denumire, buffer);

	printf("Glazura: ");
	scanf("%s", buffer);
	g.glazura = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(g.glazura, buffer);

	printf("Pret: ");
	scanf("%f", &g.pret);

	printf("Cost fabricare: ");
	scanf("%f", &g.costFabricare);

	printf("Marime: ");
	scanf(" %c", &g.marime);

	printf("------------------------------\n");
	return g;
}

void afisareGogoasa(Gogoasa g) {
	printf("Cod: %d\n", g.cod);
	printf("Denumire: %s\n", g.denumire);
	printf("Glazura: %s\n", g.glazura);
	printf("Pret: %f\n", g.pret);
	printf("Cost fabricare: %f\n", g.costFabricare);
	printf("Marime: %c\n", g.marime);
	printf("------------------------------\n");

}

float calculeazaProfitPerGogoasa(Gogoasa g) {
	if (g.pret > g.costFabricare)
		printf("Profitul pentru gogoasa %s: %f\n", g.denumire, g.pret - g.costFabricare);
	return g.pret - g.costFabricare;
}

void modificareDenumire(Gogoasa* g, const char* denumireNoua) {
	if (g->denumire) {
		free(g->denumire);
	}
	g->denumire = (char*)malloc((strlen(denumireNoua) + 1) * sizeof(char));
	strcpy_s(g->denumire, strlen(denumireNoua) + 1, denumireNoua);
}

void modificarePretpentruGogoasa(Gogoasa* g, float pretNou) {
	g->pret = pretNou;
}


int main() {

	printf("------------------Citire gogoasa------------------\n");
	Gogoasa g1 = citireGogoasa();

	printf("------------------Afisare gogoasa------------------\n");
	afisareGogoasa(g1);

	printf("------------------Profit per gogoasa------------------\n");
	calculeazaProfitPerGogoasa(g1);

	printf("------------------Modificare denumire & pret------------------\n");
	Gogoasa g2;
	g2.cod = 2;
	g2.denumire = (char*)malloc(strlen("doNutEatMe") + 1);
	strcpy_s(g2.denumire, strlen("doNutEatMe") + 1, "doNutEatMe");

	g2.glazura = (char*)malloc(strlen("Vanilie") + 1);
	strcpy(g2.glazura, strlen("Vanilie") + 1, "Vanilie");

	g2.pret = 25;
	g2.costFabricare = 23;
	g2.marime = 'L';

	printf("Inainte de modificare\n");
	afisareGogoasa(g2);
	printf("Dupa modificare\n");
	modificareDenumire(&g2, "DonutEatMe");
	modificarePretpentruGogoasa(&g2, 30);

	afisareGogoasa(g2);

	return 0;

}
