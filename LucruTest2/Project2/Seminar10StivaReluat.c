//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector  --folosim lsi
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	Nod* next;
//};
//
//void pushStack(Nod** stiva, Masina masina) {  //inserarea la inceput
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masina;
//	nodNou->next = (*stiva);
//	(*stiva) = nodNou;
//}
//
//Masina popStack(Nod** stiva) {  //stergere la inceput
//	if ((*stiva) != NULL) {
//		Masina nou = (*stiva)->info;
//		Nod* prev = (*stiva);
//		(*stiva) = (*stiva)->next;
//		free(prev);
//		return nou;
//	}
//	Masina m;
//	m.id = -1;
//	return m;
//}
//
//unsigned char emptyStack(Nod** stiva) {
//	return stiva == NULL;
//}
//
//void* citireStackMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* stiva = NULL;
//
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		pushStack(&stiva, m);
//	}
//	fclose(file);
//	return stiva;
//
//}
//
//void dezalocareStivaDeMasini(Nod** stiva) {
//	//sunt dezalocate toate masinile si stiva de elemente
//	while ((*stiva) != NULL) {
//		Masina m = popStack(stiva);
//		free(m.numeSofer);
//		free(m.model);
//	}
//	
//	(*stiva) = NULL;
//}
//
//int sizeSTACK(Nod* stiva) {
//	//returneaza numarul de elemente din stiva
//	int nr = 0;
//	while (stiva != NULL) {
//		nr++;
//		stiva = stiva->next;
//	}
//	return nr;
//}
//
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector  --ldi
//
//typedef struct NodDublu NodDublu;
//struct NodDublu {
//	NodDublu* next;
//	NodDublu* prev;
//	Masina info;
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//	NodDublu* head;
//	NodDublu* tail;
//};
//
//void enqueue(ListaDubla* coada, Masina masina) { //adaugare la final
//	//adauga o masina in coada
//	NodDublu* nodnou = (NodDublu*)malloc(sizeof(NodDublu));
//	nodnou->info = masina;
//	nodnou->next = NULL;
//	nodnou->prev = coada->tail;
//
//	if (coada->tail != NULL) {
//		coada->tail->next = nodnou;
//	}
//	else {
//		coada->head = nodnou;
//	}
//
//	coada->tail = nodnou;
//}
//
//Masina dequeue(ListaDubla* coada) { //stergere de la inceput
//	//extrage o masina din coada
//	Masina m;
//	m.id = -1;
//
//	if (coada->head != NULL) {
//		m = coada->head->info;
//		NodDublu* aux = coada->head;
//
//		if (coada->head->next != NULL) {
//			coada->head = coada->head->next;
//			coada->head->prev = NULL;
//		}
//		else {
//			coada->head = NULL;
//			coada->tail = NULL;
//		}
//		free(aux);
//	}
//	return m;
//}
//
//void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	ListaDubla* coada=(ListaDubla*)malloc(sizeof(ListaDubla));;
//	coada->head = NULL;
//	coada->tail = NULL;
//
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		enqueue(&coada, m);
//	}
//	fclose(file);
//	return coada;
//}
//
//void dezalocareCoadaDeMasini(ListaDubla** coada) {
//	//sunt dezalocate toate masinile si coada de elemente
//	while ((*coada)->head!=NULL) {
//		Masina m=dequeue(coada);
//		free(m.model);
//		free(m.numeSofer);
//	}
//	(*coada)->head = NULL;
//	(*coada)->tail = NULL;
//	free(*coada);
//	*coada = NULL;
//}
//
//
////metode de procesare
//Masina getMasinaByID(ListaDubla* coada, int id) {
//	Masina rezultat;
//	rezultat.id = -1; // marcãm cã nu s-a gãsit
//
//	ListaDubla temporara;
//	temporara.head = NULL;
//	temporara.tail = NULL;
//
//	while (coada->head != NULL) {
//		Masina m = dequeue(coada);
//		if (m.id == id && rezultat.id == -1) {
//			rezultat = m;
//			// copiem adânc string-urile ca sã nu le pierdem la reenqueue
//			rezultat.model = malloc(strlen(m.model) + 1);
//			strcpy_s(rezultat.model, strlen(m.model) + 1, m.model);
//			rezultat.numeSofer = malloc(strlen(m.numeSofer) + 1);
//			strcpy_s(rezultat.numeSofer, strlen(m.numeSofer) + 1, m.numeSofer);
//		}
//		enqueue(&temporara, m); // pãstrãm ordinea
//	}
//
//	// restaurãm coada originalã
//	coada->head = temporara.head;
//	coada->tail = temporara.tail;
//
//	return rezultat;
//}
//
//
//float calculeazaPretTotal(ListaDubla* coada) {
//	float suma = 0;
//	ListaDubla temporara;
//	temporara.head = NULL;
//	temporara.tail = NULL;
//
//	while (coada->head != NULL) {
//		Masina m = dequeue(coada);
//		suma += m.pret;
//		enqueue(&temporara, m); // salvãm pentru restaurare
//	}
//
//	coada->head = temporara.head;
//	coada->tail = temporara.tail;
//
//	return suma;
//}
//
//
//int main() {
//	/*Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//
//	int nr = sizeSTACK(stiva);
//	printf("Nr de elemente in stiva: %d\n\n", nr);
//
//	Masina m = popStack(&stiva);
//	afisareMasina(m);
//	free(m.model);
//	free(m.numeSofer);
//
//	m = popStack(&stiva);
//	afisareMasina(m);*/
//
//	return 0;
//}