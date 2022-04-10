#include "../nagłówki/menu.h"
// main
int main(int argc, char * argv[]){
	char *sciezka = argv[0];
	zmienSciezke(sciezka);
	int ileB;
	wielokat *figura = NULL;
	lista_czas *root = (lista_czas*)malloc(sizeof(lista_czas));
	root->next = NULL;
	czas *pomiary = NULL;
	char opcja;
	pomiary = zainicjujCzasy();
	while(true){
		wypiszOpcje();
		printf("Wybór: ");
		scanf("%c", &opcja);
		fflush(stdin);
		switch(opcja & 0x5F){
			case 'A':{
				wypiszDaneWielokat(figura);
				break;
			}
			case 'B':{
				wypiszOpisy();
				break;
			}
			case 'C':{
				figura = wczytaj(figura);
				break;
			}
			case 'D':{
				poprawDane(figura);
				break;
			}
			case 'E':{
				wypiszLista(root);
				break;
			}
			case 'F':{
				figura = pobierzPlik(figura, sciezka);
				break;
			}
			case 'G':{
				dokonajPomiaru(figura, pomiary);
				dodajCzas(pomiary, &root);
				wypiszCzasy(pomiary);
				pomiary = zainicjujCzasy();
				break;
			}
			case 'H':{
				system("clear");
				break;
			}
			case 'I':{
				if(figura == NULL) figura = (wielokat*)malloc(sizeof(figura));
				porzadek(figura,pomiary, root);
				figura = NULL;
				pomiary = zainicjujCzasy();
				figura = wczytaj(figura);
				root = (lista_czas*)malloc(sizeof(lista_czas));
				root->next = NULL;
				break;
			}
			case 'L':{
				zapiszDoPliku(figura, root, sciezka);
				break;
			}
			case 'M':{
				if(figura == NULL) figura = (wielokat*)malloc(sizeof(figura));
				porzadek(figura,pomiary, root);
				return 0;
			}
			default :{
				printf("BŁĘDNA OPCJA!\n\n");
				break;
			}
		}
	}
}