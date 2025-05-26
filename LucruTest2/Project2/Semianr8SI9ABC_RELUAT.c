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
////creare structura pentru un nod dintr-un arbore binar de cautare
//typedef struct NodABC Nod;
//struct NodABC {
//	Nod* st;
//	Nod* dr;
//	Masina info;
//
//};
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
//	m1.pret= atof(strtok(NULL, sep));
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
//
//void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte princiippile de arbore binar de cautare
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > masinaNoua.id) {
//			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
//		}
//		else if ((*radacina)->info.id < masinaNoua.id) {
//			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
//
//		}
//		else {
//			(*radacina)->info.nrUsi = masinaNoua.nrUsi;
//			(*radacina)->info.pret = masinaNoua.pret;
//			(*radacina)->info.serie = masinaNoua.serie;
//			if ((*radacina)->info.model != NULL)
//			{
//				free((*radacina)->info.model);
//			}
//			if ((*radacina)->info.numeSofer != NULL) {
//				free((*radacina)->info.numeSofer);
//			}
//			(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
//			strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//			(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
//			strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//		}
//	}
//	else {
//		(*radacina) = malloc(sizeof(Nod));
//
//		(*radacina)->info = masinaNoua;
//		(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
//		strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//		(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
//		strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//		(*radacina)->st = NULL;
//		(*radacina)->dr = NULL;
//	}
//	
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* radacina = NULL;
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		adaugaMasinaInArbore(&radacina, m);
//		free(m.model);
//		free(m.numeSofer);
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisareMasiniDinArborePreordine(Nod* radacina) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//
//	//in ordine = SRD
//	//POST ORDINE = SDR
//	//PREORDINE = RSD
//	
//	//preordine rsd
//	if (radacina != NULL) {
//		afisareMasina(radacina->info);
//		afisareMasiniDinArborePreordine(radacina->st);
//		afisareMasiniDinArborePreordine(radacina->dr);
//	}
//}
//
//void afisareArboreInOrdine(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareArboreInOrdine(radacina->st);
//		afisareMasina(radacina->info);
//		afisareArboreInOrdine(radacina->dr);
//	}
//}
//
//void afisarePostOrdineArbore(Nod* radacina) {
//	if (radacina != NULL) {
//		afisarePostOrdineArbore(radacina->st);
//		afisarePostOrdineArbore(radacina->dr);
//		afisareMasina(radacina->info);
//	}
//}
//
//void dezalocareArboreDeMasini(Nod** radacina) {
//	//sunt dezalocate toate masinile si arborele de elemente
//	if ((*radacina) != NULL) {
//		dezalocareArboreDeMasini(&(*radacina)->st);
//		dezalocareArboreDeMasini(&(*radacina)->dr);
//		free((*radacina)->info.numeSofer);
//		free((*radacina)->info.model);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Masina getMasinaByID(Nod* radacina, int id) {
//	Masina m;
//	if (radacina != NULL) {
//
//		if (id > radacina->info.id) {
//			return getMasinaByID(radacina->dr, id);
//		}
//		else if (id < radacina->info.id) {
//			return getMasinaByID(radacina->st, id);
//		}
//		else {
//			m = radacina->info;
//			m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
//			strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
//			m.model = (char*)malloc(strlen(radacina->info.model) + 1);
//			strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
//			return m;
//		}
//	}
//	else {
//		m.id = -1;
//		m.model = NULL;
//		m.numeSofer = NULL;
//		m.nrUsi = 0;
//		m.pret = 0;
//		m.serie = 0;
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* radacina) {
//	//calculeaza numarul total de noduri din arborele binar de cautare
//	
//
//	if (radacina == NULL) {
//		return 0;
//	}
//	else {
//		return  1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
//	}
//	return 0;
//}
//
//int calculeazaInaltimeArbore(Nod* radacina) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	int inaltimeST = 0;
//	int inaltimeDR = 0;
//	if (radacina != NULL) {
//		inaltimeST = calculeazaInaltimeArbore(radacina->st);
//		inaltimeDR = calculeazaInaltimeArbore(radacina->dr);
//		if (inaltimeST > inaltimeDR) {
//			return 1+inaltimeST;
//		}
//		else {
//			return 1+inaltimeDR;
//		}
//	}
//	else {
//		return 0;
//	}
//
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	//calculeaza pretul tuturor masinilor din arbore.
//	float pretTotal = 0;
//	if (radacina != NULL) {
//		pretTotal = radacina->info.pret + calculeazaPretTotal(radacina->st) + calculeazaPretTotal(radacina->dr);
//		return pretTotal;
//	}
//	else {
//		return 0;
//	}
//	return pretTotal;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	if (radacina == NULL)
//		return 0;
//
//	float suma = 0;
//
//	if (strcmp(radacina->info.numeSofer, numeSofer) == 0)
//		suma += radacina->info.pret;
//
//	suma += calculeazaPretulMasinilorUnuiSofer(radacina->st, numeSofer);
//	suma += calculeazaPretulMasinilorUnuiSofer(radacina->dr, numeSofer);
//
//	return suma;
//}
//
//int main() {
//	Nod* arbore = citireArboreDeMasiniDinFisier("masiniArbore.txt");
//
//	printf("\n\n============ IN ORDINE: SRD ================\n");
//	afisareArboreInOrdine(arbore);
//
//	printf("\n\n============ IN POSTORDINE: SDR ================\n");
//	afisarePostOrdineArbore(arbore);
//
//	printf("\n\n============ PREORDINE: RSD ================\n");
//	afisareMasiniDinArborePreordine(arbore);
//
//	printf("Numarul de noduri total: %d\n", determinaNumarNoduri(arbore));
//	printf("Inaltimea arborelui: %d\n", calculeazaInaltimeArbore(arbore));
//	printf("Pret total masini: %.2f\n", calculeazaPretTotal(arbore));
//
//	char nume[] = "Gheorghe";
//	printf("Pret total masini ale soferului %s: %.2f\n", nume, calculeazaPretulMasinilorUnuiSofer(arbore, nume));
//
//	//dezalocareArboreDeMasini(arbore);
//
//	Masina m;
//	m.id = 11;
//	m.nrUsi = 5;
//	m.pret = 290000;
//	m.model = (char*)malloc(strlen("Renaul Arkana 2025") + 1);
//	strcpy_s(m.model, strlen("Renaul Arkana 2025") + 1, "Renaul Arkana 2025");
//	m.numeSofer = (char*)malloc(strlen("Gina") + 1);
//	strcpy_s(m.numeSofer, strlen("Gina") + 1, "Gina");
//	m.serie = 'Z';
//
//	printf("\n\n============ IN ORDINE: INAINTE DE INSERARE ================\n");
//	afisareArboreInOrdine(arbore);
//
//	adaugaMasinaInArbore(&arbore, m);
//
//	printf("\n\n============ IN ORDINE DUPA INSERARE ================\n");
//	afisareArboreInOrdine(arbore);
//
//	dezalocareArboreDeMasini(arbore);
//
//	return 0;
//}