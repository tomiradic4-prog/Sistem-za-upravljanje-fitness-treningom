#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "fitness.h"
#include "globals.h"

typedef enum
{
    IZLAZ = 0,
    DODAJ = 1,
    PRIKAZ,
    UREDI,
    OBRISI,
    BMI,
    KALORIJE,
    SORTIRAJ,
    PRETRAZI

} Menu;

int main(void)
{
    int izbor;

    ucitajDatoteku();

    do
    {
        printf("\n===== FITNESS TRACKER =====\n");

        printf("1. Dodaj korisnika\n");
        printf("2. Prikazi korisnike\n");
        printf("3. Uredi korisnika\n");
        printf("4. Obrisi korisnika\n");
        printf("5. BMI kalkulator\n");
        printf("6. Kalorije kalkulator\n");
        printf("7. Sortiraj po tezini\n");
        printf("8. Pretrazi po ID\n");
        printf("0. Izlaz\n");

        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor)
        {
        case DODAJ:
            dodajKorisnika();
            break;

        case PRIKAZ:
            prikaziKorisnike();
            break;

        case UREDI:
            urediKorisnika();
            break;

        case OBRISI:
            obrisiKorisnika();
            break;

        case BMI:
            bmiKalkulator();
            break;

        case KALORIJE:
            kalorijeKalkulator();
            break;

        case SORTIRAJ:
            sortirajPoTezini();
            break;

        case PRETRAZI:
            pretraziPoId();
            break;
        }

    } while (izbor != 0);

    free(korisnici);
    korisnici = NULL;

    return 0;
}