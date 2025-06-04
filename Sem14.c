#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara
typedef struct NodListaSecundara NodListaSecundara;
typedef struct NodListaPrincipala NodListaPrincipala;

struct NodListaPrincipala {
	NodListaPrincipala* next;
	NodListaSecundara* vecini;
	Masina info;
};

struct NodListaSecundara {
	NodListaPrincipala* info;
	NodListaSecundara* next;
};


//2.
//functii de inserare in liste
//si in principala si in secundara
NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info) {
	// inserare la sfarsit
	NodListaPrincipala* nou = (NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
	nou->info = info;
	nou->next = NULL;
	nou->vecini = NULL;

	if (!cap) {
		return nou;
	}

	NodListaPrincipala* p = cap;
	while (p->next) {
		p = p->next;
	}
	p->next = nou;
	return cap;
}

NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info) {
	// inserare la inceput
	NodListaSecundara* nou = (NodListaSecundara*)malloc(sizeof(NodListaSecundara));
	nou->info = info;
	nou->next = NULL;

	nou->next = cap;
	return nou;
}


//3.
//functie de cautarea in lista principala dupa ID
NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
	while (listaPrincipala && listaPrincipala->info.id != id) {
		listaPrincipala = listaPrincipala->next;
	}
	return listaPrincipala;
}

//4.
//inserare muchie
void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
	NodListaPrincipala* nodStart = cautaNodDupaID(listaPrincipala, idStart);
	NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop); // in ambele pt ca e graf neorientat
		nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
	}
}

NodListaPrincipala* citireNoduriMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	NodListaPrincipala* listaPrincipala = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(file));
	}
	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala, const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		int idStart;
		int idStop;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
	fclose(f);
}

void stergereListaSecundara(NodListaSecundara** cap) {
	NodListaSecundara* aux = (*cap)->next;
	while ((*cap)) {
		aux = (*cap)->next;
		free((*cap));
		(*cap) = aux;
	}
}

void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
	NodListaPrincipala* aux;
	while ((*listaPrincipala)) {
		aux = (*listaPrincipala)->next;
		stergereListaSecundara((*listaPrincipala)->vecini);
		free((*listaPrincipala)->info.numeSofer);
		free((*listaPrincipala)->info.model);
		free(listaPrincipala);
		(*listaPrincipala) = aux;
	}
}

//parcurgerea in adancime
//plecam de la un nod si cautam vecinii acestui nod

//Parcurgere in adancime

//creare structura Stiva

typedef struct Stiva Stiva;
struct Stiva {
	int id;
	Stiva* next;
};

void push(Stiva** cap, int id) {
	Stiva* nou = (Stiva*)malloc(sizeof(Stiva));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}

int pop(Stiva** cap) {
	if (*cap) {
		Stiva* temp = (*cap);
		(*cap) = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else {
		return -1;
	}
}
//push si pop pentru stiva
int calculeazaNrNoduriGraf(NodListaPrincipala* listaPrincipala) {
	int contor = 0;
	while (listaPrincipala!=NULL) {
		contor++;
		listaPrincipala = listaPrincipala->next;
		
	}
	return contor;
}

void afisareGrafInAdancime(NodListaPrincipala* listaPrincipala, int idPlecare) {
	/*
	1. Este luata o STIVA si un vector de vizitate
	2. Marcam nodul de plecare ca fiind vizitat si il adaugam in STIVA noastra
	3. Pornim parcurgerea care va rula cat timp avem noduri in STIVA
	4.1 Extragem un nod din STIVA
	4.2 Procesam nodul extras din STIVA - il afisam
	4.3. identificam toti vecinii nodului extras care nu sunt vizitati si ii marcam ca vizitati, adugandu-i in STIVA
	4.4 reluam procesul
	*/

	Stiva* stiva=NULL;
	int nrNoduri = (unsigned char)calculeazaNrNoduriGraf(listaPrincipala);
	unsigned char* vizitate = (unsigned char*)malloc(sizeof(unsigned char)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	push(&stiva, idPlecare);
	while (stiva !=	NULL) {
		int idCurent = pop(&stiva);
		NodListaPrincipala* nodCurent = cautaNodDupaID(listaPrincipala, idCurent);
		afisareMasina(nodCurent->info);
		NodListaSecundara* temp = nodCurent->vecini;
		while (temp) {
			if (vizitate[temp->info->info.id - 1] == 0) {
				push(&stiva, temp->info->info.id);
				vizitate[temp->info->info.id - 1] = 1;
			}
			temp = temp->next;
		}
	}
}

//creare structura coada
//enqueue si dequeue pentru coada

typedef struct Stiva Coada;

void enqueue(Coada** cap, int id) {
	Coada* nou = (Coada*)malloc(sizeof(Coada));
	nou->id = id;
	nou->next = NULL;

	if ((*cap) != NULL) {
		Coada* temp = (*cap);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		(*cap) = nou;
	}
}


int dequeue(Stiva** cap)
{
	int id = pop(cap);
	return id;
}

void afisareGrafInLatime(NodListaPrincipala* listaPrincipala, int idPlecare) {
	/*
	1. Este luata o COADA si un vector de vizitate
	2. Marcam nodul de plecare ca fiind vizitat si il adaugam in COADA noastra
	3. Pornim parcurgerea care va rula cat timp avem noduri in COADA
	4.1 Extragem un nod din stiva
	4.2 Procesam nodul extras din COADA - il afisam
	4.3. identificam toti vecinii nodului extras care nu sunt vizitati si ii marcam ca vizitati, adugandu-i in COADA
	4.4 reluam procesul
	*/

	Coada* coada = NULL;

	int nrNoduri = (unsigned char)calculeazaNrNoduriGraf(listaPrincipala);
	unsigned char* vizitate = (unsigned char*)malloc(sizeof(unsigned char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	enqueue(&coada, idPlecare);
	while (coada != NULL) {
		int idCurent = dequeue(&coada);
		NodListaPrincipala* nodCurent = cautaNodDupaID(listaPrincipala, idCurent);
		afisareMasina(nodCurent->info);
		NodListaSecundara* temp = nodCurent->vecini;
		while (temp) {
			if (vizitate[temp->info->info.id - 1] == 0) {
				enqueue(&coada, temp->info->info.id);
				vizitate[temp->info->info.id - 1] = 1;
			}
			temp = temp->next;
		}
	}
}


int main() {
	NodListaPrincipala* graf = citireNoduriMasiniDinFisier("masini.txt");

	citireMuchiiDinFisier(graf, "muchii.txt");
	afisareGrafInAdancime(graf, 1);

	afisareGrafInLatime(graf, 1);
	dezalocareNoduriGraf(&graf);

	return 0;
}