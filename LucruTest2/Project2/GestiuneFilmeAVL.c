#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct Film Film;
struct Film {
	int id;
	int durata;
	float rating;
	char* titlu;
	unsigned char categorie;
};

typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
	Film info;
};

Film citireFilmDinFisier(FILE* file) {
	char buffer[100];
	char sep[4] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Film f;

	aux = strtok(buffer, sep);
	f.id = atoi(aux);

	aux = strtok(NULL, sep);
	f.durata = atoi(aux);

	aux = strtok(NULL, sep);
	f.rating = atof(aux);

	aux = strtok(NULL, sep);
	f.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(f.titlu, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	f.categorie = *aux;
	return f;
}

void afisareFilm(Film f) {
	printf("id: %d\n", f.id);
	printf("durata: %d\n", f.durata);
	printf("rating: %.2f\n", f.durata);
	printf("titlu: %s\n", f.titlu);
	printf("categorie: %c\n\n", f.categorie);
}

void rotireStanga(Nod** radacina) {
	if ((*radacina) != NULL) {
		Nod* aux = (*radacina)->st;
		(*radacina)->st = aux->dr;
		aux->dr = (*radacina);
		(*radacina) = aux;
	}
}

void rotireDreapta(Nod** radacina) {
	if ((*radacina) != NULL) {
		Nod* aux = (*radacina)->dr;
		(*radacina)->dr = aux->st;
		aux->st = (*radacina);
		(*radacina) = aux;
	}
}

int calclulGradDeEchilibru(Nod* radacina) {
	if (radacina != NULL) {
		return calclulGradDeEchilibru(radacina->st) - calclulGradDeEchilibru(radacina->dr);
	}
	return 0;
}

int calculInaltime(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeST = 1 + calculInaltime(radacina->st);
		int inaltimeDR = 1 + calculInaltime(radacina->dr);

		if (inaltimeST > inaltimeDR) {
			return inaltimeST;
		}
		else { 
			return inaltimeDR; 
		}
	}
	return 0;
}

void adaugaFilmInAvl(Nod** radacina, Film f) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > f.id) {
			adaugaFilmInAvl(&((*radacina)->st), f);
		}
		else if ((*radacina)->info.id < f.id) {
			adaugaFilmInAvl(&((*radacina)->dr), f);
		}
		else {
			(*radacina)->info = f;
			if ((*radacina)->info.titlu != NULL) {
				free((*radacina)->info.titlu);
			}
			(*radacina)->info.titlu = (char*)malloc(strlen(f.titlu) + 1);
			strcpy_s((*radacina)->info.titlu, strlen(f.titlu) + 1, f.titlu);
		}

		int gradDeEchilibru = calclulGradDeEchilibru((*radacina));

		if (gradDeEchilibru == 2) {
			if (calclulGradDeEchilibru((*radacina)->st) >= 0) { //ll
				rotireDreapta(radacina);
			}
			else { //lr
				rotireStanga(&((*radacina)->st));
				rotireDreapta(radacina);
			}
		}

		if (gradDeEchilibru == -2) {
			if (calclulGradDeEchilibru((*radacina)->dr) <= 0) { //rr
				rotireStanga(radacina);
			}
			else { //rl
				rotireDreapta(&((*radacina)->dr));
				rotireStanga(radacina);
			}
		}
	}
	else {
		*radacina = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = f;
		(*radacina)->info.titlu = (char*)malloc(strlen(f.titlu) + 1);
		strcpy_s((*radacina)->info.titlu, strlen(f.titlu) + 1, f.titlu);
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

void afisarePostOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisarePostOrdine(radacina->st);
		afisarePostOrdine(radacina->dr);
		afisareFilm(radacina->info);
	}
}

void afisarePreOrdine(Nod* radacina){
	if (radacina != NULL) {
		afisareFilm(radacina->info);
		afisarePreOrdine(radacina->st);
		afisarePreOrdine(radacina->dr);

	}
}
Nod* citireABCDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(file)) {
		Film f = citireFilmDinFisier(file);
		adaugaFilmInAvl(&radacina,f);
		free(f.titlu);
	}
	fclose(file);
	return radacina;
}

int nrNoduriAVL(Nod* radacina) {
	if (radacina != NULL) {
		return 1 + nrNoduriAVL(radacina->st) + nrNoduriAVL(radacina->dr);
	}
	return 0;
}

float calculeazaSumaRatingFilme(Nod* radacina) {
	if (radacina != NULL) {
		
		float suma = radacina->info.rating + calculeazaSumaRatingFilme(radacina->dr)+calculeazaSumaRatingFilme(radacina->st);
		
		return suma;
	}
	return 0.0f;
}

float calculeazaMediaRatingFilme(Nod* radacina) {
	if (radacina != NULL) {
		printf("%.2f\n", calculeazaSumaRatingFilme(radacina));
		printf("%d\n", nrNoduriAVL(radacina));
		return (float)(calculeazaSumaRatingFilme(radacina) / nrNoduriAVL(radacina));
	}
	return 0.0f;
}

void dezalocareAVL(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocareAVL(&((*radacina)->st));
		dezalocareAVL(&((*radacina)->dr));
		free((*radacina)->info.titlu);
		free(*radacina);
		(*radacina) = NULL;
	}
}
void main() {
	Nod* avl = citireABCDinFisier("filme.txt");

	printf("post\n\n");
	afisarePostOrdine(avl);

	printf("pre\n\n");
	afisarePreOrdine(avl);

	Film f;
	f.id = 6;
	f.durata = 66;
	f.rating = 6.6f;
	f.titlu = "Titlu6";
	f.categorie = '-';

	adaugaFilmInAvl(&avl, f);
	afisarePreOrdine(avl);

	printf("Inaltimea arbore: %d\n\n", calculInaltime(avl));

	printf("media rating: %.2f\n\n", calculeazaMediaRatingFilme(avl));
	dezalocareAVL(&avl);
}