//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//typedef struct Document Document;
//struct Document {
//	int id;
//	int nrpag;
//	char* titlu;
//	char* autor;
//	float dimensiuneMB;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* next;
//	Document info;
//};
//
//Document citireDocumentDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Document d;
//
//	aux = strtok(buffer, sep);
//	d.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	d.nrpag = atoi(aux)
//		;
//	aux = strtok(NULL, sep);
//	d.titlu = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(d.titlu, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	d.autor = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(d.autor, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	d.dimensiuneMB = atof(aux);
//	return d;
//}
//
//void pushStack(Nod** stiva, Document d) { //inserare la inceput
//		Nod* nodnou = (Nod*)malloc(sizeof(Nod));
//		nodnou->info = d;
//		nodnou->next = NULL;
//		(*stiva) = nodnou;	
//}
//
//Document popStack(Nod** stiva) { //stergere la inceput
//	if ((*stiva) != NULL) {
//		Document nou = (*stiva)->info;
//		Nod* prev = (*stiva);
//		(*stiva) = (*stiva)->next;
//		free(prev);
//		return nou;
//	}
//	Document d;
//	d.id = -1;
//	return d;
//
//}
//
//void citireStivaDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* stiva = NULL;
//	while (!feof(file)) {
//		Document d = citireDocumentDinFisier(file);
//		pushStack(&stiva, d);
//	}
//	fclose(file);
//	return stiva;
//}
//
//void main() {
//	
//}