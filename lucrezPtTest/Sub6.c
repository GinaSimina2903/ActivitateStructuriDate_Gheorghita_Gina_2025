#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

typedef struct ComandaOnline ComandaOnline;
struct ComandaOnline {
	int id;
	char* produs;
	float pretTotal;
	char* status;
};
typedef struct Nod Nod;
struct Nod {
	ComandaOnline info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* head;
	Nod* tail;
};

ComandaOnline citireComandaDinFisier(FILE* file) {
	char buffer[100];
	char separator[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, separator);

	ComandaOnline c;
	c.id = atoi(aux);

	aux = strtok(NULL, separator);
	c.produs = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.produs, strlen(aux) + 1, aux);

	aux = strtok(NULL, separator);
	c.pretTotal = atof(aux);

	aux = strtok(NULL, separator);
	c.status = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.status, strlen(aux) + 1, aux);

	return c;
}

void afisareComanda(ComandaOnline c) {
	printf("Comanda cu id: %d | produs: %s | pret: %.2f | status: %s\n", c.id, c.produs, c.pretTotal, c.status);
}

void afisareListaDeLaInceput(ListaDubla lista) {
	Nod* temp = lista.head;
	while (temp) {
		afisareComanda(temp->info);
		temp = temp->next;
	}
}
void inserareLaFinalInLD(ListaDubla* head, ComandaOnline comandaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = comandaNoua;
	nodNou->next = NULL;
	nodNou->prev = head->tail;

	if (head->head==NULL) {
		head->head = nodNou;
	}
	else {
		head->tail->next = nodNou;
	}

	head->tail = nodNou;

}

ComandaOnline comandaPretMaxim(ListaDubla lista) {
	float maxim = lista.head->info.pretTotal;
	ComandaOnline c;
	Nod* temp = lista.head;
	while (temp) {
		if (temp->info.pretTotal > maxim) {
			c.id = temp->info.id;

			c.pretTotal = temp->info.pretTotal;

			c.produs = (char*)malloc(strlen(temp->info.produs) + 1);
			strcpy_s(c.produs, strlen(temp->info.produs) + 1, temp->info.produs);

			c.status = (char*)malloc(strlen(temp->info.status) + 1);
			strcpy_s(c.status, strlen(temp->info.status) + 1, temp->info.status);

			maxim = temp->info.pretTotal;
		}
		temp = temp->next;
	}
	return c;
}

void dezalocare(ListaDubla* lista) {
	if ((*lista).head)
	{
		
		Nod* temp = (*lista).head;
		while (temp->next != NULL) {
			temp = temp->next;
			free(temp->prev->info.produs);
			free(temp->prev->info.status);
			free(temp->prev);
		}
		free(temp->info.produs);
		free(temp->info.status);
		free(temp);
		(*lista).head = NULL;
		(*lista).tail = NULL;
	}
}

ListaDubla citireComenziDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;

	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareLaFinalInLD(&lista, citireComandaDinFisier(f));
	}
	fclose(f);
	return lista;
}
 
 
void main() {
	ListaDubla lista = citireComenziDinFisier("comenzi.txt");

	printf("\n--------------------------\n");
	afisareListaDeLaInceput(lista);

	printf("\n--------------------------\n");
	afisareComanda(comandaPretMaxim(lista));

	dezalocare(&lista);
	
}