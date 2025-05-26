//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct BibliotecaDigitala Biblioteca;
//struct BibliotecaDigitala {
//	int id;
//	int nrPagini;
//	float pret;
//	char* titlu;
//	char* autor;
//	unsigned char nivelAcces;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	Biblioteca info;
//};
//
//Biblioteca citireBibliotecaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Biblioteca b;
//
//	aux = strtok(buffer, sep);
//	b.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	b.nrPagini = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	b.pret = atof(aux);
//
//	aux = strtok(NULL, sep);
//	b.titlu = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(b.titlu, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	b.autor = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(b.autor, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	b.nivelAcces = *aux;
//	return b;
//}
//
//void afisareBiblioteca(Biblioteca b) {
//	printf("ID: %d\n", b.id);
//	printf("nr pagini: %d\n", b.nrPagini);
//	printf("pret: %.2f\n", b.pret);
//	printf("titlu: %s\n", b.titlu);
//	printf("autor: %s\n", b.autor);
//	printf("nivel acces: %c\n\n", b.nivelAcces);
//}
//
//void rotireStanga(Nod** radacina) {
//	Nod* aux = (*radacina)->dr;
//	(*radacina)->dr = aux->st;
//	aux->st = (*radacina);
//	(*radacina) = aux;
//}
//
//void rotireDreapta(Nod** radacina) {
//	Nod* aux = (*radacina)->st;
//	(*radacina)->st = aux->dr;
//	aux->dr = (*radacina);
//	(*radacina) = aux;
//}
//
//int calculNrNoduriAVL(Nod* radacina) {
//	if (radacina != NULL) {
//		return 1 + calculNrNoduriAVL(radacina->st) + calculNrNoduriAVL(radacina->dr);
//	}
//	return 0;
//}
//
//int calculInaltimeAVL(Nod* radacina) {
//	if (radacina != NULL) {
//		int inaltimeST = calculInaltimeAVL(radacina->st);
//		int inaltimeDR = calculInaltimeAVL(radacina->dr);
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
//int calculGradEchilibruAVL(Nod* radacina) {
//	if (radacina != NULL) {
//		return calculInaltimeAVL(radacina->st) - calculInaltimeAVL(radacina->dr);
//	}
//	return 0;
//}
//
//void adaugaBibliotecaAVL(Nod** radacina, Biblioteca b) {
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > b.id) {
//			adaugaBibliotecaAVL(&((*radacina)->st), b);
//		}
//		else if ((*radacina)->info.id < b.id) {
//			adaugaBibliotecaAVL(&((*radacina)->dr), b);
//		}
//		else {
//			(*radacina)->info = b;
//			if ((*radacina)->info.titlu != NULL) {
//				free((*radacina)->info.titlu);
//			}
//			if ((*radacina)->info.autor != NULL) {
//				free((*radacina)->info.autor);
//			}
//			(*radacina)->info.autor = (char*)malloc(strlen(b.autor) + 1);
//			strcpy_s((*radacina)->info.autor, strlen(b.autor) + 1, b.autor);
//
//			(*radacina)->info.titlu = (char*)malloc(strlen(b.titlu) + 1);
//			strcpy_s((*radacina)->info.titlu, strlen(b.titlu) + 1, b.titlu);
//
//
//		}
//
//		int gradDeEchilibru = calculGradEchilibruAVL((*radacina));
//
//		if (gradDeEchilibru == 2) {
//			if (calculGradEchilibruAVL((*radacina)->st) >= 0) {
//				rotireDreapta(radacina);
//			}
//			else {
//				rotireStanga(&((*radacina)->st));
//				rotireDreapta(radacina);
//			}
//		}
//		else if (gradDeEchilibru == -2) {
//			if (calculGradEchilibruAVL((*radacina)->dr) <= 0) {
//				rotireStanga(radacina);
//			}
//			else {
//				rotireDreapta(&((*radacina)->dr));
//				rotireStanga(radacina);
//			}
//		}
//	}
//	else {
//		(*radacina) = malloc(sizeof(Nod));
//		(*radacina)->info = b;
//		(*radacina)->info.autor = (char*)malloc(strlen(b.autor) + 1);
//		strcpy_s((*radacina)->info.autor, strlen(b.autor) + 1, b.autor);
//
//		(*radacina)->info.titlu = (char*)malloc(strlen(b.titlu) + 1);
//		strcpy_s((*radacina)->info.titlu, strlen(b.titlu) + 1, b.titlu);
//		(*radacina)->st = NULL;
//		(*radacina)->dr = NULL;
//	}
//}
//
//void afisareINORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareINORDINE(radacina->st);
//		afisareBiblioteca(radacina->info);
//		afisareINORDINE(radacina->dr);
//	}
//}
//
//void afisarePREORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareBiblioteca(radacina->info);
//		afisarePREORDINE(radacina->st);
//		afisarePREORDINE(radacina->dr);
//	}
//}
//
//void afisarePOSTORDINE(Nod* radacina) {
//	if (radacina != NULL) {
//		afisarePOSTORDINE(radacina->st);
//		afisarePOSTORDINE(radacina->dr);
//		afisareBiblioteca(radacina->info);
//	}
//}
//Nod* citireArboreDinFisier(const char* numefisier) {
//	FILE* file = fopen(numefisier, "r");
//	Nod* radacina = NULL;
//
//	while (!feof(file)) {
//		Biblioteca b = citireBibliotecaDinFisier(file);
//		adaugaBibliotecaAVL(&radacina, b);
//		free(b.titlu);
//		free(b.autor);
//	}
//	fclose(file);
//	return radacina;
//}
//
//float claculeazaPretTotal(Nod* radacina) {
//	if (radacina != NULL) {
//		float suma = 0;
//		
//		suma += radacina->info.pret;
//		float sumaST = claculeazaPretTotal(radacina->st);
//		float sumaDR = claculeazaPretTotal(radacina->dr);
//
//		return suma + sumaST + sumaDR;
//	}
//	return 0;
//}
//
//float calculeazaPretTotalPtUnAccesAnume(Nod* radacina, char nivelCerut) {
//	if (radacina != NULL) {
//		float suma = 0;
//		if (radacina->info.nivelAcces == nivelCerut) {
//			suma += radacina->info.pret;
//		}
//
//		suma += calculeazaPretTotalPtUnAccesAnume(radacina->st, nivelCerut);
//		suma += calculeazaPretTotalPtUnAccesAnume(radacina->dr, nivelCerut);
//
//		return suma;
//	}
//	return 0;
//}
//
//Biblioteca getBibliotecaByID(Nod* radacina, int id) {
//	Biblioteca b;
//	b.id = -1;
//	if (radacina != NULL) {
//		if (radacina->info.id > id) {
//			getBibliotecaByID(radacina->st, id);
//		}
//		else if(radacina->info.id<id){
//			getBibliotecaByID(radacina->dr, id);
//		}
//		else {
//			b = (radacina)->info;
//			b.titlu = (char*)malloc(strlen((radacina)->info.titlu) + 1);
//			strcpy_s(b.titlu, strlen((radacina)->info.titlu)+1, (radacina)->info.titlu);
//
//			b.autor = (char*)malloc(strlen((radacina)->info.autor) + 1);
//			strcpy_s(b.autor, strlen((radacina)->info.autor) + 1, (radacina)->info.autor);
//
//			return b;
//		}
//
//
//	}
//	return b;
//}
//
//int afisareNrCartiAutor(Nod* radacina, const char* numeAutor) {
//	if (radacina != NULL) {
//		int suma = 0;
//		int nrST= afisareNrCartiAutor(radacina->st, numeAutor);
//		int nrDR = afisareNrCartiAutor(radacina->dr, numeAutor);
//		if (strcmp((radacina->info.autor), numeAutor) == 0) {
//			suma = 1 + nrST + nrDR;
//		}
//		return suma;
//	}
//	return 0;
//}
//
//Biblioteca getBibliotecaCelMaiMicPret(Nod* radacina) {
//	Biblioteca min;
//	min.id = -1;
//	min.nrPagini = 0;
//	min.pret = 0.0f;
//	min.nivelAcces = '-';
//	min.autor = NULL;
//	min.titlu = NULL;
//
//	if (radacina != NULL) {
//		
//		Biblioteca bST = getBibliotecaCelMaiMicPret(radacina->st);
//		Biblioteca bDR = getBibliotecaCelMaiMicPret(radacina->dr);
//
//		if (bST.pret > bDR.pret && radacina->info.pret>bDR.pret) {
//			min = bDR;
//
//			if (min.titlu != NULL) {
//				free(min.titlu);
//			}
//
//			if (min.autor != NULL) {
//				free(min.autor);
//			}
//
//			min.titlu = (char*)malloc(strlen(bDR.titlu) + 1);
//			strcpy_s(min.titlu, strlen(bDR.titlu) + 1, bDR.titlu);
//
//			min.autor = (char*)malloc(strlen(bDR.autor) + 1);
//			strcpy_s(min.autor, strlen(bDR.autor) + 1, bDR.autor);
//		}
//		else if(bST.pret < bDR.pret && radacina->info.pret<bDR.pret) {
//			min = bST;
//
//			min.titlu = (char*)malloc(strlen(bST.titlu) + 1);
//			strcpy_s(min.titlu, strlen(bST.titlu) + 1, bST.titlu);
//
//			min.autor = (char*)malloc(strlen(bST.autor) + 1);
//			strcpy_s(min.autor, strlen(bST.autor) + 1, bST.autor);
//		}
//		else {
//			min = radacina->info;
//
//			min.titlu = (char*)malloc(strlen(radacina->info.titlu) + 1);
//			strcpy_s(min.titlu, strlen(radacina->info.titlu) + 1, radacina->info.titlu);
//
//			min.autor = (char*)malloc(strlen(radacina->info.autor) + 1);
//			strcpy_s(min.autor, strlen(radacina->info.autor) + 1, radacina->info.autor);
//		}
//		return min;
//	}
//	
//	return min;
//}
//
//void dezalocare(Nod** radacina) {
//	if ((*radacina) != NULL) {
//		dezalocare(&((*radacina)->st));
//		dezalocare(&((*radacina)->dr));
//		
//		free((*radacina)->info.autor);
//		free((*radacina)->info.titlu);
//		free(*radacina);
//		(*radacina) = NULL;
//	}
//}
//
//void main(){
//	Nod* avl =citireArboreDinFisier("biblioteciAVL.txt");
//
//	printf("\n\n========== IN ORDINE ============\n");
//	afisareINORDINE(avl);
//
//	printf("\n\n========== PRE ORDINE ============\n");
//	afisarePREORDINE(avl);
//
//	printf("\n\n========== POST ORDINE ============\n");
//	afisarePOSTORDINE(avl);
//
//	Biblioteca b;
//	b.id = 11;
//	b.nrPagini = 200;
//	b.nivelAcces = 'M';
//	b.pret = 9999.99;
//
//	b.titlu = (char*)malloc(strlen("Moara cu noroc")+1);
//	strcpy_s(b.titlu, strlen("Moara cu noroc") + 1, "Moara cu noroc");
//
//	b.autor = (char*)malloc(strlen("Ioan Slavici") + 1);
//	strcpy_s(b.autor, strlen("Ioan Slavici") + 1, "Ioan Slavici");
//
//	printf("\n\n================= DUPA ADAUGARE ==============\n\n");
//	adaugaBibliotecaAVL(&avl, b);
//	afisareINORDINE(avl);
//
//	printf("Nr carti mircea eliade: %d\n", afisareNrCartiAutor(avl, "Mircea Eliade"));
//	dezalocare(avl);
//}