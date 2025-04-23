//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Moneda{
//	char* taraEminenta;
//	int valoareNominala;
//	float greutate;
//	int anEmitere;
//};
//typedef struct Moneda Moneda;
//
//struct Nod {
//	Moneda info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//Moneda citireMonedaDinFisier(FILE* file) {
//	char buffer[100];
//	char separator[3] = ",\n";
//	fgets(buffer, 100, file);
//
//	char* aux;
//	Moneda m1;
//	aux = strtok(buffer, separator);
//
//	m1.taraEminenta = malloc(strlen(aux) + 1);
//	strcpy_s(m1.taraEminenta, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, separator);
//	m1.valoareNominala = atoi(aux);
//
//	aux = strtok(NULL, separator);
//	m1.greutate = atof(aux);
//
//	aux = strtok(NULL, separator);
//	m1.anEmitere = atoi(aux);
//
//	return m1;
//}
//
//void afisareMoneda(Moneda moneda) {
//	printf("tara eminenta: %s\n", moneda.taraEminenta);
//	printf("valoare nominala: %d\n", moneda.valoareNominala);
//	printf("greutate: %.2f\n", moneda.greutate);
//	printf("an emitere: %d\n", moneda.anEmitere);
//}
//
//void afisareListaMonede(Nod* lista) {
//	Nod* temp = lista;
//	while (temp) {
//		afisareMoneda(temp->info);
//		temp = temp->next;
//	}
//}
//
//void inserareMonedaLI(Nod** listaSimpla, Moneda monedaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = monedaNoua;
//	nodNou->next = NULL;
//
//	if ((*listaSimpla) == NULL) {
//		(*listaSimpla) = nodNou;
//	}
//	else {
//		Nod* temp = (*listaSimpla);
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//		temp->next = nodNou;
//	}
//}
//void main() 
//{
//
//	Nod* lista = NULL;
//	FILE* f = fopen("monezi.txt", "r");
//	while (!feof(f)) {
//		inserareMonedaLI(&lista, citireMonedaDinFisier(f));
//		
//	}
//	fclose(f);
//
//
//}