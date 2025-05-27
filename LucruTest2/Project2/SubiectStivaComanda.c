//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//typedef struct Comanda Comanda;
//struct Comanda {
//	int id;
//	char* dataProcesare;
//	char* datcaLivrare;
//	char* numeClient;
//	float pret;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* next;
//	Comanda info;
//};
//
//Comanda citireComandaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//
//	Comanda c;
//
//	aux = strtok(buffer, sep);
//	c.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	c.dataProcesare = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(c.dataProcesare, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	c.datcaLivrare = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(c.datcaLivrare, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	c.numeClient = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(c.numeClient, strlen(aux) + 1, aux);
//	return c;
//}
//
//void afisareComanda(Comanda c) {
//	printf("id: %d\n", c.id);
//	printf("data procesare:  %s\n", c.dataProcesare);
//	printf("data livrare:  %s\n", c.datcaLivrare);
//	printf("nume client: %s\n\n", c.numeClient);
//}
//
//void pushStack(Nod** stiva, Comanda c) {//adaugare la inceput
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = c;
//	nodNou->next = (*stiva);
//	(*stiva) = nodNou;
//}
//
//Comanda popStack(Nod** stiva) {//stergere de la inceput
//	
//	if ((*stiva) != NULL) {
//		Comanda c = (*stiva)->info;
//		Nod* prev = (*stiva); //retinem capul stivei
//		(*stiva) = (*stiva)->next; //ne mutam la urm element, practic scoatem mutam capul de lista
//		free(prev); //dam afara din lista, nu doar ascundem!
//		return c;
//	}
//	else {
//		Comanda c;
//		c.id = -1;
//		return c;
//	}
//
//}
//
//unsigned char emptyStack(Nod* stiva) {
//	return stiva == NULL;
//}
//
//Nod* citireStivaDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* stiva = NULL;
//
//	while (!feof(file)) {
//		Comanda c = citireComandaDinFisier(file);
//		//pushStiva
//		pushStack(&stiva, c);
//	}
//	fclose(file);
//	return stiva;
//}
//
//void afisareStack(Nod* stiva) {
//	printf("\n\n===== afisare stack ======\n\n");
//	while (stiva != NULL) {
//		afisareComanda(stiva->info);
//		stiva = stiva->next;
//	}
//}
//
//int sizeStack(Nod* stiva) {
//	int size = 0;
//	while (stiva != NULL) {
//		size++;
//		stiva = stiva->next;
//	}
//	return size;
//}
//void dezalocareStiva(Nod** stiva) {
//	while ((*stiva) != NULL) {
//		Comanda c = popStack(stiva);
//		free(c.dataProcesare);
//		free(c.datcaLivrare);
//		free(c.numeClient);
//	}
//	*stiva = NULL;
//}
//void main() {
//	Nod* stiva = citireStivaDinFisier("comenzi.txt");
//
//	afisareStack(stiva);
//	Comanda c;
//	c.id = 6;
//	c.dataProcesare = "6 octombrie";
//	c.datcaLivrare = "9 octombrie";
//	c.numeClient = "Jani";
//	c.pret = 200.00f;
//	pushStack(&stiva, c);
//	afisareStack(stiva);
//
//	printf("\n\n====== pop stack====\n");
//	afisareComanda(popStack(&stiva));
//
//	printf("\n\n stack size = %d\n\n", sizeStack(stiva));
//
//	printf("%d", emptyStack(stiva));
//
//	dezalocareStiva(&stiva);
//
//	printf("%d", emptyStack(stiva));
//}