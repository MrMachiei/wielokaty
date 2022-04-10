#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//struktury
typedef enum {false,true} bool;

typedef struct{
	float x, y;
} punkt;

typedef struct{
	int ileBokow;
	punkt* wierzcholki;
	bool wypukly;
}wielokat;

typedef struct{
	clock_t start,koniec;
	double czas;
	punkt p;
} czas;
typedef struct Lista_czas lista_czas;
struct Lista_czas{
	czas wartosc[3];
	lista_czas* next;
};
void dodajCzas(czas *wartosc, lista_czas **root);
// wczytywanie
void wczytajPunkt(punkt* p);
wielokat* wczytajWielokat(int ile);
void wczytajIloscBokow(int *ileB);
void wczytajPunktPlik(punkt* p,FILE *dane);
wielokat* wczytajWielokatPlik(wielokat* figura,FILE *dane);
czas* zainicjujCzasy();
// sprawdzenie czy jest wypukly O(n^2)
float obliczWyznacznik(punkt* a, punkt* b, punkt*c);
bool czyWypukly(wielokat* figura);
// usuwanie danych
void porzadek(wielokat *figura, czas *pomiary, lista_czas *lista);
// punkty
// algorytm siłowy - sprawdzenie czy dla każdego boku punkt leży po tej samej stronie boku
bool czyNalezy1(wielokat* figura, punkt* p);
// algorytm wykorzystujacy podzial na trojkaty 
bool sprawdzTrojkat(punkt *a, punkt *b, punkt *c, punkt *p);
bool czyNalezy2(wielokat* figura, punkt *p);
//algorytm przecięć
bool czyNalezy3(wielokat* figura, punkt *p);
//testowanie
void testuj(wielokat* figura, bool(* funk)(wielokat *, punkt*), czas *wynik, punkt *p);
void zapiszPlik(wielokat* figura, czas* pomiar, FILE* dane);
void zapiszPlikWiel(wielokat* figura, FILE* dane);
