//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct Echipament Echipament;
//struct Echipament {
//	int id;
//	int garantieLuni;
//	float pret;
//	char* denumire;
//	char* furnizor;
//	unsigned char categorie;
//};
//
//typedef struct NodABC Nod;
//struct NodABC {
//	Nod* st;
//	Nod* dr;
//	Echipament info;
//};
//
//Echipament citireEchipamentDinFisier(FILE* f) {
//	Echipament e;
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, f);
//	char* aux;
//
//	aux = strtok(buffer, sep);
//	e.id = atoi(aux);
//	
//	aux = strtok(NULL, sep);
//	e.garantieLuni = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	e.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	e.denumire = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(e.denumire, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	e.furnizor = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(e.furnizor, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	e.categorie = *aux;
//
//	return e;
//}
//
//void afisareEchipament(Echipament e) {
//	printf("Id: %d\n", e.id);
//	printf("Garantie: %d\n", e.garantieLuni);
//	printf("Pret: %.2f\n", e.pret);
//	printf("Denumire: %s\n", e.denumire);
//	printf("Furnizor: %s\n", e.furnizor);
//	printf("Categorie: %c\n\n", e.categorie);
//}
//
//void adaugaEchipamentInArbore(Nod** radacina, Echipament e) {
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > e.id) {
//			adaugaEchipamentInArbore(&(*radacina)->st, e);
//		}
//		else if ((*radacina)->info.id < e.id) {
//			adaugaEchipamentInArbore(&(*radacina)->dr, e);
//		}
//		else {
//			(*radacina)->info.id = e.id;
//			(*radacina)->info.garantieLuni = e.garantieLuni;
//			(*radacina)->info.categorie = e.categorie;
//			if ((*radacina)->info.denumire != NULL) {
//				free((*radacina)->info.denumire);
//			}
//			if ((*radacina)->info.furnizor != NULL) {
//				free((*radacina)->info.furnizor);
//			}
//			(*radacina)->info.denumire = (char*)malloc(strlen(e.denumire) + 1);
//			strcpy_s((*radacina)->info.denumire, strlen(e.denumire) + 1, e.denumire);
//			(*radacina)->info.furnizor = (char*)malloc(strlen(e.furnizor) + 1);
//			strcpy_s((*radacina)->info.furnizor, strlen(e.furnizor) + 1, e.furnizor);
//		}
//	}
//	else {
//		(*radacina) = malloc(sizeof(Nod));
//		(*radacina)->info = e;
//		(*radacina)->info.denumire = (char*)malloc(strlen(e.denumire) + 1);
//		strcpy_s((*radacina)->info.denumire, strlen(e.denumire) + 1, e.denumire);
//		(*radacina)->info.furnizor = (char*)malloc(strlen(e.furnizor) + 1);
//		strcpy_s((*radacina)->info.furnizor, strlen(e.furnizor) + 1, e.furnizor);
//		(*radacina)->dr = NULL;
//		(*radacina)->st = NULL;
//	}
//}
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* radacina = NULL;
//
//	while (!feof(file)) {
//		Echipament e = citireEchipamentDinFisier(file);
//		adaugaEchipamentInArbore(&radacina, e);
//		free(e.denumire);
//		free(e.furnizor);
//	}
//
//	fclose(file);
//	return radacina;
//}
//
//void afisareArboreInOrdine(Nod* radacina) { //srd
//	if(radacina != NULL) {
//		afisareArboreInOrdine(radacina->st);
//		afisareEchipament(radacina->info);
//		afisareArboreInOrdine(radacina->dr);
//	}
//}
//
//void afisareArborePREOrdine(Nod* radacina) {//rsd
//	if (radacina!=NULL) {
//		afisareEchipament(radacina->info);
//		afisareArborePREOrdine(radacina->st);
//		afisareArborePREOrdine(radacina->dr);
//	}
//
//}
//void afisarePOSTOrdine(Nod* radacina) { //sdr
//	if (radacina != NULL) {
//		afisarePOSTOrdine(radacina->st);
//		afisarePOSTOrdine(radacina->dr);
//		afisareEchipament(radacina->info);
//	}
//}
//
//Echipament getEchipamentByID(Nod* radacina, int id) {
//	if (radacina != NULL) {
//		if (radacina->info.id == id) {
//			return radacina->info;
//		}
//		else {
//			if (radacina->info.id > id) {
//				return getEchipamentByID(radacina->st, id);
//			}
//			else {
//				return getEchipamentByID(radacina->dr, id);
//			}
//		}
//	}
//	Echipament e;
//	e.id = -1;
//	e.pret = -1;
//	e.garantieLuni = -1;
//	e.denumire = NULL;
//	e.furnizor = NULL;
//	e.categorie = '-';
//	return e;
//}
//
//int determinareNrNoduri(Nod* radacina) {
//
//	if (radacina != NULL) {
//		return 1 + determinareNrNoduri(radacina->st) + determinareNrNoduri(radacina->dr);
//	}
//	else {
//		return 0;
//	}
//}
//
//int calculInaltimeArbore(Nod* radacina) {
//	int inaltimeST = 1;
//	int inaltimeDR = 1;
//	if (radacina != NULL) {
//		if (radacina->st != NULL) {
//			inaltimeST = 1 + calculInaltimeArbore(radacina->st);
//		}
//		if (radacina->dr != NULL) {
//			inaltimeDR = 1 + calculInaltimeArbore(radacina->dr);
//		}
//
//		if(inaltimeST>inaltimeDR){
//			return inaltimeST;
//		}
//		else {
//			return inaltimeDR;
//		}
//	}
//	else {
//		return 0;
//	}
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	if (radacina != NULL) {
//		return radacina->info.pret + calculeazaPretTotal(radacina->st) + calculeazaPretTotal(radacina->dr);
//	}
//	else {
//		return 0;
//	}
//}
//
//float calculeazaPretEchipamenteFurnizor(Nod* radacina, const char* numeFurnizor) {
//	if (radacina != NULL) {
//		float suma = 0;
//		if (strcmp(numeFurnizor, radacina->info.furnizor) == 0) {
//			suma+= radacina->info.pret;
//		}
//		suma += calculeazaPretEchipamenteFurnizor(radacina->st, numeFurnizor);
//		suma += calculeazaPretEchipamenteFurnizor(radacina->dr, numeFurnizor);
//		return suma;
//	}
//	
//	return 0;
//}
//
//void dezalocareArbore(Nod** radacina) {
//	if ((*radacina) != NULL) {
//		dezalocareArbore(&(*radacina)->st);
//		dezalocareArbore(&(*radacina)->dr);
//
//		free((*radacina)->info.denumire);
//		free((*radacina)->info.furnizor);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//void main() {
//	Nod* arbore=citireArboreDinFisier("echipamente.txt");
//
//	printf("\n\n ========= IN ORDINE =========\n");
//	afisareArboreInOrdine(arbore);
//
//	printf("\n\n ========= PRE ORDINE =========\n");
//	afisareArborePREOrdine(arbore);
//
//	printf("\n\n ========= POST ORDINE =========\n");
//	afisarePOSTOrdine(arbore);
//
//	printf("\n\nElementul cautat dupa id este: \n");
//	afisareEchipament(getEchipamentByID(arbore, 15));
//
//	printf("\n\nnoduri ale arborelui: \n");
//	printf("%d\n", determinareNrNoduri(arbore));
//
//	printf("\nSuma tuturor echipamentelor este: %.2f\n", calculeazaPretTotal(arbore));
//
//	printf("\nFurnizorul altex: %.2f\n", calculeazaPretEchipamenteFurnizor(arbore,"Altex"));
//
//	printf("\n\n%d\n", calculInaltimeArbore(arbore));
//
//	Echipament e;
//	e.id = 11;
//	e.garantieLuni = 3;
//	e.categorie = 's';
//	e.denumire = (char*)malloc(strlen("Asus VivoBook") + 1);
//	strcpy_s(e.denumire, strlen("Asus VivoBook") + 1, "Asus VivoBook");
//
//	e.furnizor = (char*)malloc(strlen("la gigi piticu") + 1);
//	strcpy_s(e.furnizor, strlen("la gigi piticu") + 1, "la gigi piticu");
//
//	e.pret = 10000000000.00;
//	adaugaEchipamentInArbore(&arbore, e);
//
//	afisareArboreInOrdine(arbore);
//	
//	dezalocareArbore(arbore);
//}
