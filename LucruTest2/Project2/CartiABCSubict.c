//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//typedef struct Carte Carte;
//struct Carte {
//	int id;
//	int nrPagini;
//	float pret;
//	char* titlu;
//	char* autor;
//	unsigned char serie;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	Carte info;
//};
//
//Carte citireCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Carte c;
//
//	aux = strtok(buffer,sep);
//	c.id = atoi(aux);
//	
//	aux = strtok(NULL, sep);
//	c.nrPagini = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	c.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	c.titlu = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(c.titlu, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	c.autor = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(c.autor, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	c.serie = *aux;
//	return c;
//}
//
//void afisareCarte(Carte c) {
//	printf("ID: %d\n", c.id);
//	printf("nrpagini: %d\n", c.nrPagini);
//	printf("pret: %.2f\n", c.pret);
//	printf("titlu: %s\n", c.titlu);
//	printf("autor: %s\n\n", c.autor);
//}
//
//void adaugaCarteInArbore(Nod** radacina, Carte c){ //dupa id
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > c.id) {
//			adaugaCarteInArbore(&((*radacina)->st), c);
//		}
//		else if((*radacina)->info.id <c.id) {
//			adaugaCarteInArbore(&((*radacina)->dr), c);
//		}
//		else {
//			(*radacina)->info = c;
//
//			if ((*radacina)->info.titlu != NULL) {
//				free((*radacina)->info.titlu);
//			}
//
//			if ((*radacina)->info.autor != NULL) {
//				free((*radacina)->info.autor);
//			}
//
//			(*radacina)->info.titlu = (char*)malloc(strlen(c.titlu) + 1);
//			strcpy_s((*radacina)->info.titlu, strlen(c.titlu) + 1, c.titlu);
//
//			(*radacina)->info.autor = (char*)malloc(strlen(c.autor) + 1);
//			strcpy_s((*radacina)->info.autor, strlen(c.autor) + 1, c.autor);
//		}
//	}
//	else {
//		(*radacina) = malloc(sizeof(Nod));
//		(*radacina)->info = c;
//
//		(*radacina)->info.autor = (char*)malloc(strlen(c.autor)+1);
//		strcpy_s((*radacina)->info.autor, strlen(c.autor) + 1, c.autor);
//
//		(*radacina)->info.titlu = (char*)malloc(strlen(c.titlu) + 1);
//		strcpy_s((*radacina)->info.titlu, strlen(c.titlu) + 1, c.titlu);
//
//		(*radacina)->st = NULL;
//		(*radacina)->dr = NULL;	
//	}
//}
//
//
//Nod* citireArboreDinFisier(const char* numefisier) {
//	FILE* file = fopen(numefisier, "r");
//	Nod* radacina=NULL;
//
//	while (!feof(file)) {
//		Carte c = citireCarteDinFisier(file);
//		adaugaCarteInArbore(&radacina, c);
//		//adauga aici carte in arbore
//
//		free(c.autor);
//		free(c.titlu);
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisareArboreINORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareArboreINORDINE(radacina->st);
//		afisareCarte(radacina->info);
//		afisareArboreINORDINE(radacina->dr);
//	}
//}
//
//void afisarePREORDINE(Nod* radacina) {
//	if(radacina!=NULL){
//		afisareCarte(radacina->info);
//		afisarePREORDINE(radacina->st);
//		afisarePREORDINE(radacina->dr);
//	}
//}
//
//void afisarePOSTORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisarePOSTORDINE(radacina->st);
//		afisarePOSTORDINE(radacina->dr);
//		afisareCarte(radacina->info);
//	}
//}
//
//int nrTotalCarti(Nod* radacina) {
//	if (radacina != NULL) {
//		return 1 + nrTotalCarti(radacina->st) + nrTotalCarti(radacina->dr);
//	}
//	return 0;
//
//}
//
//Carte getCarteByID(Nod* radacina, int id) {
//	Carte c;
//	if (radacina != NULL) {
//		if (radacina->info.id > c.id) {
//			c = getCarteByID(radacina->st, id);
//		}
//		else if (radacina->info.id < c.id) {
//			c = getCarteByID(radacina->dr, id);
//		}
//		else {
//			radacina->info = c;
//			radacina->info.titlu = (char*)malloc(strlen(c.titlu) + 1);
//			strcpy_s(radacina->info.titlu, strlen(c.titlu) + 1, c.titlu);
//
//			radacina->info.autor = (char*)malloc(strlen(c.autor) + 1);
//			strcpy_s(radacina->info.autor, strlen(c.autor) + 1, c.autor);
//		}
//	}
//	else {
//		c.id = -1;
//		c.nrPagini = 0;
//		c.pret = 0.0f;
//		c.serie = '-';
//		c.autor = NULL;
//		c.titlu = NULL;
//	}
//	return c;
//}
//
//float pretTotalCarti(Nod* radacina) {
//	if (radacina != NULL) {
//		float suma = radacina->info.pret;
//		
//		float sumaST = pretTotalCarti(radacina->st);
//		float sumaDR = pretTotalCarti(radacina->dr);
//
//		return suma + sumaST + sumaDR;
//	}
//	return 0;
//}
//
//int calculeazaInaltimeArbore(Nod*radacina) {
//	if (radacina != NULL) {
//		int inaltimeST = calculeazaInaltimeArbore(radacina->st);
//		int inaltimeDR = calculeazaInaltimeArbore(radacina->dr);
//
//		if (inaltimeST > inaltimeDR) {
//			return 1 + inaltimeST;
//		}
//		else {
//			return 1 + inaltimeDR;
//		}
//	}
//	return 0;
//}
//
//int afisareNrTotalCartiAutor(Nod* radacina, const char* autorCautat) {
//	if (radacina != NULL) {
//		int nrtotal = 0;
//		int nrTotalST = afisareNrTotalCartiAutor(radacina->st, autorCautat);
//		int nrTotalDR = afisareNrTotalCartiAutor(radacina->dr, autorCautat);
//
//		if (strcmp(radacina->info.autor, autorCautat) == 0) {
//			nrtotal += 1;
//			
//		} 
//		return nrtotal + nrTotalST + nrTotalDR;
//	}
//	return 0;
//}
//
//void dezalocare(Nod** radacina)
//{
//	if ((*radacina) != NULL) {
//		dezalocare(&((*radacina)->st));
//		dezalocare(&((*radacina)->dr));
//		free((*radacina)->info.autor);
//		free((*radacina)->info.titlu);
//		free((*radacina));
//		(*radacina) = NULL;
//	}
//}
//void main() {
//	Nod* arbore = citireArboreDinFisier("carti.txt");
//
//	printf("\n\n =========== IN ORDINE =========\n");
//	afisareArboreINORDINE(arbore);
//
//	printf("\n\n =========== PRE ORDINE =========\n");
//	afisarePREORDINE(arbore);
//
//	printf("\n\n =========== POST ORDINE =========\n");
//	afisarePOSTORDINE(arbore);
//
//	Carte c;
//	c.id = 11;
//	c.nrPagini = 260;
//	c.pret = 99.99f;
//	c.serie = 'S';
//	c.titlu = (char*)malloc(strlen("Titlu11") + 1);
//	strcpy_s(c.titlu, strlen("Titlu11") + 1, "Titlu11");
//
//	c.autor = (char*)malloc(strlen("Autor11") + 1);
//	strcpy_s(c.autor, strlen("Autor11") + 1, "Autor11");
//
//	adaugaCarteInArbore(&arbore, c);
//	afisareArboreINORDINE(arbore);
//
//	dezalocare(&arbore);
//}