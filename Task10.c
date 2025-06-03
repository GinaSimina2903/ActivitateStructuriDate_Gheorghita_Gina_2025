#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;
struct Nod {
    Nod* st;
    Nod* dr;
    Masina info;
};

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy_s(m1.model, strlen(aux) + 1, aux);

    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

    m1.serie = *strtok(NULL, sep);
    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

Nod* gasesteMinim(Nod* radacina) {
    while (radacina && radacina->st != NULL) {
        radacina = radacina->st;
    }
    return radacina;
}

void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
    if (*radacina != NULL) {
        if (masinaNoua.id < (*radacina)->info.id) {
            adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
        }
        else if (masinaNoua.id > (*radacina)->info.id) {
            adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
        }
        else {
            free((*radacina)->info.model);
            free((*radacina)->info.numeSofer);
            (*radacina)->info.nrUsi = masinaNoua.nrUsi;
            (*radacina)->info.pret = masinaNoua.pret;
            (*radacina)->info.serie = masinaNoua.serie;
            (*radacina)->info.model = malloc(strlen(masinaNoua.model) + 1);
            strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
            (*radacina)->info.numeSofer = malloc(strlen(masinaNoua.numeSofer) + 1);
            strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
        }
    }
    else {
        *radacina = malloc(sizeof(Nod));
        (*radacina)->info = masinaNoua;
        (*radacina)->info.model = malloc(strlen(masinaNoua.model) + 1);
        strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
        (*radacina)->info.numeSofer = malloc(strlen(masinaNoua.numeSofer) + 1);
        strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
        (*radacina)->st = NULL;
        (*radacina)->dr = NULL;
    }
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    Nod* radacina = NULL;
    while (!feof(file)) {
        Masina m = citireMasinaDinFisier(file);
        adaugaMasinaInArbore(&radacina, m);
        free(m.model);
        free(m.numeSofer);
    }
    fclose(file);
    return radacina;
}

void afisareArboreInOrdine(Nod* radacina) {
    if (radacina != NULL) {
        afisareArboreInOrdine(radacina->st);
        afisareMasina(radacina->info);
        afisareArboreInOrdine(radacina->dr);
    }
}

void afisareArborePreOrdine(Nod* radacina) {
    if (radacina != NULL) {
        afisareMasina(radacina->info);
        afisareArborePreOrdine(radacina->st);
        afisareArborePreOrdine(radacina->dr);
    }
}

int determinaNumarNoduri(Nod* radacina) {
    if (radacina != NULL) {
        return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
    }
    return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
    if (radacina != NULL) {
        int inaltimeST = calculeazaInaltimeArbore(radacina->st);
        int inaltimeDR = calculeazaInaltimeArbore(radacina->dr);
        return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
    }
    return 0;
}

float calculeazaPretTotal(Nod* radacina) {
    if (radacina == NULL) {
        return 0.0f;
    }
    return radacina->info.pret
        + calculeazaPretTotal(radacina->st)
        + calculeazaPretTotal(radacina->dr);
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
    if (radacina == NULL) {
        return 0.0f;
    }
    float sumaSt = calculeazaPretulMasinilorUnuiSofer(radacina->st, numeSofer);
    float sumaDr = calculeazaPretulMasinilorUnuiSofer(radacina->dr, numeSofer);
    if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
        return radacina->info.pret + sumaSt + sumaDr;
    }
    else {
        return sumaSt + sumaDr;
    }
}

Masina getMasinaByID(Nod* radacina, int id) {
    Masina m;
    m.id = -1;
    if (radacina == NULL) {
        return m;
    }
    if (id > radacina->info.id) {
        return getMasinaByID(radacina->dr, id);
    }
    else if (id < radacina->info.id) {
        return getMasinaByID(radacina->st, id);
    }
    else {
        m = radacina->info;
        m.numeSofer = malloc(strlen(radacina->info.numeSofer) + 1);
        strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
        m.model = malloc(strlen(radacina->info.model) + 1);
        strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
        return m;
    }
}

Nod* stergeNod(Nod* radacina, int idDeSters) {
    if (radacina == NULL) {
        return NULL;
    }

    if (idDeSters < radacina->info.id) {
        radacina->st = stergeNod(radacina->st, idDeSters);
    }
    else if (idDeSters > radacina->info.id) {
        radacina->dr = stergeNod(radacina->dr, idDeSters);
    }
    else {
        if (radacina->st == NULL) {
            Nod* temp = radacina->dr;
            free(radacina->info.model);
            free(radacina->info.numeSofer);
            free(radacina);
            return temp;
        }
        else if (radacina->dr == NULL) {
            Nod* temp = radacina->st;
            free(radacina->info.model);
            free(radacina->info.numeSofer);
            free(radacina);
            return temp;
        }

        Nod* succesor = gasesteMinim(radacina->dr);
        free(radacina->info.model);
        free(radacina->info.numeSofer);
        radacina->info.id = succesor->info.id;
        radacina->info.nrUsi = succesor->info.nrUsi;
        radacina->info.pret = succesor->info.pret;
        radacina->info.serie = succesor->info.serie;
        radacina->info.model = malloc(strlen(succesor->info.model) + 1);
        strcpy_s(radacina->info.model, strlen(succesor->info.model) + 1, succesor->info.model);
        radacina->info.numeSofer = malloc(strlen(succesor->info.numeSofer) + 1);
        strcpy_s(radacina->info.numeSofer, strlen(succesor->info.numeSofer) + 1, succesor->info.numeSofer);

        radacina->dr = stergeNod(radacina->dr, succesor->info.id);
    }
    return radacina;
}

Nod* subarboreMaiInalt(Nod* radacina) {
    if (radacina == NULL) {
        return NULL;
    }
    int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
    int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);
    if (inaltimeSt >= inaltimeDr) {
        return radacina->st;
    }
    else {
        return radacina->dr;
    }
}

int numarSubordine(Nod* radacina) {
    if (radacina == NULL) {
        return 0;
    }
    return determinaNumarNoduri(radacina) - 1;
}

Nod* subarboreCuMaiMulteNoduri(Nod* radacina) {
    if (radacina == NULL) {
        return NULL;
    }
    int cntSt = determinaNumarNoduri(radacina->st);
    int cntDr = determinaNumarNoduri(radacina->dr);
    if (cntSt >= cntDr) {
        return radacina->st;
    }
    else {
        return radacina->dr;
    }
}

void dezalocareArboreDeMasini(Nod** radacina) {
    if (*radacina != NULL) {
        dezalocareArboreDeMasini(&((*radacina)->st));
        dezalocareArboreDeMasini(&((*radacina)->dr));
        free((*radacina)->info.model);
        free((*radacina)->info.numeSofer);
        free(*radacina);
        *radacina = NULL;
    }
}

int main() {
    Nod* arbore = citireArboreDeMasiniDinFisier("masiniArbore.txt");
    if (arbore == NULL) {
        return 1;
    }

    printf("===== in ordine =====\n");
    afisareArboreInOrdine(arbore);

    int idDeSters = 2;
    arbore = stergeNod(arbore, idDeSters);
    printf("\n===== Stergerea nodului cu ID = %d =====\n", idDeSters);
    afisareArboreInOrdine(arbore);

    Nod* arbMaiInalt = subarboreMaiInalt(arbore);
    if (arbMaiInalt) {
        printf("\nSubarborele cu h mai mare ( ID = %d):\n", arbMaiInalt->info.id);
        afisareMasina(arbMaiInalt->info);
    }
    else {
        printf("\nArborele este gol sau nu are subarbori.\n");
    }

    int subNr = numarSubordine(arbore);
    printf("\nnr noduri in subordine pentru nodul cu id (ID = %d): %d\n", arbore->info.id, subNr);

    Nod* arbMaiMulte = subarboreCuMaiMulteNoduri(arbore);
    if (arbMaiMulte) {
        printf("\nSubarborele cu cele mai multe noduri in subordine ( ID = %d):\n", arbMaiMulte->info.id);
        afisareMasina(arbMaiMulte->info);
    }
    else {
        printf("\nArborele este gol sau nu are subarbori.\n");
    }

    printf("\nnr total de noduri în arbore: %d\n", determinaNumarNoduri(arbore));
    printf("h arbore: %d\n", calculeazaInaltimeArbore(arbore));

    float pretTotal = calculeazaPretTotal(arbore);
    printf("\npret total: %.2f\n", pretTotal);
    const char* soferCautat = "Popescu Ion";
    float pretSofer = calculeazaPretulMasinilorUnuiSofer(arbore, soferCautat);
    printf("pret total al masinilor soferului \"%s\": %.2f\n", soferCautat, pretSofer);

    dezalocareArboreDeMasini(&arbore);
    return 0;
}
