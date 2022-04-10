#include "../nagłówki/wielokat.h"
//struktury
void wczytajPunkt(punkt* p){
	while(1){
		printf("Podaj współrzędne wierzchołka: ");
		if(!scanf("%f %f", &(p->x), &(p->y))){
			fflush(stdin);
			printf("Błędne dane!\n\n");
		}else break;
	}
	fflush(stdin);
}
wielokat* wczytajWielokat(int ile){
	wielokat* figura = (wielokat*)malloc(sizeof(wielokat));
	figura->ileBokow = ile;
	figura->wypukly = false;
	figura->wierzcholki = (punkt*)malloc(sizeof(punkt)*ile);
	for(int i = 0; i < ile; i++){
		wczytajPunkt(figura->wierzcholki + i);
	}
	figura->wypukly = czyWypukly(figura);
	if(figura->wypukly) printf("\n                  Wielokąt jest wypukły.\n");
	else printf("\n              Wielokąt nie jest wypukły.\n");
	return figura;
}
void wczytajPunktPlik(punkt* p,FILE *dane){
	while(1){
		if(!fscanf(dane,"%f %f", &(p->x), &(p->y))){
			fflush(stdin);
			printf("Błędne dane!\n\n");
		}else break;
	}
	fflush(stdin);
}
wielokat* wczytajWielokatPlik(wielokat* figura, FILE *dane){
	if(figura != NULL){
		printf("Figura została już wczytana!\n");
		return NULL;
	}
	figura = (wielokat*)malloc(sizeof(wielokat));
	fscanf(dane,"%d",&(figura->ileBokow));
	figura->wypukly = false;
	int ile = figura->ileBokow;
	figura->wierzcholki = (punkt*)malloc(sizeof(punkt)*ile);
	for(int i = 0; i < ile; i++){
		wczytajPunktPlik(figura->wierzcholki + i, dane);
	}
	figura->wypukly = czyWypukly(figura);
	if(figura->wypukly) printf("\n                  Wielokąt jest wypukły.\n");
	else printf("\n              Wielokąt nie jest wypukły.\n");
	return figura;
}
void wczytajIloscBokow(int *ileB){
	bool czy;
	while(1){
		printf("Podaj ilość wierzchołków wielokąta: ");
		if(!scanf("%d", ileB)) fflush(stdin);
		fflush(stdin);
		if(*ileB < 3){
			printf("Błędna ilośc wierzchołków! Podaj n > 2!\n\n");
		}else break;
	}
}
// sprawdzenie czy jest wypukly O(n^2)
float obliczWyznacznik(punkt* a, punkt* b, punkt*c){
	return a->x*b->y + b->x*c->y + c->x*a->y - c->x*b->y - a->x*c->y - b->x*a->y;
}
bool czyWypukly(wielokat* figura){
	int ile = figura->ileBokow;
	float kierunek;
	short znak = 0;
	punkt * p;
	for(int i = 0; i < ile-1; i++){
		punkt *b, *a = figura->wierzcholki + i;
		if(i + 1 == ile) b = figura->wierzcholki;
		else b = figura->wierzcholki + i+1;
		if (i+2 < ile) p = figura->wierzcholki + i+2;
		else p = figura->wierzcholki + i-1; 
		for(int j = 0; j < ile; j++){
			p = figura->wierzcholki + j;
			if(p == a || p == b) continue;
			kierunek = obliczWyznacznik(a, b, p);
			if(znak == 0){
				if(kierunek < 0) znak = -1;
				else znak = 1;
			}
			if(kierunek*znak < 0 || kierunek == 0) return false;
		}
	}
	return true;
}
// usuwanie danych
void porzadek(wielokat *figura,czas *pomiary, lista_czas *lista){
	free(figura->wierzcholki);
	free(figura);
	lista_czas *temp;
	while(lista->next != NULL){
		temp = lista;
		lista = lista->next;
		free(temp);
	}
	free(lista);
	free(pomiary);
}
// punkty
// algorytm 1 - sprawdzenie czy dla każdego boku punkt leży po tej samej stronie boku O(n)
bool czyNalezy1(wielokat* figura, punkt* p){
	int ile = figura->ileBokow;
	float kierunek;
	short znak = 0;
	punkt *b, *a;
	for(int i = 0; i < ile; i++){
		a = figura->wierzcholki + i;
		if(i + 1 == ile) b = figura->wierzcholki;
		else b = figura->wierzcholki + i+1;
		kierunek = obliczWyznacznik(a,b,p);
		if(znak == 0){
			if(kierunek < 0) znak = -1;
			else znak = 1;
		}
		if(kierunek*znak < 0) return 0;
	}
	return 1;
}
// algorytm wykorzystujacy podzial na trojkaty - O(n), ale lepszy warunek optymistyczny, zoptymalizowanie średniego
bool sprawdzTrojkat(punkt *a, punkt *b, punkt *c, punkt *p){
	//printf("A: %f,%f, B: %f,%f, C: %f, %f\n", a->x, a->y, b->x, b->y,c->x, c->y);
	float kierunek;
	short znak = 0;
	kierunek = obliczWyznacznik(a,b,p);
	if(znak == 0){
		if(kierunek < 0) znak = -1;
		else znak = 1;
	}
	if(kierunek*znak < 0) return 0;
	kierunek = obliczWyznacznik(b,c,p);
	if(znak == 0){
		if(kierunek < 0) znak = -1;
		else znak = 1;
	}
	if(kierunek*znak < 0) return 0;
	kierunek = obliczWyznacznik(c,a,p);
	if(znak == 0){
		if(kierunek < 0) znak = -1;
		else znak = 1;
	}
	if(kierunek*znak < 0) return 0;
	return 1;
}
bool czyNalezy2(wielokat* figura, punkt *p){
	int ile = figura->ileBokow;
	punkt *a,*b;
	for(int i = 0; i < ile-2; i++){
		a = figura->wierzcholki + i+1, b = figura->wierzcholki + i + 2;
		if(sprawdzTrojkat(figura->wierzcholki, a, b, p)) return 1;
	}
	return 0;
}
// algorytm wykorzystujący ilość przecięc - również O(n) - metoda bez wyznacznika
bool czyNalezy3(wielokat* figura, punkt *p){
	punkt *b, *a;
	int ile = figura->ileBokow, ilePrzeciec = 0;
	float xPrzeciecia;
	for(int i = 0; i < ile; i++){
		a = figura->wierzcholki + i;
		if(i + 1 == ile) b = figura->wierzcholki;
		else b = figura->wierzcholki + i+1;
		if((a->x == p->x && p->y == a->y) || (p->x == b->x && p->y == b->y)) return 1;
		if(a->y == b->y  == p->y){
			if((a->x < b->x) && (p->x >= a->x && p->x <= b->x)) return 1;
			if((b->x < a->x) && (p->x >= b->x && p->x <= a->x)) return 1;
		}
		if(a->x == b->x  == p->x){
			if((a->y < b->y) && (p->y >= a->y && p->y <= b->y)) return 1;
			if((b->y < a->y) && (p->y >= b->y && p->y <= a->y)) return 1;
		}
		if ((a->y < p->y && b->y >= p->y) || (a->y >= p->y && b->y < p->y)){
			if(a->x == b->x == p ->x ){
				ilePrzeciec++;
				continue;
			}
			xPrzeciecia = a->x + (p->y-a->y)*(b->x-a->x)/(b->y-a->y);
			if(xPrzeciecia >= p->x){
				ilePrzeciec++;
				continue;
			}
		}
	}
	return ilePrzeciec & 1;
}
void testuj(wielokat* figura, bool(* funk)(wielokat *, punkt*), czas *wynik, punkt *p){
	wynik->start = clock();
	if(funk(figura, p)){
		printf("Punkt należy do wielokąta!\n");
	}else printf("Punkt nie należy do wielokąta!\n");
	wynik->koniec = clock();
	wynik->czas = (double)(wynik->koniec-wynik->start) / CLOCKS_PER_SEC;
}
czas* zainicjujCzasy(){
	czas *pomiary = (czas*)malloc(sizeof(czas)*3);
	for(int i = 0; i < 3; i++){
		(pomiary+i)->start = -1;
		(pomiary+i)->koniec = -1;
		(pomiary+i)->czas = 0;
		(pomiary+i)->p.x = 0;
		(pomiary+i)->p.y = 0;
	}
	return pomiary;
}
void zapiszPlikWiel(wielokat* figura, FILE* dane){
	int ile = figura->ileBokow;
	fprintf(dane,"\n-------------DANE WIELOKĄTA-------------\n");
	for(int i = 0; i < ile; i++){
		fprintf(dane,"WIERZCHOŁEK %d: (%f, %f)\n", (i+1), (figura->wierzcholki)[i].x,(figura->wierzcholki)[i].y);
	}
	if(figura->wypukly) fprintf(dane,"\n                  Wielokąt jest wypukły.\n");
	else fprintf(dane,"\n              Wielokąt nie jest wypukły.\n");
	fprintf(dane,"----------------------------------------\n");
}
void zapiszPlik(wielokat* figura, czas* pomiar, FILE* dane){
	fprintf(dane,"\n------------------CZASY-----------------\n");
	fprintf(dane,"PUNKT : (%lf, %lf)\n", pomiar->p.x, pomiar->p.y);
	for(int i = 0; i < 3; i++){
		fprintf(dane,"WYNIK ALGORYTMU %d: ", (i+1));
		if(pomiar[i].start == -1){
			fprintf(dane,"BRAK\n");
		}else fprintf(dane,"%lf\n", pomiar[i].czas);
	}
	fprintf(dane,"----------------------------------------\n");
}
void dodajCzas(czas *wartosc, lista_czas **root){
	lista_czas *nowy = (lista_czas*)malloc(sizeof(lista_czas));
	for(int i = 0; i < 3; i++){
		nowy->wartosc[i].start = wartosc[i].start;
		nowy->wartosc[i].koniec = wartosc[i].koniec;
		nowy->wartosc[i].czas = wartosc[i].czas;
		nowy->wartosc[i].p.x = wartosc[i].p.x;
		nowy->wartosc[i].p.y = wartosc[i].p.y;
	}
	nowy->next = *root;
	*root = nowy;
}



