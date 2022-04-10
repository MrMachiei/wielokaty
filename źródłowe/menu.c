#include "../nagłówki/menu.h"
void wypiszOpcje(){
	printf("------------------MENU------------------\n");
	printf("A) Wyświetl dane wielokąta\n");
	printf("B) Wyświetl opisy algorytmów\n");
	printf("C) Wczytaj dane wielokąta\n");
	printf("D) Skoryguj dane wielokąta\n");
	printf("E) Wyświetl czasy wykonania\n");
	printf("F) Wczytaj dane z pliku\n");
	printf("G) Dokonaj pomiaru\n");
	printf("H) Wyczyść konsolę i wyświetl menu\n");
	printf("I) Zmień dane wejściowe\n");
	printf("L) Zapisz dane do pliku\n");
	printf("M) Zakończ program\n");
	printf("----------------------------------------\n");
}
//----------------------------------------
void wypiszDaneWielokat(wielokat *figura){
	printf("\n-------------DANE WIELOKĄTA-------------\n");
	if (figura == NULL){
		printf("Nie podano jeszcze danych!\n");
		printf("----------------------------------------\n");
		return;
	}else{
		int ile = figura->ileBokow;
		for(int i = 0; i < ile; i++){
			printf("WIERZCHOŁEK %d: (%f, %f)\n", i+1, (figura->wierzcholki)[i].x,(figura->wierzcholki)[i].y);
		}
	}
	if(figura->wypukly) printf("\n                  Wielokąt jest wypukły.\n");
	else printf("\n              Wielokąt nie jest wypukły.\n");
	printf("----------------------------------------\n");
}
//----------------------------------------
void wypiszOpisy(){
	printf("\n------------OPISY ALGORYTMÓW------------\n");
	printf("ALGORYTM 1:\nAlgorytm ten sprawdza dla danego punktu\njego położenie względem każdego boku wie-\nlokąta. Jeśli położenie dla wszystkich\npar jest identyczne - punkt nalezy do\nwielkoąta.\n");
	//printf("****************************************\n");
	printf("\nALGORYTM 2:\nAlgorytm ten dzieli wielokąt na kolejne\ntrójkąty i sprawdza, czy punkt leży wew-\nnątrz któregoś z nich.\n");
	//printf("****************************************\n");
	printf("\nALGORYTM 3:\nAlgorytm ten wykorzystuje matematyczną\nzależność: jeśli z punktu poprowadzimy\npólproste,to jeśli ilość ich przecięć\nz bokami jest nieparzysta - punkt leży\nwewnątrz wielokąta. W przypadku\nwielokąta wypukłego wystarczy sprawdzić\njedną półprostą poziomą.\n");
	printf("\nAlgorytmy używają metody wyznacznika\nw celu sprawdzenia położenia\npunktu względem prostej.\n");
	printf("----------------------------------------\n");
}
//----------------------------------------
wielokat * wczytaj(wielokat *figura){
	printf("\n--------------WCZYTYWANIE---------------\n");
	if (figura != NULL){
		printf("Dane już zostały wczytane!\n");
		printf("----------------------------------------\n");
	}else{
		int ileB;
		wczytajIloscBokow(&ileB);
		figura = wczytajWielokat(ileB);
		printf("----------------------------------------\n");
	}
	return figura;
}
//----------------------------------------
void poprawDane(wielokat* figura){
	printf("\n--------------KORYGOWANIE---------------\n");
	if (figura == NULL){
		printf("Nie podano jeszcze danych!\n");
		printf("----------------------------------------\n");
		return;
	}
	int ktory;
	char wybor;
	bool kont = true;
	while(kont){
		while(1){
			printf("Który wierzchołek chcesz poprawić: ");
			if(!scanf("%d", &ktory) || ktory < 0 || ktory > figura->ileBokow){
				fflush(stdin);
				printf("Błędny numer!\n\n");
			}else break;
		}
		fflush(stdin);
		wczytajPunkt(figura->wierzcholki + ktory-1);
		while(true){
			printf("Czy chcesz poprawić inne wierzchołki? (Y/N): ");
			scanf("%c", &wybor);
			fflush(stdin);
			wybor &= 0x5F;
			if (wybor == 'N'){kont = false; break;}
			if (wybor == 'Y'){printf("\n"); break;}
			else printf("Błędna opcja!\n\n");
		}
	}
	figura->wypukly = czyWypukly(figura);
	if (!figura->wypukly) printf("\nUWAGA! Wprowadzone zmiany sprawiły, że wielkoąt nie jest wypukły.\n");
	printf("----------------------------------------\n");
}
//----------------------------------------
void wypiszCzasy(czas* pomiar){
	printf("\n------------------CZASY-----------------\n");
	printf("PUNKT : (%lf, %lf)\n", pomiar->p.x, pomiar->p.y);
	for(int i = 0; i < 3;i ++){
		printf("WYNIK ALGORYTMU %d: ", i+1);
		if(pomiar[i].start == -1){
			printf("BRAK\n");
		}else printf("%lf\n", pomiar[i].czas);
	}
	printf("----------------------------------------\n");
}
//----------------------------------------
wielokat* pobierzPlik(wielokat* figura,char *plik){
	printf("\n------------------PLIKI-----------------\n");
	if (figura != NULL){
		printf("Dane już zostały wczytane!\n");
		printf("----------------------------------------\n");
		return figura;
	}
	char nazwa[50];
	printf("Podaj nazwę pliku: ");
	scanf("%s", nazwa);
	fflush(stdin);
	FILE* dane;
	int ile = 150;
	char *sciezka = (char*)malloc(sizeof(char)*ile);
	int i = 0;
	for(i; plik[i] != '\0'; i++){
		sciezka[i] = plik[i];
	}
	char wyn[] = "program/";
	for(int k = 0; k < 8; k++,i++) sciezka[i] = wyn[k];
	int j = 0;
	for(i,j = 0; j < sizeof(nazwa)/sizeof(char) ; i++,j++){
		sciezka[i] = nazwa[j];
	}
	dane = fopen(sciezka, "r");
	if(!dane){
		printf("Plik nie istnieje!\n");
	}
	else{
		figura = wczytajWielokatPlik(figura, dane);
		fclose(dane);
	}
	printf("----------------------------------------\n");
	free(sciezka);
	return figura;
}
//----------------------------------------
void dokonajPomiaru(wielokat *figura, czas *pomiar){
	printf("\n----------------POMIARY-----------------\n");
	if(figura==NULL){
		printf("Pomiar niemożliwy, figura nie istnieje.\n");
		printf("----------------------------------------\n");
		return;
	}
	if(!figura->wypukly){
		printf("Pomiar niemożliwy, figura nie jest wypukła.\n");
		printf("----------------------------------------\n");
		return;
	}
	char wybor;
	bool kon = true;
	punkt *p = (punkt*)malloc(sizeof(punkt));
	wczytajPunkt(p);
	pomiar->p.x = p->x;
	pomiar->p.y = p->y;
	while(kon){
		printf("\nWybierz algorytm (1-3, inna opcja kończy pomiar): ");
		scanf("%c", &wybor);
		fflush(stdin);
		switch(wybor){
			case '1':{
				printf("Wykonuję...\n");
				testuj(figura, czyNalezy1, pomiar, p);
				printf("Zakończono!\nTrwało to: %lf.\n", pomiar[0].czas);
				pomiar->p.x = p->x;
				pomiar->p.y = p->y;
				break;
			}
			case '2':{
				printf("Wykonuję...\n");
				testuj(figura, czyNalezy2, pomiar+1, p);
				printf("Zakończono!\nTrwało to: %lf.\n", pomiar[1].czas);
				(pomiar+1)->p.x = p->x;
				(pomiar+1)->p.y = p->y;
				break;
			}
			case '3':{
				printf("Wykonuję...\n");
				testuj(figura, czyNalezy3, pomiar+2, p);
				printf("Zakończono!\nTrwało to: %lf.\n", pomiar[2].czas);
				(pomiar+2)->p.x = p->x;
				(pomiar+2)->p.y = p->y;
				break;
			}
			default:{
				kon = false;
				break;
			}
		}
	}
	free(p);
	printf("----------------------------------------\n");
}
//----------------------------------------
void zapiszDoPliku(wielokat* figura, lista_czas* lista,char *plik){
	printf("\n------------------PLIKI-----------------\n");
	if (figura == NULL){
		printf("Nie podano jeszcze danych!\n");
		printf("----------------------------------------\n");
		return;
	}
	if (lista->next == NULL  && lista->wartosc[0].czas == 0 && lista->wartosc[1].czas == 0 && lista->wartosc[2].czas == 0){
		printf("Nie dokonano pomiaru!\n");
		printf("----------------------------------------\n");
		return;
	}
	char nazwa[50];
	printf("Podaj nazwę pliku: ");
	scanf("%s", nazwa);
	fflush(stdin);
	FILE* dane;
	int ile = 150;
	char *sciezka = (char*)malloc(sizeof(char)*ile);
	int i = 0;
	for(i; plik[i] != '\0'; i++){
		sciezka[i] = plik[i];
	}
	char wyn[] = "wyniki/";
	for(int k = 0; k < 7; k++,i++) sciezka[i] = wyn[k];
	int j = 0;
	for(i,j = 0; j < sizeof(nazwa)/sizeof(char) ; i++,j++){
		sciezka[i] = nazwa[j];
	}
	dane = fopen(sciezka, "a+");
	zapiszPlikWiel(figura, dane);
	lista_czas* temp;
	while(lista->next != NULL){
		temp = lista;
		lista = lista->next;
		zapiszPlik(figura,temp->wartosc,dane);
	}
	printf("----------------------------------------\n");
	free(sciezka);
}
void zmienSciezke(char *dane){
	int i = 0;
	while(dane[i] != '\0') i++;
	int j = i;
	while(dane[j] != '/') j--;
	j--;
	while(dane[j] != '/') j--;
	dane[++j] = '\0';
}
void wypiszLista(lista_czas* lista){
	printf("\n-----------------WYNIKI-----------------\n");
	if (lista->next == NULL  && lista->wartosc[0].czas == 0 && lista->wartosc[1].czas == 0 && lista->wartosc[2].czas == 0){
		printf("Nie dokonano pomiaru!\n");
		printf("----------------------------------------\n");
		return;
	}
	lista_czas* temp;
	while(lista->next != NULL){
		temp = lista;
		lista = lista->next;
		wypiszCzasy(temp->wartosc);
	}
	printf("----------------------------------------\n");
}