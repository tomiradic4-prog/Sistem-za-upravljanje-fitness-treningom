#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fitness.h"
#include "globals.h"

static const char* DATOTEKA = "fitness.bin";

void spremiDatoteku(void)
{
    FILE* file = fopen(DATOTEKA, "wb");

    if (file == NULL)
    {
        perror("Greska datoteke");
        return;
    }

    fwrite(&brojKorisnika,
        sizeof(int),
        1,
        file);

    fwrite(korisnici,
        sizeof(Korisnik),
        brojKorisnika,
        file);

    fclose(file);
}

void ucitajDatoteku(void)
{
    FILE* file = fopen(DATOTEKA, "rb");

    if (file == NULL)
        return;

    fread(&brojKorisnika,
        sizeof(int),
        1,
        file);

    if (brojKorisnika > 0)
    {
        korisnici =
            malloc(
                brojKorisnika *
                sizeof(Korisnik));

        if (korisnici == NULL)
        {
            fclose(file);
            return;
        }

        fread(korisnici,
            sizeof(Korisnik),
            brojKorisnika,
            file);
    }

    fclose(file);
}

void dodajKorisnika(void)
{
    Korisnik novi;

    printf("ID: ");
    scanf("%d", &novi.id);

    printf("Ime: ");
    scanf("%49s", novi.ime);

    printf("Godine: ");
    scanf("%d", &novi.godine);

    printf("Tezina: ");
    scanf("%f", &novi.tezina);

    printf("Visina (m): ");
    scanf("%f", &novi.visina);

    Korisnik* temp =
        realloc(
            korisnici,
            (brojKorisnika + 1) *
            sizeof(Korisnik));

    if (temp == NULL)
    {
        perror("realloc");
        return;
    }

    korisnici = temp;
    korisnici[brojKorisnika] = novi;

    brojKorisnika++;

    spremiDatoteku();

    printf("Korisnik dodan.\n");
}

void prikaziKorisnike(void)
{
    if (brojKorisnika == 0)
    {
        printf("Nema korisnika.\n");
        return;
    }

    for (int i = 0; i < brojKorisnika; i++)
    {
        printf("\n------------------\n");

        printf("ID: %d\n",
            korisnici[i].id);

        printf("Ime: %s\n",
            korisnici[i].ime);

        printf("Godine: %d\n",
            korisnici[i].godine);

        printf("Tezina: %.1f kg\n",
            korisnici[i].tezina);

        printf("Visina: %.2f m\n",
            korisnici[i].visina);
    }
}

void urediKorisnika(void)
{
    int id;

    printf("ID korisnika: ");
    scanf("%d", &id);

    for (int i = 0; i < brojKorisnika; i++)
    {
        if (korisnici[i].id == id)
        {
            printf("Novo ime: ");
            scanf("%49s",
                korisnici[i].ime);

            printf("Nova tezina: ");
            scanf("%f",
                &korisnici[i].tezina);

            spremiDatoteku();

            printf("Azurirano.\n");
            return;
        }
    }

    printf("Korisnik nije pronaden.\n");
}

void obrisiKorisnika(void)
{
    int id;

    printf("ID za brisanje: ");
    scanf("%d", &id);

    for (int i = 0; i < brojKorisnika; i++)
    {
        if (korisnici[i].id == id)
        {
            for (int j = i;
                j < brojKorisnika - 1;
                j++)
            {
                korisnici[j] =
                    korisnici[j + 1];
            }

            brojKorisnika--;

            spremiDatoteku();

            printf("Obrisano.\n");
            return;
        }
    }

    printf("Korisnik nije pronaden.\n");
}

void bmiKalkulator(void)

{
    float tezina = 0.0f;
    float visina = 0.0f;
    float bmi = 0.0f;

    printf("Unesi tezinu u kg: ");
    scanf("%f", &tezina);

    printf("Unesi visinu u metrima, npr. 1.80: ");
    scanf("%f", &visina);

    if (tezina <= 0 || visina <= 0)
    {
        printf("Greska: tezina i visina moraju biti vece od 0.\n");
        return;
    }

    bmi = tezina / (visina * visina);

    printf("Tvoj BMI je: %.2f\n", bmi);

    if (bmi < 18.5f)
        printf("Kategorija: Pothranjenost\n");
    else if (bmi < 25.0f)
        printf("Kategorija: Normalna tezina\n");
    else if (bmi < 30.0f)
        printf("Kategorija: Prekomjerna tezina\n");
    else
        printf("Kategorija: Pretilost\n");
}

void kalorijeKalkulator(void)
{
    float kg;
    float cm;
    int godine;

    printf("Tezina: ");
    scanf("%f", &kg);

    printf("Visina(cm): ");
    scanf("%f", &cm);

    printf("Godine: ");
    scanf("%d", &godine);

    float bmr =
        10 * kg +
        6.25f * cm -
        5 * godine +
        5;

    printf("Kalorije za odrzavanje: %.0f\n",
        bmr * 1.55f);
}

static int compareWeight(
    const void* a,
    const void* b)
{
    const Korisnik* x = a;
    const Korisnik* y = b;

    if (x->tezina > y->tezina)
        return 1;

    if (x->tezina < y->tezina)
        return -1;

    return 0;
}

void sortirajPoTezini(void)
{
    qsort(korisnici,
        brojKorisnika,
        sizeof(Korisnik),
        compareWeight);

    printf("Sortirano.\n");
}

static int compareIdSort(
    const void* a,
    const void* b)
{
    const Korisnik* x = a;
    const Korisnik* y = b;

    return x->id - y->id;
}

static int compareIdSearch(
    const void* key,
    const void* element)
{
    int id =
        *(const int*)key;

    const Korisnik* k =
        element;

    return id - k->id;
}

void pretraziPoId(void)
{
    int id;

    printf("ID: ");
    scanf("%d", &id);

    qsort(korisnici,
        brojKorisnika,
        sizeof(Korisnik),
        compareIdSort);

    Korisnik* rezultat =
        bsearch(
            &id,
            korisnici,
            brojKorisnika,
            sizeof(Korisnik),
            compareIdSearch);

    if (rezultat)
    {
        printf("Pronaden: %s\n",
            rezultat->ime);
    }
    else
    {
        printf("Nije pronaden.\n");
    }
}
