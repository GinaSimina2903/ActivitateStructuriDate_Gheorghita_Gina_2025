#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CarteTarot {
	char* nume;
	int tipArcana;
	char* simbol;
	float energie;
};
typedef struct CarteTarot CarteTarot;

struct Nod {
	CarteTarot info;
	struct Nod* prev;
	struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* head;
	Nod* tail;
};
typedef struct ListaDubla ListaDubla; 

struct NodSimplu {
	CarteTarot info;
	struct NodSimplu* next;
};
typedef struct NodSimplu NodSimplu;

CarteTarot initializareCarteTarot(const char* nume, int tipArcana, const char*simbol, float energie) {
	CarteTarot carte;
	carte.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(carte.nume, strlen(nume) + 1, nume);

	carte.tipArcana = tipArcana;

	carte.simbol = (char*)malloc(strlen(simbol) + 1);
	strcpy_s(carte.simbol, strlen(simbol) + 1, simbol);

	carte.energie = energie;
	return carte;
}

void afisareCarteTarot(CarteTarot carte) {
	printf("Numele cartii: %s\n", carte.nume);
	printf("Tipul Arcanei: %d\n", carte.tipArcana);
	printf("Simbolul: %s\n", carte.simbol);
	printf("Energie: %.2f\n", carte.energie);
	printf("\n");
}

void afisareLista(ListaDubla lista) {
	Nod* temp = lista.head;
	while (temp) {
		afisareCarteTarot(temp->info);
		temp = temp->next;
	}
}

void parcurgereAfisarefinal(ListaDubla lista) {
	Nod* temp = lista.tail;
	while (temp) {
		afisareCarteTarot(temp->info);
		temp = temp->prev;
	}
}

void inserareInLDLaInceput(ListaDubla* lista, CarteTarot carteTarotNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteTarotNoua;
	nodNou->next = lista->head;
	nodNou->prev = NULL;

	if (lista->head == NULL) {
		lista->tail = nodNou;
	}
	else {
		lista->head->prev = nodNou;
	}
	lista->head = nodNou;
}

void inserareInLDLaFinal(ListaDubla* lista, CarteTarot carteTarotNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteTarotNoua;
	nodNou->next = NULL;
	nodNou->prev = lista->tail;

	if (lista->tail == NULL) {
		lista->head = nodNou;
	}
	else {
		lista->tail->next = nodNou;
	}
	lista->tail = nodNou;
}

CarteTarot carteEnergieMaxima(ListaDubla lista) {
	CarteTarot carte;
	float maxim = lista.head->info.energie;
	while (lista.head) {
		if (lista.head->info.energie > maxim) {
			carte.energie = lista.head->info.energie;
			carte.tipArcana = lista.head->info.tipArcana;

			carte.nume = (char*)malloc(strlen(lista.head->info.nume) + 1);
			strcpy_s(carte.nume, strlen(lista.head->info.nume) + 1, lista.head->info.nume);

			carte.simbol = (char*)malloc(strlen(lista.head->info.simbol) + 1);
			strcpy_s(carte.simbol, strlen(lista.head->info.simbol) + 1, lista.head->info.simbol);

			maxim = lista.head->info.energie;
		}
		lista.head = lista.head->next;
	}
	return carte;
}

void stergereCartiCuSimbol(ListaDubla* lista, const char* simbol) {
	Nod* temp = lista->head;
	while (temp != NULL) {
		Nod* urmator = temp->next;

		if (strcmp(temp->info.simbol, simbol) == 0) {
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			else
				lista->head = temp->next;

			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			else
				lista->tail = temp->prev;

			free(temp->info.nume);
			free(temp->info.simbol);
			free(temp);
		}

		temp = urmator;
	}
}

void transferaCartiDinDublaInSimpla(ListaDubla listaDubla, NodSimplu** listaSimpla) {
	Nod* temp = listaDubla.head;
	while (temp) {
		// Alocăm nod nou pentru lista simplă
		NodSimplu* nodNou = (NodSimplu*)malloc(sizeof(NodSimplu));

		// Copiem conținutul (deep copy)
		nodNou->info.nume = (char*)malloc(strlen(temp->info.nume) + 1);
		strcpy_s(nodNou->info.nume, strlen(temp->info.nume) + 1, temp->info.nume);

		nodNou->info.simbol = (char*)malloc(strlen(temp->info.simbol) + 1);
		strcpy_s(nodNou->info.simbol, strlen(temp->info.simbol) + 1, temp->info.simbol);

		nodNou->info.tipArcana = temp->info.tipArcana;
		nodNou->info.energie = temp->info.energie;

		nodNou->next = NULL;

		// Inserăm la final în lista simplă
		if (*listaSimpla == NULL) {
			*listaSimpla = nodNou;
		}
		else {
			NodSimplu* aux = *listaSimpla;
			while (aux->next != NULL) {
				aux = aux->next;
			}
			aux->next = nodNou;
		}

		temp = temp->next;
	}
}

void afisareListaSimpla(NodSimplu* cap) {
	while (cap) {
		afisareCarteTarot(cap->info);
		cap = cap->next;
	}
}


void dezalocareMemorie(ListaDubla* lista) {
	Nod* temp = lista->head;
	while (temp != NULL) {
		Nod* deSters = temp;
		temp = temp->next;

		free(deSters->info.nume);
		free(deSters->info.simbol);
		free(deSters);
	}

	lista->head = NULL;
	lista->tail = NULL;
}


void main() {
	CarteTarot carte1 = initializareCarteTarot("Regele de Cupe", 1, "Negativitate", 200.0);
	CarteTarot carte2 = initializareCarteTarot("Regina de Spade", 0, "Iubire", 1000.0);
	CarteTarot carte3 = initializareCarteTarot("Nebunul", 0, "Avutie", 500.0);
	CarteTarot carte4 = initializareCarteTarot("Printesa", 1, "Prietenie", 100.0);

	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;

	afisareCarteTarot(carte1);
	printf("\n==========================\n");
	inserareInLDLaInceput(&lista, carte1);
	afisareLista(lista);

	inserareInLDLaFinal(&lista, carte2);
	inserareInLDLaFinal(&lista, carte3);
	inserareInLDLaFinal(&lista, carte4);

	printf("\n============= LISTA FINALA ============\n");
	afisareLista(lista);

	printf("\n============= LISTA INVERS ============\n");
	parcurgereAfisarefinal(lista);

	printf("\n\n====== MAXIM ENERGIE ==============\n");
	afisareCarteTarot(carteEnergieMaxima(lista));

	CarteTarot carte5 = initializareCarteTarot("Print", 0, "Turn", 300.0);
	CarteTarot carte6 = initializareCarteTarot("Tura", 1, "Turn", 400.0);
	inserareInLDLaFinal(&lista, carte5);
	inserareInLDLaFinal(&lista, carte6);
	afisareLista(lista);


	printf("\n\n====== lista sters turn ==============\n");
	const char* simbolTrimis = "Turn";
	stergereCartiCuSimbol(&lista, simbolTrimis);
	afisareLista(lista);

	/*NodSimplu* listaSimpla = NULL;
	transferaCartiDinDublaInSimpla(lista, &listaSimpla);
	printf("\n\n\n==========================\n");
	afisareListaSimpla(listaSimpla);*/
	dezalocareMemorie(&lista);
}