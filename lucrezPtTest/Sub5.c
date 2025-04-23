//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct EvenimentIstoric {
//	char* numeEveniment;
//	int an;
//	char* locatie;
//	char importanta;
//}; 
//typedef struct EvenimentIstoric EvenimentIstoric;
//
//struct Nod {
//	EvenimentIstoric info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//EvenimentIstoric initializareEveniment(const char* numeEveniment, int an, const char*locatie, char importanta) {
//	EvenimentIstoric ev;
//	ev.numeEveniment = malloc(strlen(numeEveniment) + 1);
//	strcpy_s(ev.numeEveniment, strlen(numeEveniment) + 1, numeEveniment);
//
//	ev.an = an;
//	ev.importanta = importanta;
//
//	ev.locatie = malloc(strlen(locatie) + 1);
//	strcpy_s(ev.locatie, strlen(locatie) + 1, locatie);
//	return ev;
//}
//
//void afisareEveniment(EvenimentIstoric e) {
//	printf("Nume: %s\n", e.numeEveniment);
//	printf("An: %d\n", e.an);
//	printf("Locatie: %s\n", e.locatie);
//	printf("Importanta: %c\n\n", e.importanta);
//
//}
//
//void afisareLista(Nod* lista) {
//	while (lista) {
//		afisareEveniment(lista->info);
//		lista = lista->next;
//	}
//}
//void inserareLaInceputInLI(Nod** head, EvenimentIstoric ev) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = ev;
//	nodNou->next = NULL;
//
//	if ((*head)!=NULL) {
//		nodNou->next = (*head);
//		*head = nodNou;
//	}
//	else {
//		*head = nodNou;
//	}
//}
//
//void afisareListaEvenimenteImportante(Nod* head) {
//	while (head) {
//		if (head->info.importanta == 'A') {
//			afisareEveniment(head->info);
//		}
//		head = head->next;
//	}
//}
//
//
//EvenimentIstoric celMaiRecentEveniment(Nod* lista) {
//	EvenimentIstoric e;
//	int anRecent = lista->info.an;
//	while (lista) {
//		if (lista->info.an > anRecent) {
//			e.an = lista->info.an;
//			e.importanta = lista->info.importanta;
//
//			e.numeEveniment = (char*)malloc(strlen(lista->info.numeEveniment) + 1);
//			strcpy_s(e.numeEveniment, strlen(lista->info.numeEveniment) + 1, lista->info.numeEveniment);
//			
//			e.locatie = (char*)malloc(strlen(lista->info.locatie) + 1);
//			strcpy_s(e.locatie, strlen(lista->info.locatie) + 1, lista->info.locatie);
//
//			anRecent = lista->info.an;
//		}
//		lista = lista->next;
//	}
//	return e;
//}
//
//void stergereEvenimenteDupaLocatie(Nod** head, const char* locatieData) {
//	while ((*head) && strcmp((*head)->info.locatie, locatieData) == 0) {
//		Nod* temp = (*head);
//		(*head) = (*head)->next;
//
//		free(temp->info.numeEveniment);
//		free(temp->info.locatie);
//		free(temp);
//
//	}
//
//	Nod* curent = (*head);
//	while (curent && curent->next) {
//		if (strcmp(curent->next->info.locatie, locatieData) == 0) {
//			Nod* temp = curent->next;
//			curent->next = curent->next->next;
//
//			free(temp->info.numeEveniment);
//			free(temp->info.locatie);
//			free(temp);
//		}
//		else {
//			curent = curent->next;
//		}
//	}
//
//}
//
//void dezalocare(Nod** head) {
//	while ((*head)) {
//		Nod* temp = *head;
//		(*head) = (*head)->next;
//
//		free(temp->info.numeEveniment);
//		free(temp->info.locatie);
//		free(temp);
//	}
//}
//
//void main() {
//	Nod* lista = NULL;
//	EvenimentIstoric ev1 = initializareEveniment("Razboi", 1900, "Islaz", 'A');
//	EvenimentIstoric ev2 = initializareEveniment("Pace", 2000, "Bucuresti", 'B');
//	EvenimentIstoric ev3 = initializareEveniment("Tratat", 1990, "Cluj", 'C');
//	EvenimentIstoric ev4 = initializareEveniment("Retragere", 1980, "Turnu", 'A');
//
//	inserareLaInceputInLI(&lista, ev4);
//	inserareLaInceputInLI(&lista, ev3);
//	inserareLaInceputInLI(&lista, ev2);
//	inserareLaInceputInLI(&lista, ev1);
//	afisareLista(lista);
//
//	printf("\n==========================\n");
//	afisareListaEvenimenteImportante(lista);
//}