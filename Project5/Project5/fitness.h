#pragma once

#ifndef FITNESS_H
#define FITNESS_H

#define MAX_NAME 50

typedef struct
{
    int id;
    char ime[MAX_NAME];
    int godine;
    float tezina;
    float visina;

} Korisnik;

void dodajKorisnika(void);
void prikaziKorisnike(void);
void urediKorisnika(void);
void obrisiKorisnika(void);

void spremiDatoteku(void);
void ucitajDatoteku(void);

void bmiKalkulator(void);
void kalorijeKalkulator(void);

void sortirajPoTezini(void);
void pretraziPoId(void);

#endif