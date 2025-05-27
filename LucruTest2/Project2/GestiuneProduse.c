//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct Produs Produs;
//struct Produs {
//	int id;
//	float pret;
//	char* denumire;
//	unsigned char categorie;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	Produs info;
//};
//
//Produs citireDinFisierProdus(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Produs p;
//
//	aux = strtok(buffer, sep);
//	p.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	p.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	p.denumire = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(p.denumire, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	p.categorie = *aux;
//	return p;
//}
//
//void afisareProdus(Produs p) {
//	printf("id: %d\n", p.id);
//	printf("pret: %.2f\n", p.pret);
//	printf("denumire: %s\n", p.denumire);
//	printf("categorie: %c\n\n", p.categorie);
//}
//
//void adaugaProdusInArbore(Nod** radacina, Produs p) {
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > p.id) {
//			adaugaProdusInArbore(&((*radacina)->st), p);
//		}
//		else if((*radacina)->info.id < p.id) {
//			adaugaProdusInArbore(&((*radacina)->dr), p);
//		}
//		else {
//			(*radacina)->info = p;
//			if ((*radacina)->info.denumire != NULL) {
//				free((*radacina)->info.denumire);
//			}
//			(*radacina)->info.denumire = (char*)malloc(strlen(p.denumire) + 1);
//			strcpy_s((*radacina)->info.denumire, strlen(p.denumire) + 1, p.denumire);
//		}
//	}
//	else {
//		(*radacina) =(Nod*)malloc(sizeof(Nod));
//		(*radacina)->info = p;
//		(*radacina)->info.denumire = (char*)malloc(strlen(p.denumire) + 1);
//		strcpy_s((*radacina)->info.denumire, strlen(p.denumire) + 1, p.denumire);
//		(*radacina)->st = NULL;
//		(*radacina)->dr = NULL;
//	}
//
//}
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* radacina = NULL;
//	
//	while(!feof(file)) {
//		Produs p = citireDinFisierProdus(file);
//		adaugaProdusInArbore(&radacina, p);
//		free(p.denumire);
//	}
//
//	fclose(file);
//	return radacina;
//}
//
//int calcNrNoduriArbore(Nod* radacina) {
//	if (radacina!=NULL) {
//		return 1 + calcNrNoduriArbore(radacina->st) + calcNrNoduriArbore(radacina->dr);
//	}
//	return 0;
//}
//
//int calculeazaInaltimearbore(Nod* radacina) {
//	if (radacina != NULL) {
//		int inaltimeST = 1 + calculeazaInaltimearbore(radacina->st);
//		int inaltimeDR = 1 + calculeazaInaltimearbore(radacina->dr);
//
//		if (inaltimeST > inaltimeDR) {
//			return inaltimeST;
//		}
//		else {
//			return inaltimeDR;
//		}
//	}
//	return 0;
//}
//
//Produs getProdusByID(Nod* radacina, int id) {
//	Produs p;
//	p.id = -1;
//	if (radacina != NULL) {
//		if (radacina->info.id > id) {
//			p = getProdusByID(radacina->st, id);
//		}
//		else if (radacina->info.id < id) {
//			p = getProdusByID(radacina->dr, id);
//		}
//		else {
//			p = radacina->info;
//			p.denumire = (char*)malloc(strlen(radacina->info.denumire) + 1);
//			strcpy_s(p.denumire, strlen(radacina->info.denumire) + 1, radacina->info.denumire);
//
//		}
//	}
//	else {
//		p.categorie = '-';
//		p.pret = 0.00f;
//		p.denumire = (char*)malloc(strlen("N/A") + 1);
//		strcpy_s(p.denumire, strlen("N/A") + 1, "N/A");
//	}
//	return p;
//}
//
//float sumaProdCuNume(Nod* radacina, const char* nume) {
//	float suma = 0;
//	if (radacina != NULL) {
//
//		sumaProdCuNume(radacina->st, nume);
//		sumaProdCuNume(radacina->dr, nume);
//
//		if (strcmp(radacina->info.denumire, nume)==0) {
//			suma += radacina->info.pret;
//		}
//		return suma;
//	}
//	return 0;
//}
//
//void afisare(Nod* radacina) {
//	if (radacina != NULL) {
//		afisare(radacina->st);
//		afisareProdus(radacina->info);
//		afisare(radacina->dr);
//	}
//}
//
//void dezalocareABC(Nod** radacina) {
//	if ((*radacina) != NULL) {
//		dezalocareABC(&((*radacina)->st));
//		dezalocareABC(&((*radacina)->dr));
//		free((*radacina)->info.denumire);
//		free((*radacina));
//		(*radacina) = NULL;
//	}
//}
//void main() {
//	Nod* abc = citireArboreDinFisier("produse.txt");
//	
//	afisare(abc);
//
//	Produs p;
//	p.id = 6;
//	p.pret = 666.66;
//	p.denumire = "Produs6";
//	p.categorie = 's';
//
//	adaugaProdusInArbore(&abc, p);
//	afisare(abc);
//
//	printf("Nr noduri pe care il are abc este: %d\n", calcNrNoduriArbore(abc));
//	printf("Inaltimea abc este : % d\n", calculeazaInaltimearbore(abc));
//
//	
//	afisareProdus(getProdusByID(abc,6));
//
//	printf("suma preturilor produselor cu numele milka cioco: %.2f", sumaProdCuNume(abc,"Milka cioco"));
//	dezalocareABC(&abc);
//}