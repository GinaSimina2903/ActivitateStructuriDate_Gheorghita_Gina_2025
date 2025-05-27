#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ComandaOnline ComandaOnline;
struct ComandaOnline {
	int id;
	char* numeClient;
	char* adresaLivrare;
	float valoare;
	unsigned char tipPlata;
};

typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Nod* prev;
	ComandaOnline info;
};

typedef struct LD LD;
struct LD {
	Nod* head;
	Nod* tail;
};

ComandaOnline citireComandaDinFisier(FILE* file) {
	char buffer[100];
	char sep[4] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	ComandaOnline co;

	aux = strtok(buffer, sep);
	co.id = atoi(aux);

	aux = strtok(NULL, sep);
	co.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy_s(co.numeClient, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	co.adresaLivrare = (char*)malloc(strlen(aux) + 1);
	strcpy_s(co.adresaLivrare, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	co.valoare = atof(aux);

	aux = strtok(NULL, sep);
	co.tipPlata = *aux;
	return co;
}

void afisareComanda(ComandaOnline co) {
	printf("ID: %d\n", co.id);
	printf("adresaLivrare: %s\n", co.adresaLivrare);
	printf("nume client: %s\n", co.numeClient);
	printf("adresa livrare: %.2f\n", co.valoare);
	printf("tip plata: %c\n\n", co.tipPlata);
}
void enqueue(LD* coada, ComandaOnline co) {//adaugare la final

	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = co;
	nodNou->prev = coada->tail;
	nodNou->next = NULL;

	if (coada->tail != NULL) {
		coada->tail->next = nodNou;
	}
	else {
		coada->head = nodNou;	
	}
	coada->tail = nodNou;
}

ComandaOnline dequeue(LD* coada) { //stergere de la inceput
	ComandaOnline co;
	co.id = -1;

	if (coada->head != NULL) {
		co = coada->head->info;
		Nod* aux = coada->head;

		if (coada->head->next != NULL) {
			coada->head = coada->head->next;
			coada->head->prev = NULL;
		}
		else {
			coada->head =NULL;
			coada->tail = NULL;
		}
		free(aux);
	}
	return co;
}
LD* citireCoadaComenziDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	LD* coada = (LD*)malloc(sizeof(LD));
	coada->head = NULL;
	coada->tail = NULL;
	while (!feof(file)) {
		ComandaOnline co = citireComandaDinFisier(file);
		enqueue(coada, co);
	}
	fclose(file);
	return coada;
}

void afisareQueue(LD* coada) {
	Nod* temp = coada->head;
	while (temp != NULL) {
		afisareComanda(temp->info);
		temp = temp->next;
	}

}

int isQueueEmpty(LD* coada) {
	return coada->head == NULL;
}
void dezalocareQueue(LD** coada) {
	if ((*coada)->head != NULL) {
		ComandaOnline co= dequeue((*coada));
		free(co.adresaLivrare);
		free(co.numeClient);
	}
	(*coada)->head = NULL;
	(*coada)->tail = NULL;
	free((*coada));
	*coada = NULL;
}
void main() {
	LD* coada = citireCoadaComenziDinFisier("comenziOnline.txt");

	afisareQueue(coada);
	ComandaOnline co;
	co.id = 6;
	co.numeClient = "SDD";
	co.adresaLivrare = "Fac";
	co.tipPlata = 'C';
	co.valoare = 900.00f;
	enqueue(coada, co);
	afisareQueue(coada);

	afisareComanda(dequeue(coada));
}