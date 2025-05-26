//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<string.h>
//#include <stdlib.h>
//
//struct BiletAvion {
//	int id;
//	float pret;
//	int durata;
//	char* companie;
//	char* destinatie;
//	unsigned char clasa; //e economy, b business
//};
//typedef struct BiletAvion BiletAvion;
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	BiletAvion info;
//};
//
//BiletAvion citireBiletDinFisier(FILE* file) {
//	BiletAvion b;
//	char buffer[100];
//	char sep[4] = ",\n";
//	char* aux;
//	fgets(buffer, 100, file);
//
//	aux = strtok(buffer, sep);
//	b.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	b.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	b.durata = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	b.companie = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(b.companie, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	b.destinatie = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(b.destinatie, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	b.clasa = *aux;
//
//	return b;
//}
//
//void afisareBiletDinFisier(BiletAvion b) {
//	printf("Id: %d\n", b.id);
//	printf("Pret: %.2f\n", b.pret);
//	printf("Durata: %d\n", b.durata);
//	printf("Companie: %s\n", b.companie);
//	printf("Destinatie: %s\n", b.destinatie);
//	printf("Clasa: %c\n\n", b.clasa);
//}
//
//int calculeazaInaltimeArbore(Nod* radacina) {
//	if (radacina != NULL) {
//		int inaltimeST =  calculeazaInaltimeArbore(radacina->st);
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
//void rotatieStanga(Nod** radacina) {
//	Nod* aux = (*radacina)->dr;
//	(*radacina)->dr = aux->st;
//	aux->st = (*radacina);
//	*radacina = aux;
//}
//
//void rotatieDreapta(Nod** radacina) {
//	Nod* aux = (*radacina)->st;
//	(*radacina)->st = aux->dr;
//	aux->dr = (*radacina);
//	*radacina = aux;
//}
//
//int calculGradDeEchilibru(Nod* radacina) {
//	if (radacina != NULL) {
//		return calculeazaInaltimeArbore(radacina->st) - calculeazaInaltimeArbore(radacina->dr);
//	}
//	return 0;
//}
//
//void adaugaBiletInArbore(Nod** radacina, BiletAvion b) {
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > b.id) {
//			adaugaBiletInArbore(&((*radacina)->st), b);
//		}
//		else if ((*radacina)->info.id < b.id) {
//			adaugaBiletInArbore(&((*radacina)->dr), b);
//		}
//		else {
//			(*radacina)->info.id = b.id;
//			(*radacina)->info.durata = b.durata;
//			(*radacina)->info.pret = b.pret;
//			(*radacina)->info.clasa = b.clasa;
//			if ((*radacina)->info.companie != NULL) {
//				free((*radacina)->info.companie);
//			}
//
//			(*radacina)->info.companie = (char*)malloc(strlen(b.companie) + 1);
//			strcpy_s((*radacina)->info.companie, strlen(b.companie) + 1, b.companie);
//
//			if ((*radacina)->info.destinatie != NULL) {
//				free((*radacina)->info.destinatie);
//			}
//			(*radacina)->info.destinatie = (char*)malloc(strlen(b.destinatie) + 1);
//			strcpy_s((*radacina)->info.destinatie, strlen(b.destinatie) + 1, b.destinatie);
//		}
//
//		int gradDeEchilibru = calculGradDeEchilibru((*radacina));
//
//		if (gradDeEchilibru == 2) {
//			if (calculGradDeEchilibru((*radacina)->st) >= 0) { //LL
//				rotatieDreapta(radacina);
//			}
//			else { //LR
//				rotatieStanga(&((*radacina)->st));
//				rotatieDreapta(radacina);
//			}
//		}
//		else if (gradDeEchilibru == -2) { //RR
//			if (calculGradDeEchilibru((*radacina)->dr) <=0 ) {
//				rotatieStanga(radacina);
//			}
//			else { //RL
//				rotatieDreapta(&((*radacina)->dr));
//				rotatieStanga(radacina);
//			}
//		}
//	}
//	else {
//		(*radacina) = malloc(sizeof(Nod));
//
//		(*radacina)->info = b;
//
//		(*radacina)->info.companie = (char*)malloc(strlen(b.companie) + 1);
//		strcpy_s((*radacina)->info.companie, strlen(b.companie) + 1,b.companie);
//		(*radacina)->info.destinatie = (char*)malloc(strlen(b.destinatie) + 1);
//		strcpy_s((*radacina)->info.destinatie, strlen(b.destinatie) + 1, b.destinatie);
//
//		(*radacina)->st = NULL;
//		(*radacina)->dr = NULL;
//	}
//}
//
//Nod* citireArboreDinFisiser(const char* numefisier) {
//	FILE* file = fopen(numefisier, "r");
//	Nod* radacina=NULL;
//
//	while (!feof(file)) {
//		BiletAvion b = citireBiletDinFisier(file);
//		adaugaBiletInArbore(&radacina, b);
//		free(b.companie);
//		free(b.destinatie);
//	}
//
//	fclose(file);
//	return radacina;
//}
//
//void afisareArboreINORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareArboreINORDINE(radacina->st);
//		afisareBiletDinFisier(radacina->info);
//		afisareArboreINORDINE(radacina->dr);
//	}
//}
//
//void afisareArborePREORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareBiletDinFisier(radacina->info);
//		afisareArborePREORDINE(radacina->st);
//		afisareArborePREORDINE(radacina->dr);
//	}
//}
//
//void afisareArborePOSTORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareArborePOSTORDINE(radacina->st);
//		afisareArborePOSTORDINE(radacina->dr);
//		afisareBiletDinFisier(radacina->info);
//	}
//}
//
//BiletAvion getBiletByID(Nod* radacina, int id) {
//	BiletAvion b;
//	b.id = -1;
//	if (radacina != NULL) {
//		if (radacina->info.id > id) {
//			return (getBiletByID(radacina->st, id));
//		}
//		else if(radacina->info.id < id){
//			return (getBiletByID(radacina->dr,id));
//		}
//		else {
//			b = radacina->info;
//
//			b.companie = (char*)malloc(strlen((radacina)->info.companie) + 1);
//			strcpy_s(b.companie, strlen((radacina)->info.companie) + 1, (radacina)->info.companie);
//			b.destinatie = (char*)malloc(strlen((radacina)->info.destinatie) + 1);
//			strcpy_s(b.destinatie, strlen((radacina)->info.destinatie) + 1, (radacina)->info.destinatie);
//
//			return b;
//		}
//	}
//	return b;
//
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	if (radacina != NULL) {
//		float suma = radacina->info.pret;
//		float sumaST = calculeazaPretTotal(radacina->st);
//		float sumaDR = calculeazaPretTotal(radacina->dr);
//		return suma + sumaST + sumaDR;
//	}
//	return 0;
//}
//
//float calculeazaPretTotalBileteCompanie(Nod* radacina, const char* numeCompanie) {
//	if (radacina != NULL) {
//		float suma = 0;
//
//		if (strcmp(radacina->info.companie, numeCompanie) == 0) {
//			suma = radacina->info.pret;
//		}
//		float sumaST = calculeazaPretTotalBileteCompanie((radacina->st),numeCompanie);
//		float sumaDR = calculeazaPretTotalBileteCompanie((radacina->dr), numeCompanie);
//		return suma + sumaST + sumaDR;
//	}
//	return 0;
//}
//
//int calculNrNoduriAVL(Nod* radacina) {
//	if (radacina != NULL) {
//		return 1 + calculNrNoduriAVL(radacina->st) + calculNrNoduriAVL(radacina->dr);
//	}
//	return 0;
//}
//
//void dezalocareArbore(Nod** radacina) {
//	if (radacina != NULL) {
//		dezalocareArbore(&((*radacina)->st));
//		dezalocareArbore(&((*radacina)->dr));
//		free((*radacina)->info.companie);
//		free((*radacina)->info.destinatie);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//void afisareBileteDupaCompanie(Nod* radacina, const char* numeCompanie) {
//	if (radacina != NULL) {
//		afisareBileteDupaCompanie(radacina->st, numeCompanie);
//		if (strcmp(radacina->info.companie, numeCompanie) == 0) {
//			afisareBiletDinFisier(radacina->info);
//		}
//		afisareBileteDupaCompanie(radacina->dr, numeCompanie);
//	}
//}
//void main() {
//	Nod* arbore = citireArboreDinFisiser("bileteAVL.txt");
//
//	printf("\n\n============ IN ORDINE ==============\n");
//	afisareArboreINORDINE(arbore);
//
//	printf("\n\n============ PRE ORDINE ==============\n");
//	afisareArborePREORDINE(arbore);
//
//	printf("\n\n============ POST ORDINE ==============\n");
//	afisareArborePOSTORDINE(arbore);
//
//
//}