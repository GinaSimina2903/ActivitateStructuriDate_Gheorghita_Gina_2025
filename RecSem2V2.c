#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
#include<malloc.h>

struct Masina {
	int id;
	//int ;
	char* model;
	float tonaj;
	char serie;
	//char* ;
	//float ;
	//char ;
};
struct Masina initializare(int idNou, const char* modelNou, float tonajNou, char serieNoua ) {
	struct Masina m;
	m.id = idNou;
	m.model = (char*)malloc(strlen(modelNou) + 1);
	strcpy_s(m.model, strlen(modelNou) + 1, modelNou);
	m.tonaj = tonajNou;
	m.serie = serieNoua;
	//initializare structura 
	return m;
}

void afisare(struct Masina m) {
	/*printf("id: %d \n Model: %s \n Tonaj: %f \n Serie: %c\n", m.id, m.model, m.tonaj, m.serie);*/
	printf("Id: %d \n", m.id);
	printf("Modelul: %s \n", m.model);
	printf("Tonaj: %f \n", m.tonaj);
	printf("Serie: %c \n", m.serie);
	printf("_____________________________\n");
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Masina* copiazaPrimeleNMasini(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina *vectorNou=malloc(sizeof(struct Masina)*nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
		strcpy_s(vectorNou[i].model, strlen(vector[i].model) + 1, vector[i].model);
	}
	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].model);
	}
	free(*vector);
	(*vector) = NULL;
	*nrElemente = 0;
}

struct Masina** copiazaMasiniCuTonajMic(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if(vector[i].tonaj<prag)
		{
			(*dimensiune)++;
		}
	}
	(*vectorNou) = malloc(sizeof(struct Masina)*(*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].tonaj < prag)
		{
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].model = malloc(sizeof(char)*(strlen(vector[i].model)+1));
			strcpy_s((*vectorNou)[k].model, strlen(vector[i].model)+1, (vector[i].model));
			k++;
		}
	}

	return vectorNou;
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) 
{
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina m;
	m.id = -1;
	m.model = NULL;
	m.tonaj = 0;
	m.serie = '\0';

	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].model, conditie) == 0) {
			m.id = vector[i].id;
			m.serie = vector[i].serie;
			m.tonaj = vector[i].tonaj;

			m.model = (char*)malloc(strlen(vector[i].model) + 1);
			strcpy_s(m.model, strlen(vector[i].model) + 1, vector[i].model);
			return m;
		}
	}
	return m;
}

void toateElementeleDupaConditie(struct Masina* vector, int nrElemente, const char* conditie) {
	//sa se gadeasca toate elementele care indeplinesc o conditie data
	struct Masina m;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].model, conditie) == 0) {
			m.id = vector[i].id;
			m.serie = vector[i].serie;
			m.tonaj = vector[i].tonaj;

			m.model = (char*)malloc(strlen(vector[i].model) + 1);
			strcpy_s(m.model, strlen(vector[i].model) + 1, vector[i].model);
			printf("Elementul %d: \n", i);
			afisare(m);
		}
	}
}

struct Masina actualizeazaTonaj(struct Masina* vector,int nrElemente, int idCautat, float tonajNou) {
	struct Masina m;
	m.id = -1;
	m.model = NULL;
	m.tonaj = 0;
	m.serie = '\0';
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].id == idCautat) {

			vector[i].tonaj = tonajNou;
			return vector[i];
		}
	}
	return m;
}
	

//Verifică existența unei mașini după model și serie – Returnează true sau false dacă există o mașină cu un anumit model și serie.
bool existaMasinaModelSiSerie(struct Masina* vector, int nrElemente, const char* modelCautat, char serieCautata)
{

	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].model, modelCautat) ==0 && vector[i].serie==serieCautata) 
		{
			return true;
		}
	}
	return false;
}

//ordonam masinile dupa tonaj -- CRESCATOR
void ordonareCrescatoareDupaTonaj(struct Masina* vector, int nrElemente) {

	int schimbat = 1;

	while (schimbat) {
		schimbat = 0;
		for (int i = 0; i < nrElemente - 1; i++) {
			if (vector[i].tonaj > vector[i + 1].tonaj) {

				struct Masina masinaAuxiliara;
				masinaAuxiliara.id = vector[i].id;
				masinaAuxiliara.serie = vector[i].serie;
				masinaAuxiliara.tonaj = vector[i].tonaj;
				masinaAuxiliara.model = (char*)malloc(strlen(vector[i].model) + 1);
				strcpy_s(masinaAuxiliara.model, strlen(vector[i].model) + 1, vector[i].model);

				free(vector[i].model);

				vector[i].id = vector[i + 1].id;
				vector[i].serie = vector[i + 1].serie;
				vector[i].tonaj = vector[i + 1].tonaj;
				vector[i].model = (char*)malloc(strlen(vector[i + 1].model) + 1);
				strcpy_s(vector[i].model, strlen(vector[i + 1].model) + 1, vector[i + 1].model);

				free(vector[i + 1].model);

				vector[i + 1].id = masinaAuxiliara.id;
				vector[i + 1].serie = masinaAuxiliara.serie;
				vector[i + 1].tonaj = masinaAuxiliara.tonaj;
				vector[i + 1].model = (char*)malloc(strlen(masinaAuxiliara.model) + 1);
				strcpy_s(vector[i + 1].model, strlen(masinaAuxiliara.model) + 1, masinaAuxiliara.model);

				free(masinaAuxiliara.model);

				schimbat = 1;
			}
		}
	}
}

//stergem o masina dupa id
struct Masina* stergereMasinaDupaID(struct Masina* vector, int* nrElemente, int idCerut)
{
	for (int i = 0; i < *nrElemente; i++) {
		if (vector[i].id == idCerut) {
			free(vector[i].model);
			for (int j = i; j < *nrElemente - 1; j++) {
				vector[j] = vector[j + 1];
			}
			(*nrElemente)--;

			vector = (struct Masina*)realloc(vector, (*nrElemente) * sizeof(struct Masina));

			if (vector == NULL && *nrElemente > 0) {
				printf("Eroare la realocare memorie!\n");
				exit(1);
			}
			return vector;
		}
	}

	return vector;
}



int main() {
	struct Masina m;
	m = initializare(1, "Audi", 2.3, 'S');
	afisare(m);

	int nrMasini = 3;
	struct Masina* vectorMasini;
	vectorMasini = malloc(sizeof(struct Masina)*nrMasini);
	vectorMasini[0] = initializare(2, "BMW", 2.2, 'C');
	vectorMasini[1] = initializare(3, "Fiat", 2.6, 'A');
	vectorMasini[2] = initializare(4, "Fiat", 1.8, 'T');

	afisareVector(vectorMasini, nrMasini);

	struct Masina* vectorMasiniCopiate;
	int nrMasiniCopiate = 2;
	
	vectorMasiniCopiate = copiazaPrimeleNMasini(vectorMasini,nrMasini,nrMasiniCopiate);
	printf("\n\n-------------------MASINI COPIATE--------------------\n");
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);


	printf("\n\n-------------------MASINI USOARE--------------------\n");
	copiazaMasiniCuTonajMic(vectorMasini, nrMasini, 2.5, &vectorMasiniCopiate, &nrMasiniCopiate );
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);


	printf("\n\n-------------------MASINA GASITA DUPA CONDITIE--------------------\n");
	struct Masina masinaGasita = getPrimulElementConditionat(vectorMasini, nrMasini, "Fiat");
	if (masinaGasita.id != -1) {
		printf("Masina gasita: \n");
		afisare(masinaGasita);
		free(masinaGasita.model);
	}
	else {
		printf("Nu s-a gasit nicio masina cu modelul dat.\n");
	}

	printf("\n\n-------------------MASINI GASITE DUPA CONDITIE--------------------\n");
	toateElementeleDupaConditie(vectorMasini, nrMasini, "Fiat");


	printf("\n\n-------------------MODIFICARE MASINA DUPA ID--------------------\n");

	int idCautat;
	float tonajNou;

	printf("Introduceti ID-ul masinii al carei tonaj doriti sa il modificati: ");
	scanf_s("%d", &idCautat);

	printf("Introduceti noul tonaj: ");
	scanf_s("%f", &tonajNou);

	struct Masina masinaModificataDupaId = actualizeazaTonaj(vectorMasini, nrMasini, idCautat, tonajNou);

	if (masinaModificataDupaId.id != -1) {
		printf("Masina modificata: \n");
		afisare(masinaModificataDupaId);
	}

	printf("\n\n-------------------EXISTA MASINI DUPA MODEL SI SERIE--------------------\n");

	if (existaMasinaModelSiSerie(vectorMasini, nrMasini, "Fiat", 'A')) {
		printf("Masina cu modelul 'Fiat' si seria 'A' exista in lista.\n");
	}
	else {
		printf("Nu s-a gasit nicio masina cu modelul 'Fiat' si seria 'A'.\n");
	}

	printf("\n\n-------------------ORDONARE CRESCATOARE--------------------\n");

	printf("Vector initial: \n");
	afisareVector(vectorMasini,nrMasini);
	printf("\n\nVector ordonat crescator: \n");
	ordonareCrescatoareDupaTonaj(vectorMasini, nrMasini);
	afisareVector(vectorMasini, nrMasini);

	printf("\n\n-------------------STERGERE MASINA DUPA ID--------------------\n");
	int idDeSters;
	printf("Introduceti ID-ul masinii de sters: ");
	scanf_s("%d", &idDeSters);

	vectorMasini = stergereMasinaDupaID(vectorMasini, &nrMasini, idDeSters);

	printf("Vector actualizat dupa stergere:\n");
	afisareVector(vectorMasini, nrMasini);


	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);
	dezalocare(&vectorMasini, &nrMasini);	

	return 0;
}