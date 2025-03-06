#include<stdio.h>
#include<stdlib.h>
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

void copiazaMasiniCuTonajMic(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
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

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}
	

int main() {
	struct Masina m;
	m = initializare(1, "Audi", 2.3, 'S');
	afisare(m);

	int nrMasini = 3;
	struct Masina* vectorMasini;
	vectorMasini = malloc(sizeof(struct Masina)*nrMasini);
	vectorMasini[0] = initializare(2, "BMW", 2.2, 'C');
	vectorMasini[1] = initializare(3, "Mercedes", 2.6, 'A');
	vectorMasini[2] = initializare(4, "Fiat", 1.8, 'T');

	afisareVector(vectorMasini, nrMasini);

	struct Masina* vectorMasiniCopiate;
	int nrMasiniCopiate = 2;
	
	vectorMasiniCopiate = copiazaPrimeleNMasini(vectorMasini,nrMasini,nrMasiniCopiate);
	printf("\n\n-------------------MASINI COPIATE--------------------\n");
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);


	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);

	printf("\n\n-------------------MASINI USOARE--------------------\n");
	copiazaMasiniCuTonajMic(vectorMasini, nrMasini, 2.5, &vectorMasiniCopiate, &nrMasiniCopiate );
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);


	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);

	return 0;
}