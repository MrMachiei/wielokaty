#include "../nagłówki/wielokat.h"

void wypiszOpcje();
void wypiszOpisy();
void wypiszDaneWielokat(wielokat *figura);
wielokat * wczytaj(wielokat *figura);
void poprawDane(wielokat* figura);
void wypiszCzasy(czas* pomiar);
void wypiszLista(lista_czas* lista);
void dokonajPomiaru(wielokat *figura, czas *pomiar);
wielokat* pobierzPlik(wielokat* figura, char *plik);
void zapiszDoPliku(wielokat* figura, lista_czas* lista,char *plik);
void zmienSciezke(char *dane);