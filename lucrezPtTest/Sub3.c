#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AplicatieMobila {
	char* denumire;
	float marimeMB;
	int nrDescarcari;
	int anulLansarii;
};
typedef struct AplicatieMobila AplicatieMobila;

struct Nod {
	AplicatieMobila info;
	struct Nod* next;
};
typedef struct Nod Nod;

AplicatieMobila initializareAplicatie(const char* denumire, float marimeMB, int nrDescarcari, int anulLansarii) {
	AplicatieMobila apl;
	apl.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(apl.denumire, strlen(denumire) + 1, denumire);

	apl.marimeMB = marimeMB;
	apl.nrDescarcari = nrDescarcari;
	apl.anulLansarii = anulLansarii;

	return apl;
}

void afisareAplicatieMobila(AplicatieMobila apl) {
	printf_s("Aplicatia: %s | Marimea in MB: %.2f | Descarcari: %d | An lansare: %d\n",
		apl.denumire, apl.marimeMB, apl.nrDescarcari, apl.anulLansarii);
}

void afisareLista(Nod* head) {
	while (head) {
		afisareAplicatieMobila(head->info);
		head = head->next;
	}
}

void inserareInLI(Nod** head, AplicatieMobila aplicatieMobilaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = aplicatieMobilaNoua;
	nodNou->next = NULL;	

	if ((*head) == NULL) {
		(*head) = nodNou;
	}
	else {
		Nod* temp = (*head);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
}

AplicatieMobila afisareMinSpatiu(Nod* head) {
	float  minim = head->info.marimeMB;
	AplicatieMobila apl;
	while (head) {
		if (head->info.marimeMB < minim) {
			apl.denumire = (char*)malloc(strlen(head->info.denumire)+1);
			strcpy_s(apl.denumire, strlen(head->info.denumire) + 1, head->info.denumire);

			apl.anulLansarii = head->info.anulLansarii;
			apl.nrDescarcari = head->info.nrDescarcari;
			apl.marimeMB = head->info.marimeMB;

			minim = head->info.marimeMB;
		}
		head = head->next;
	}
	return apl;
}

Nod* stergereAplicatieDupaDenumire(Nod** head, const char* denumire) {
	while ((*head) != NULL && strcmp((*head)->info.denumire, denumire)==0) {
		Nod* temp = (*head);
		(*head) = (*head)->next;

		free(temp->info.denumire);
		free(temp);
	}

	Nod* curent = *head;
	while (curent && curent->next) {
		if (strcmp(curent->next->info.denumire, denumire) == 0) {
			Nod* temp = curent->next;
			curent->next = curent->next->next;

			free(temp->info.denumire);
			free(temp);
		}
		else {
			curent = curent->next;
		}
	}
}

Nod* dezalocare(Nod** head) {
	while ((*head)) {
		Nod* temp = (*head);
		(*head) = (*head)->next;

		free(temp->info.denumire);
		free(temp);
	}
}

void main() {
	Nod* listaSimpla = NULL;
	AplicatieMobila apl1 = initializareAplicatie("Brawl Stars", 500.0, 10000, 2014);
	AplicatieMobila apl2 =initializareAplicatie("Facebook", 1000.0, 500000, 2011);
	AplicatieMobila apl3 = initializareAplicatie("WhatsApp", 200.0, 60000, 2010);
	AplicatieMobila apl4 = initializareAplicatie("Instagram", 300.0, 200000, 2012);	
	AplicatieMobila apl5 = initializareAplicatie("Telegram", 400.0, 300000, 2013);

	inserareInLI(&listaSimpla, apl1);
	inserareInLI(&listaSimpla, apl2);
	inserareInLI(&listaSimpla, apl3);
	inserareInLI(&listaSimpla, apl4);
	inserareInLI(&listaSimpla, apl5);

	afisareLista(listaSimpla);

	printf("\n===========================================\n");
	afisareAplicatieMobila(afisareMinSpatiu(listaSimpla));
	
	printf("\n===================STERGERE========================\n");
	afisareLista(listaSimpla);
	stergereAplicatieDupaDenumire(&listaSimpla, "Instagram");
	printf("\n===========================================\n");
	afisareLista(listaSimpla);

	dezalocare(&listaSimpla);

}