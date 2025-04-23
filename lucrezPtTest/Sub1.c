//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Reteta {
//	unsigned int nrReteta;
//	unsigned char nrMedicamente;
//	char** denumiri;
//	unsigned char* cantitati;
//	float* preturi;
//	unsigned char* procenteDeCompensare;
//	char* numeMedic;
//};
//typedef struct Reteta Reteta;
//
//struct Nod {
//	Reteta info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//
//struct ListaDubla {
//	Nod* head;
//	Nod* tail;
//};
//typedef struct ListaDubla ListaDubla;
//
//void inserareLaFinal(ListaDubla* listaDubla, Reteta reteta) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = reteta;
//	nodNou->prev = listaDubla->tail;
//	nodNou->next = NULL;
//
//	if (listaDubla->tail == NULL) {
//		listaDubla->head = nodNou;
//	}
//	else {
//		nodNou->prev = listaDubla->tail;
//		listaDubla->tail->next = nodNou;
//		
//	}
//
//	listaDubla->tail = nodNou;
//}
//
//Reteta initializareReteta(unsigned int nrReteta,
//	const char* numeMedic,
//	unsigned char nrMedicamente,
//	const char** denumiri,
//	const unsigned char* cantitati,
//	const float* preturi,
//	const unsigned char* procenteDeCompensare)
//{
//	Reteta r;
//	r.nrReteta = nrReteta;
//	r.nrMedicamente = nrMedicamente;
//
//	r.denumiri = (char**)malloc(nrMedicamente * sizeof(char*));
//	for (int i = 0; i < nrMedicamente; i++) {
//		r.denumiri[i] = (char*)malloc(strlen(denumiri[i]) + 1);
//		strcpy_s(r.denumiri[i], strlen(denumiri[i]) + 1, denumiri[i]);
//	}
//
//	r.cantitati = (unsigned char*)malloc(nrMedicamente * sizeof(unsigned char*));
//	memcpy(r.cantitati, cantitati, nrMedicamente * sizeof(unsigned char*));
//
//	r.preturi = (float*)malloc(nrMedicamente * sizeof(float));
//	for (int i = 0; i < nrMedicamente; i++) {
//		r.preturi[i] = preturi[i];
//	}
//
//	r.procenteDeCompensare = (unsigned char*)malloc(nrMedicamente * sizeof(unsigned char));
//	memcpy(r.procenteDeCompensare, procenteDeCompensare, nrMedicamente * sizeof(unsigned char));
//
//	r.numeMedic = (char*)malloc(strlen(numeMedic) + 1);
//	strcpy_s(r.numeMedic, strlen(numeMedic) + 1, numeMedic);
//
//	return r;
//
//}
//
//void afisareReteta(Reteta reteta) {
//	printf("================================================================\n");
//	printf("Nr. reteta: %u\n", reteta.nrReteta);
//	printf("Medic: %s\n", reteta.numeMedic);
//	printf("Medicamente:\n");
//	for (int i = 0; i < reteta.nrMedicamente; i++) {
//		printf(" - %s, Cantitate: %d, Pret: %.2f, Compensare: %d%%\n",
//			reteta.denumiri[i], reteta.cantitati[i], reteta.preturi[i], reteta.procenteDeCompensare[i]);
//	}
//}
//
//void afisareLista(ListaDubla lista) {
//	Nod* curent = lista.head;
//	while (curent != NULL) {
//		afisareReteta(curent->info);
//		curent = curent->next;
//	}
//}
//void eliberareMemorieReteta(Reteta* reteta) {
//	for (int i = 0; i < reteta->nrMedicamente; i++) {
//		free(reteta->denumiri[i]);
//	}
//	free(reteta->denumiri);
//	free(reteta->cantitati);
//	free(reteta->preturi);
//	free(reteta->procenteDeCompensare);
//	free(reteta->numeMedic);
//}
//
//void calculIncasari(ListaDubla lista, const char* denumireCautata) {
//
//	float incasari = 0.0f;
//	Nod* curent = lista.head;
//
//	while (curent != NULL) {
//		Reteta r = curent->info;
//		for (int i = 0; i < r.nrMedicamente; i++) {
//			if (strcmp(r.denumiri[i], denumireCautata) == 0) {
//				float pret = r.preturi[i];
//				unsigned char cant = r.cantitati[i];
//				unsigned char compensare = r.procenteDeCompensare[i];
//				float incasareMed = pret * cant * (100 - compensare) / 100.0f;
//				incasari += incasareMed;
//			}
//		}
//		curent = curent->next;
//	}
//
//	printf("Incasarile pentru medicamentul \"%s\" sunt: %.2f lei\n", denumireCautata, incasari);
//}
//
//void eliberareMemorieLista(ListaDubla* lista) {
//	Nod* curent = lista->head;
//	while (curent != NULL) {
//		Nod* deEliberat = curent;
//		curent = curent->next;
//		eliberareMemorieReteta(&deEliberat->info);
//		free(deEliberat);
//	}
//	lista->head = NULL;
//	lista->tail = NULL;
//}
//
//
//void main()
//{
//	ListaDubla lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//
//
//	const char* denumiri1[] = { "Paracetamol", "Ibuprofen" };
//	unsigned char cantitati1[] = { 10, 20 };
//	float preturi1[] = { 100.5f, 200.75f };
//	unsigned char procente1[] = { 50, 25 };
//	Reteta r1 = initializareReteta(1, "Dr. Ana", 2, denumiri1, cantitati1, preturi1, procente1);
//	inserareLaFinal(&lista, r1);
//
//	const char* denumiri2[] = { "Aspirina", "Amoxicilina" };
//	unsigned char cantitati2[] = { 5, 15 };
//	float preturi2[] = { 50.0f, 150.0f };
//	unsigned char procente2[] = { 30, 20 };
//	Reteta r2 = initializareReteta(2, "Dr. Ion", 2, denumiri2, cantitati2, preturi2, procente2);
//	inserareLaFinal(&lista, r2);
//
//	const char* denumiri3[] = { "Cetirizina", "Loratadina" };
//	unsigned char cantitati3[] = { 8, 12 };
//	float preturi3[] = { 80.0f, 120.0f };
//	unsigned char procente3[] = { 40, 10 };
//	Reteta r3 = initializareReteta(3, "Dr. Maria", 2, denumiri3, cantitati3, preturi3, procente3);
//	inserareLaFinal(&lista, r3);
//
//	const char* denumiri4[] = { "Omeprazol", "Esomeprazol" };
//	unsigned char cantitati4[] = { 7, 14 };
//	float preturi4[] = { 90.0f, 130.0f };
//	unsigned char procente4[] = { 35, 15 };
//	Reteta r4 = initializareReteta(4, "Dr. Elena", 2, denumiri4, cantitati4, preturi4, procente4);
//	inserareLaFinal(&lista, r4);
//
//	const char* denumiri5[] = { "Simvastatina", "Atorvastatina" };
//	unsigned char cantitati5[] = { 6, 18 };
//	float preturi5[] = { 110.0f, 140.0f };
//	unsigned char procente5[] = { 20, 5 };
//	Reteta r5 = initializareReteta(5, "Dr. Andrei", 2, denumiri5, cantitati5, preturi5, procente5);
//	inserareLaFinal(&lista, r5);
//	const char* denumiri6[] = { "Metformin", "Gliclazida" };
//	unsigned char cantitati6[] = { 9, 11 };
//	float preturi6[] = { 70.0f, 160.0f };
//	unsigned char procente6[] = { 45, 25 };
//	Reteta r6 = initializareReteta(6, "Dr. Gabriela", 2, denumiri6, cantitati6, preturi6, procente6);
//	inserareLaFinal(&lista, r6);
//	const char* denumiri7[] = { "Levotiroxina", "Liotironina" };
//	unsigned char cantitati7[] = { 4, 16 };
//	float preturi7[] = { 130.0f, 170.0f };
//	unsigned char procente7[] = { 10, 30 };
//	Reteta r7 = initializareReteta(7, "Dr. Radu", 2, denumiri7, cantitati7, preturi7, procente7);
//	inserareLaFinal(&lista, r7);
//	const char* denumiri8[] = { "Insulina", "Glimepirida" };
//	unsigned char cantitati8[] = { 3, 13 };
//	float preturi8[] = { 150.0f, 180.0f };
//	unsigned char procente8[] = { 15, 35 };
//	Reteta r8 = initializareReteta(8, "Dr. Cristina", 2, denumiri8, cantitati8, preturi8, procente8);
//	inserareLaFinal(&lista, r8);
//	const char* denumiri9[] = { "Amlodipina", "Diltiazem" };
//	unsigned char cantitati9[] = { 2, 20 };
//	float preturi9[] = { 160.0f, 190.0f };
//	unsigned char procente9[] = { 25, 45 };
//	Reteta r9 = initializareReteta(9, "Dr. Sorin", 2, denumiri9, cantitati9, preturi9, procente9);
//	inserareLaFinal(&lista, r9);
//	const char* denumiri10[] = { "Citalopram", "Sertralina" };
//	unsigned char cantitati10[] = { 1, 19 };
//	float preturi10[] = { 170.0f, 200.0f };
//	unsigned char procente10[] = { 5, 50 };
//	Reteta r10 = initializareReteta(10, "Dr. Laura", 2, denumiri10, cantitati10, preturi10, procente10);
//	inserareLaFinal(&lista, r10);
//
//	//fisare lista
//	afisareLista(lista);
//	printf("\n\n\n================================================================\n");
//
//	calculIncasari(lista, "Paracetamol");
//	calculIncasari(lista, "Ibuprofen");
//	calculIncasari(lista, "Citalopram");
//
//	dezalocareListaDubla(&lista);
//
//}
