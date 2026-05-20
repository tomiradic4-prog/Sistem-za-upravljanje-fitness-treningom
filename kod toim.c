  

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Trening {
    int id;
    char naziv[50];
    int trajanje;
    int kalorije;
};

struct Trening treninzi[MAX];
int brojTreninga = 0;

void spremiDatoteku() {

    FILE* file;
    int i;

    file = fopen("treninzi.txt", "w");

    if (file == NULL) {
        printf("Greska kod otvaranja datoteke!\n");
        return;
    }

    for (i = 0; i < brojTreninga; i++) {
        fprintf(file, "%d;%s;%d;%d\n",
            treninzi[i].id,
            treninzi[i].naziv,
            treninzi[i].trajanje,
            treninzi[i].kalorije);
    }

    fclose(file);
}

void ucitajDatoteku() {

    FILE* file;
    file = fopen("treninzi.txt", "r");

    if (file == NULL) {
        return;
    }

    brojTreninga = 0;

    while (fscanf(file, "%d;%49[^;];%d;%d\n",
        &treninzi[brojTreninga].id,
        treninzi[brojTreninga].naziv,
        &treninzi[brojTreninga].trajanje,
        &treninzi[brojTreninga].kalorije) == 4) {

        brojTreninga++;
    }

    fclose(file);
}

void dodajTrening() {

    if (brojTreninga >= MAX) {
        printf("Maksimalan broj treninga!\n");
        return;
    }

    printf("Unesi ID: ");
    scanf("%d", &treninzi[brojTreninga].id);

    getchar();

    printf("Unesi naziv treninga: ");
    fgets(treninzi[brojTreninga].naziv, 50, stdin);

    treninzi[brojTreninga].naziv[strcspn(treninzi[brojTreninga].naziv, "\n")] = 0;

    printf("Unesi trajanje: ");
    scanf("%d", &treninzi[brojTreninga].trajanje);

    printf("Unesi kalorije: ");
    scanf("%d", &treninzi[brojTreninga].kalorije);

    brojTreninga++;

    spremiDatoteku();

    printf("Trening dodan!\n");
}

void prikaziTreninge() {

    int i;

    if (brojTreninga == 0) {
        printf("Nema treninga.\n");
        return;
    }

    for (i = 0; i < brojTreninga; i++) {

        printf("\n-------------------\n");
        printf("ID: %d\n", treninzi[i].id);
        printf("Naziv: %s\n", treninzi[i].naziv);
        printf("Trajanje: %d min\n", treninzi[i].trajanje);
        printf("Kalorije: %d\n", treninzi[i].kalorije);
    }
}

void obrisiTrening() {

    int id;
    int i, j;
    int pronaden = 0;

    printf("Unesi ID za brisanje: ");
    scanf("%d", &id);

    for (i = 0; i < brojTreninga; i++) {

        if (treninzi[i].id == id) {

            for (j = i; j < brojTreninga - 1; j++) {
                treninzi[j] = treninzi[j + 1];
            }

            brojTreninga--;
            spremiDatoteku();

            printf("Trening obrisan.\n");

            pronaden = 1;
            break;
        }
    }

    if (!pronaden) {
        printf("Trening nije pronaden.\n");
    }
}

void urediTrening() {

    int id;
    int i;
    int pronaden = 0;

    printf("Unesi ID za uređivanje: ");
    scanf("%d", &id);

    getchar();

    for (i = 0; i < brojTreninga; i++) {

        if (treninzi[i].id == id) {

            printf("Novi naziv: ");
            fgets(treninzi[i].naziv, 50, stdin);
            treninzi[i].naziv[strcspn(treninzi[i].naziv, "\n")] = 0;

            printf("Novo trajanje: ");
            scanf("%d", &treninzi[i].trajanje);

            printf("Nove kalorije: ");
            scanf("%d", &treninzi[i].kalorije);

            spremiDatoteku();

            printf("Trening azuriran.\n");

            pronaden = 1;
            break;
        }
    }

    if (!pronaden) {
        printf("Trening nije pronaden.\n");
    }
}

void menu() {

    int izbor;

    do {
        printf("\n===== FITNESS MANAGER =====\n");
        printf("1. Dodaj trening\n");
        printf("2. Prikazi treninge\n");
        printf("3. Uredi trening\n");
        printf("4. Obrisi trening\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");

        scanf("%d", &izbor);

        switch (izbor) {

        case 1: dodajTrening(); break;
        case 2: prikaziTreninge(); break;
        case 3: urediTrening(); break;
        case 4: obrisiTrening(); break;
        case 0: printf("Gasenje...\n"); break;
        default: printf("Pogresan unos!\n");
        }

    } while (izbor != 0);
}

int main() {

    ucitajDatoteku();
    menu();

    return 0;
}
