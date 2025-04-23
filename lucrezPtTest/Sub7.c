#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Conferinta Conferinta;
struct Conferinta {
	char* titlu;
	char* domeniu;
	int an;
	int nrParticipanti;
};

typedef struct Nod Nod;
struct Nod {
	Conferinta info;
	Nod* next;
};

Conferinta citireConferintaDinFisier(FILE* file) {
	char buffer[100];
	char separator[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, separator);
	Conferinta c;

	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.titlu, strlen(aux) + 1, aux);

	aux = strtok(NULL, separator);
	c.domeniu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.domeniu, strlen(aux) + 1, aux);
	aux = strtok(NULL, separator);
	c.an = atoi(aux);
	aux = strtok(NULL, separator);
	c.nrParticipanti = atoi(aux);
	return c;
}

void afisareConferinta(Conferinta c) {
	printf("Conferinta: %s | domeniu: %s | an: %d | participanti: %d\n", c.titlu, c.domeniu, c.an, c.nrParticipanti);

}

void afisareListaSimplaInceput(Nod* lista) {
	Nod* temp = lista;
	while (temp) {
		afisareConferinta(temp->info);
		temp = temp->next;
	}
}

void inserareLaInceputLI(Nod** head, Conferinta conferintaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = conferintaNoua;
	nodNou->next = (*head);
	*head = nodNou;
	
}

void inserareLaFinalLI(Nod** head, Conferinta conferintaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = conferintaNoua;
	nodNou->next = NULL;

	if ((*head) == NULL) {
		*head = nodNou;
	}
	else {
		Nod* temp = (*head);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
}

Nod* citireConferinteDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		inserareLaFinalLI(&lista, citireConferintaDinFisier(f));
	}
	fclose(f);
	return lista;
}


void main() {
	Nod* listaSimpla=citireConferinteDinFisier("conferinte.txt");

	printf("\n====================================\n");
	afisareListaSimplaInceput(listaSimpla);

}