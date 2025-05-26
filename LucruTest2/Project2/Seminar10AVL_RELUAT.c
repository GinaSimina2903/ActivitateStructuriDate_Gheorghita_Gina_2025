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
//typedef struct Nod Nod;
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	Masina info;
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
//int calculeazaInaltimeArbore(Nod* radacina) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	if (radacina == NULL) {
//		return 0;
//	}
//	else {
//		int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
//		int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);
//
//		if (inaltimeSt > inaltimeDr) {
//			return 1 + inaltimeSt;
//		}
//		else {
//			return 1 + inaltimeDr;
//		}
//	}
//}
//
////ALTE FUNCTII NECESARE:
//// - aici veti adauga noile functii de care aveti nevoie.
//
//void rotireStanga(Nod** radacina)
//{
//	Nod* aux = (*radacina)->dr;
//	(*radacina)->dr=aux->st;
//	aux->st = (*radacina);
//	*radacina = aux;
//}
//
//void rotireDreapta(Nod** radacina) {
//
//	Nod* aux = (*radacina)->st;
//	(*radacina)->st=aux->dr;
//	aux->dr = (*radacina);
//	*radacina = aux;
//}
//
//int calculeazaGradEchilibru(Nod*radacina) {
//	if (radacina != NULL) {
//		return (calculeazaInaltimeArbore(radacina->st) - calculeazaInaltimeArbore(radacina->dr));
//	}
//	else {
//		return 0;	
//	}
//}
//void adaugaMasinaInArboreEchilibrat(Nod**radacina,  Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > masinaNoua.id) {
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->st), masinaNoua);
//		}
//		else if ((*radacina)->info.id < masinaNoua.id) {
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->dr), masinaNoua);
//		}
//		else {
//			(*radacina)->info.id = masinaNoua.id;
//			(*radacina)->info.nrUsi = masinaNoua.nrUsi;
//			(*radacina)->info.pret = masinaNoua.pret;
//			(*radacina)->info.serie = masinaNoua.serie;
//			if ((*radacina)->info.model != NULL) {
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
//		
//		int gradDeEchilibru = calculeazaGradEchilibru((*radacina));
//		if (gradDeEchilibru == 2) {
//			if (calculeazaGradEchilibru((*radacina)->st) == 1) {
//				rotireDreapta(radacina);
//			}
//			else {
//				rotireStanga(&((*radacina)->st));
//				rotireDreapta(radacina);
//			}
//		}
//		else if (gradDeEchilibru == -2) {
//			if (calculeazaGradEchilibru((*radacina)->dr) == -1) {
//				rotireDreapta(&((*radacina)->dr));
//				rotireStanga(radacina);
//			}
//		}
//	}
//	else {
//		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//		nodNou->info = masinaNoua;
//		nodNou->dr = NULL;
//		nodNou->st = NULL;
//		(*radacina) = nodNou;
//	}
//
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* radacina = NULL; 
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		adaugaMasinaInArboreEchilibrat(&radacina, m);
//	}
//	fclose(file);
//	return radacina;
//
//}
//
//void afisareMasiniDinArborePREORDINE(Nod* radacina) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//
//	if (radacina != NULL) {
//		afisareMasina(radacina->info);
//		afisareMasiniDinArborePREORDINE(radacina->st);
//		afisareMasiniDinArborePREORDINE(radacina->dr);
//	}
//}
//
//void afisareMasiniDinArborePOSTORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareMasiniDinArborePOSTORDINE(radacina->st);
//		afisareMasiniDinArborePOSTORDINE(radacina->dr);
//		afisareMasina(radacina->info);
//	}
//}
//
//void afisareMasiniDinArboreINORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareMasiniDinArboreINORDINE(radacina->st);
//		afisareMasina(radacina->info);
//		afisareMasiniDinArboreINORDINE(radacina->dr);
//	}
//}
//void dezalocareArboreDeMasini(Nod** radacina) {
//	//sunt dezalocate toate masinile si arborele de elemente
//	if ((*radacina) != NULL) {
//		dezalocareArboreDeMasini(&((*radacina)->st));
//		dezalocareArboreDeMasini(&((*radacina)->dr));
//		free((*radacina)->info.model);
//		free((*radacina)->info.numeSofer);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(Nod* radacina, int id) {
//	Masina m;
//	m.id = -1;
//	if (id < radacina->info.id) {
//		return getMasinaByID(radacina->st, id);
//	}
//	else if (id > radacina->info.id) {
//		return getMasinaByID(radacina->dr, id);
//	}
//	else {
//		m = radacina->info;
//		m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
//		strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
//		m.model = (char*)malloc(strlen(radacina->info.model) + 1);
//		strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
//		return m;
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* radacina) {
//	if (radacina != NULL) {
//		return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
//	}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	if (radacina != NULL) {
//		int suma = radacina->info.pret;
//		return suma + calculeazaPretTotal(radacina->st) + calculeazaPretTotal(radacina->dr);
//	}
//	return 0;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod*radacina, const char* numeSofer) {
//	if (radacina != NULL) {
//		float suma;
//		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
//			suma = radacina->info.pret;
//			
//		}
//		suma += calculeazaPretulMasinilorUnuiSofer(radacina->st, numeSofer);
//		suma+= calculeazaPretulMasinilorUnuiSofer(radacina->dr, numeSofer);
//		return suma;
//	}
//	return 0;
//}
//
//int main() {
//	Nod* arbore = citireArboreDeMasiniDinFisier("masiniArbore.txt");
//	printf("============== afisare in ordine: ==================\n");
//	afisareMasiniDinArboreINORDINE(arbore);
//
//	printf("============== afisare pre ordine: ==================\n");
//	afisareMasiniDinArborePREORDINE(arbore);
//
//	printf("============== afisare post ordine: ==================\n");
//	afisareMasiniDinArborePOSTORDINE(arbore);
//
//	printf("masina cu id-ul 5: \n");
//	afisareMasina(getMasinaByID(arbore, 5));
//	
//	return 0;
//}