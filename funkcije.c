#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "datatype.h"
//#include "header.h"


int brPog = 0; 		//brojac koji provjerava broj pogodenih parova
int brPot = 0;		//brojac poteza u koliko je igra zavrsena
int brIgr = 0;		//broj odigranih igara

void ispisMemory()																//ispis naslova
{
	system("cls");
	printf("\t  __  __ ______ __  __  ____  _______     __\n");
	printf("\t |  \\/  |  ____|  \\/  |/ __ \\|  __ \\ \\   / /\n");
	printf("\t | \\  / | |__  | \\  / | |  | | |__) \\ \\_/ / \n");
	printf("\t | |\\/| |  __| | |\\/| | |  | |  _  / \\   /  \n");
	printf("\t | |  | | |____| |  | | |__| | | \\ \\  | |   \n");
	printf("\t |_|  |_|______|_|  |_|\\____/|_|  \\_\\ |_|   ");

}

void pravila()																	//ispis pravila (case 1)
{
	system("cls");
	ispisMemory();
	printf("\n******************************************************************\n");
	printf("Cilj igre je pronaci parove znakova u sto\n\
manjem vremenu.\
\nDa bi zapoceli novu igru u glavnom izborniku\n\
odaberite opciju 2 te izaberite velicinu igraceg polja.\n\
Kada pokrenete novu igru pred vama ce biti ispisano popunjeno\n\
igrace polje koje ce zamjeniti skriveno polje popunjeno znakom '@'.\n\
\nZeljene koordinate upisujte u formatu RedStupac\n\
(npr. a2), te nakon svake unesene koordinate potvrdite\n\
odabir tipkom Enter. Nakon unesene obje zeljene koordinate,\n\
biti ce prikazani znakovi koji se nalaze na odabranim poljima.\n\
Ako su znakovi jednaki ostati ce prikazani dalje u igri.\n\
Ako znakovi nisu jednaki biti ce prikazani 2 sekunde nakon\n\
cega ce se na njihovo mjesto vratiti znak '@'\n\
\nZa povratak u glavni izbornik pritisnite bilo koju tipku.\n\
\n\nOva igra je nastala kao zavrsni rad za kolegij Programiranje 2\n\
studenta prve godine strucog studija racunarstva na Fakultetu\n\
elektrotehnike, racunarstva i informacijskih znanosti u Osijeku\n\
Josipa Dakovca JMBAG: 0302022777\n");
	printf("******************************************************************\n");
			
	getch();
	system("cls");
}
///////////////////////////////////////////////////////////////////
char rndZnak(char *pokZn)														//generiranje znaka za popunjavanje
{
	char a;	
	do
	{
		a = (char)rand();		
	}while (((a >= 0 && a <= 32) || a == 127) || a == '@');
	
	return a;
}
///////////////////////////////////////////////////////////////////
char** zauzimanje(char **pokP, int m)											//zauzimanje memorije za polje znakova
{
	int i, j;
	int n = sqrt(m);
	pokP = NULL;
	pokP = (char**)calloc((m), sizeof(char*));	
	if(pokP == NULL)
	{
		return NULL;
	}		
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			*(pokP + i) = (char*)calloc(n, sizeof(char));
			
			if(*(pokP + i) == NULL)
			{
				return NULL;
			}
		}
	}
	return pokP;
}
///////////////////////////////////////////////////////////////////
char* zauzimanjeZn(char *pokZn, int m)			//zauzimanje memorije za polje m znakova
{
	pokZn = (char*)calloc((m), sizeof(char));	
	return pokZn;
}
///////////////////////////////////////////////////////////////////
char* popunjavanjeZn(char *pokZn, int  m)		//popunjavanje polja m znakova
{
	int i, j;
	for(i = 0; i < m; i++)
	{
		*(pokZn + i) = rndZnak(pokZn);
		for(j = 0; j < i; j++)
		{
			if(*(pokZn + i) == *(pokZn + j))
			{
				*(pokZn + i) = rndZnak(
				pokZn);
			}
		}
	}
	return pokZn;
}
///////////////////////////////////////////////////////////////////
char* mjesanje(char *pokZn, int n)				//mjesanje polja znakova
{
	srand(time (NULL));
	int i, j;
	if(n > 0)
	{
		for(i = n - 1; i > 0; i--)
		{
			j = rand() % (i + 1);
			char t = *(pokZn + j);
			*(pokZn + j) = *(pokZn + i);
			*(pokZn + i) = t;
		}
	}
	return pokZn;
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
char** popunjavanjeSkrivene(char **pokPog, int m)								//POPUNJAVANJE SKRIVENE MATRICE
{	
	int i, j;
	m = sqrt(m);
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < m; j++)
		{
			*(*(pokPog + i)+ j) = '@';
		}
	}
	return pokPog;
}
///////////////////////////////////////////////////////////////////
char** popunjavanje(char *pokZn, char **pokPop, int m)							//POPUNJAVANJE 2D MATRICE
{
	char a;
	int i, j;
	int k = 0;
	m = sqrt(m);
	for(i = 0; i < m; i += 2)
	{
		for(j = 0; j < m; j += 2)
		{														//popunjavanje i parnih i j parnih
			a = *(pokZn + k);
			*(*(pokPop + i) + j) = a;
			k++;
		}
	}
	for(i = 1; i < m; i += 2)
	{
		for(j = 1; j < m; j += 2)
		{														//popunjavanje i neparnih i j nepranih
			a = *(pokZn + k);
			*(*(pokPop + i) + j) = a;
			k++;
		}
	}
	if(m == 6)
	{
		pokZn = mjesanje(pokZn, 18);
	}
	else 
	{
		pokZn = mjesanje(pokZn, 8);
	}
	k = 0;
	for(i = 0; i < m; i += 2)
	{															//popunjavanje i parnih i j neparnih
		for(j = 1; j < m; j += 2)
		{
			a = *(pokZn + k);
			*(*(pokPop + i) + j) = a;
			k++;
		}
	}
	for(i = 1; i < m; i += 2)
	{															//popunjavanje i neparnih i j parnih
		for(j = 0; j < m; j += 2)
		{
			a = *(pokZn + k);
			*(*(pokPop + i) + j) = a;
			k++;
		}
	}
	return pokPop;
}
///////////////////////////////////////////////////////////////////
void ispis(char **pokMat, int m)				//ispis igrace ploce
{
	int i, j;
	printf("\n");
	for(i = 0; i < m + 1; i++)
	{
		printf("\t\t");
		for(j = 0; j < m + 1; j++)
		{
			if(i == 0)
			{
				printf(" %1d |", j);
			}
			if(j == 0 && i > 0)
			{
				printf(" %1c |", 'a' + i - 1);
			}
			if(i > 0)
			{
				if(j > 0)
				{
					printf(" %1c |", *(*(pokMat + i - 1) + j - 1));
				}
			}
		}
		if(m == 4)
		{
			printf("\n\t\t---|---|---|---|---|\n");
		}
		else
		{
			printf("\n\t\t---|---|---|---|---|---|---|\n");	
		}
		
	}
}
///////////////////////////////////////////////////////////////////
int provjera(char **pokPop, char **pokPog, int x1, int y1, int x2, int y2, int m)	//provjera jednakosti vrijednosti
{																					//u odabranim celijama
	if(*(*(pokPog + x1) + y1) == '@' && *(*(pokPog + x2) + y2) == '@')
	{
		if(*(*(pokPop + x1) + y1) == *(*(pokPop + x2) + y2))
		{
			*(*(pokPog + x1) + y1) = *(*(pokPop + x1) + y1);	//ako su vrijednosti jednake 
			*(*(pokPog + x2) + y2) = *(*(pokPop + x2) + y2);	//ostavi ispisano
			ispis(pokPog, m);
			brPog++;
		}
		else
		{
			system("cls");
			ispisMemory();
			printf("\n\n");
			*(*(pokPog + x1) + y1) = *(*(pokPop + x1) + y1);	//ako vrijednosti nisu jednake
			*(*(pokPog + x2) + y2) = *(*(pokPop + x2) + y2);	//pokazi ih na 3 sec i ponovo ih sakrij
			ispis(pokPog, m);
			sleep(2);
			system("cls");
			*(*(pokPog + x1) + y1) = '@';
			*(*(pokPog + x2) + y2) = '@';
			ispis(pokPog, m);
		}
	
		brPot++;
		return brPot;
	}
	else
	{
		printf("\nPolje je vec otvoreno!");
	}
}
///////////////////////////////////////////////////////////////////
void unosPodataka(float vrijeme, int korak, int mod)
{
	FILE* pokF;
	
	if (mod == 4)
	{
		pokF = fopen("score_4.bin", "rb+");
	
		if(!pokF)
		{
			perror("Nemoguce otvoriti datoteku.");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pokF = fopen("score_6.bin", "rb+");
	
		if(!pokF)
		{
			perror("Nemoguce otvoriti datoteku.");
			exit(EXIT_FAILURE);
		}
	}
	
	IGRAC poljeIgraca = { 0 };
	
	printf("\n\nUnesi ime: ");
	scanf("%5s", &poljeIgraca.ime);
	fflush(stdin);
	fseek(pokF, 0, SEEK_SET);
	fread(&brIgr, sizeof(int), 1, pokF);
	poljeIgraca.id = brIgr;
	poljeIgraca.korak = korak;
	poljeIgraca.mod = mod;
	poljeIgraca.vrijeme = vrijeme;
	
	fseek(pokF, sizeof(IGRAC) * brIgr, SEEK_CUR);
	fwrite(&poljeIgraca, sizeof(IGRAC), 1, pokF);
	rewind(pokF);
	brIgr++;
	fwrite(&brIgr, sizeof(int), 1, pokF);
	fclose(pokF);
}
///////////////////////////////////////////////////////////////////
void* citanjeIgraca(int m)
{
	FILE* pokF;
	if(m == 4)
	{
		pokF = fopen("score_4.bin", "rb");
	
		if(!pokF)
		{
			perror("otvaranje datoteke");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pokF = fopen("score_6.bin", "rb");
	
		if(!pokF)
		{
			perror("otvaranje datoteke");
			exit(EXIT_FAILURE);
		}
	}
	
	rewind(pokF);
	fread(&brIgr, sizeof(int), 1, pokF);
	
	system("cls");
	ispisMemory();
	printf("\n\n******************************************************************\n");
	printf("\nBroj odigranih igara je %d", brIgr);
	IGRAC* poljeIgraca = (IGRAC*)calloc(brIgr, sizeof(IGRAC));
	
	if(!poljeIgraca)
	{
		perror("zauzimanje polja igraca");
		exit(EXIT_FAILURE);
	}
	
	fread(poljeIgraca, sizeof(IGRAC), brIgr, pokF);
	return poljeIgraca;
}
///////////////////////////////////////////////////////////////////
void ispisSvih(const IGRAC* const poljeIgraca)
{
	if(!poljeIgraca)
	{
		printf("Polje igraca je prazno.");
		return;
	}
	int i;
	
	for(i = 0; i < brIgr; i++)
	{
		printf("\n\nID: %d\nIme: %s\nBroj koraka: %d\nVrijeme: %.3f\nMod: %dx%d",
				(poljeIgraca + i)->id, 
				(poljeIgraca + i)->ime, 
				(poljeIgraca + i)->korak, 
				(poljeIgraca + i)->vrijeme, 
				(poljeIgraca + i)->mod, 
				(poljeIgraca + i)->mod);
	}
	getch();
}

void sortVrijeme(IGRAC* const poljeIgraca, IGRAC* const poljeTopTri, int brIgr)
{
	int i, j;
	IGRAC *temp = (IGRAC*)calloc(1, sizeof(IGRAC));		

	for(i = 0; i < brIgr - 1; i++)
	{
		for(j = 0; j < brIgr - 1 - i; j++)
		{
			if(((poljeIgraca + j + 1)->vrijeme) < (poljeIgraca + j)->vrijeme)
			{
				*temp = *(poljeIgraca + j + 1);
				*(poljeIgraca + j + 1) = *(poljeIgraca + j);
				*(poljeIgraca + j) = *temp;
			}
		}
	}	
	
	for(i = 0; i < 3; i++)
	{
		*(poljeTopTri + i) = *(poljeIgraca + i);
	}
	free(temp);
}

void sortKoraci(IGRAC* const poljeIgraca, IGRAC* const poljeTopTri, int brIgr)
{
	int i, j;
	IGRAC *temp = (IGRAC*)calloc(1, sizeof(IGRAC));		

	for(i = 0; i < brIgr - 1; i++)
	{
		for(j = 0; j < brIgr - 1 - i; j++)
		{
			if(((poljeIgraca + j + 1)->korak) < (poljeIgraca + j)->korak)
			{
				*temp = *(poljeIgraca + j + 1);
				*(poljeIgraca + j + 1) = *(poljeIgraca + j);
				*(poljeIgraca + j) = *temp;
			}
		}
	}	
	
	for(i = 0; i < 3; i++)
	{
		*(poljeTopTri + i) = *(poljeIgraca + i);
	}
	free(temp);
}
///////////////////////////////////////////////////////////////////
void TopTri(int m, char mod)
{
	int i;
	FILE* pokF;
	if(m == 4)
	{
		pokF = fopen("score_4.bin", "rb");
	
		if(!pokF)
		{
			perror("otvaranje datoteke");
			exit(EXIT_FAILURE);
		}	
	}
	else
	{
		pokF = fopen("score_6.bin", "rb");
	
		if(!pokF)
		{
			perror("otvaranje datoteke");
			exit(EXIT_FAILURE);
		}
	}
	
	rewind(pokF);
	fread(&brIgr, sizeof(int), 1, pokF);
	
	IGRAC* poljeIgraca = (IGRAC*)calloc(brIgr, sizeof(IGRAC));
	if(poljeIgraca == NULL)
	{
		perror("zauzimanje memorije za poljeIgraca");
		exit(EXIT_FAILURE);
	}
	IGRAC* poljeTopTri = (IGRAC*)calloc(3, sizeof(IGRAC));
	if(poljeTopTri == NULL)
	{
		perror("zauzimanje memorije za poljeTopTri");
		exit(EXIT_FAILURE);
	}
	
	fread(poljeIgraca, sizeof(IGRAC), brIgr, pokF);
	if(mod == 'v')
	{
		sortVrijeme(poljeIgraca, poljeTopTri, brIgr);	
	}
	else
	{
		sortKoraci(poljeIgraca, poljeTopTri, brIgr);
	}
	
	system("cls");
	ispisMemory();
	printf("\n\n******************************************************************\n");
	printf("\nTop tri\n");
	for(i = 0; i < 3; i++)
	{
		printf("\n%d.\nID: %d\nIme: %s\nBroj poteza: %d\nVrijeme: %.3f sekundi\nMod igre: %d x %d\n", 
		i + 1, 
		(poljeTopTri + i)->id, 
		(poljeTopTri + i)->ime, 
		(poljeTopTri + i)->korak, 
		(poljeTopTri + i)->vrijeme, 
		(poljeTopTri + i)->mod, 
		(poljeTopTri + i)->mod);
	}
	printf("\nZa povratak u glavni izbornik pritisnite bilo koju tipku.");
	getch();
	free(poljeTopTri);
	free(poljeIgraca);
}


///////////////////////////////////////////////////////////////////
int novaIgra(char** pokPog, char**pokPop, int m)			//nova igra
{															
	char a = NULL, b = NULL;
	int x1 = NULL, y1 = NULL, x2 = NULL, y2 = NULL;
	system("cls");
	ispisMemory();		//ispis naslova
	printf("\n\n");
	ispis(pokPop, m);		//ispis popunjene ploce
	sleep(5);
	system("cls");
	float start, stop, total;
	start = clock();
	do							//provjera jednakosti koordinata se dok nisu svi parovi nadeni
	{
		ispisMemory();
		printf("\n\n");
		ispis(pokPog, m);
		fflush(stdin);
	
		printf("\n\nUnesi prvu koordinatu: ");
		scanf("%c%d%[^\n]", &a, &y1);
		fflush(stdin);
	
		if(a >= 'A' && a <= 'Z')	//pretvorba iz veikih u mala slova
		{
			a += 32;
		}
	
		x1 = a - 97;				//pretvorba koordinata
		y1 = y1 - 1;
	
		if(x1 > m || y1 > m || y1 < 0)		//provjera postoji li unesena koordinata
		{							//tj. ako se upise red ili stupac koji ne postoji 
			printf("\nUnesena koordinata ne postoji");
			sleep(1);
			continue;
		}
	
		printf("\nUnesi drugu koordinatu: ");
		scanf("%c%d%[^\n]", &b, &y2);			
		fflush(stdin);
	
		if(b >= 'A' && b <= 'Z')	//pretvorba iz veikih u mala slova
		{
			b += 32;
		}
	
		x2 = b - 97;
		y2 = y2 - 1;
	//	printf("\n1. koordinatta: %d %d\n2. koordinata: %d %d", x1, y1, x2, y2);
	//	sleep(5);
		if(x2 > m || y2 > m || y2 < 0)
		{
			printf("\nUnesena koordinata ne postoji");
			sleep(1);
			continue;
		}
		if(x1 == x2 && y1 == y2)
		{
			printf("\nUnjeli ste iste koordinate.");
			sleep(1);
			continue;
		}
		brPot = provjera(pokPop, pokPog, x1, y1, x2, y2, m);
		system("cls");
	}while(brPog < ((m * m) / 2));
	stop = clock();	
	total = (stop - start) / CLOCKS_PER_SEC;
	brPog = 0;
	ispisMemory();
	printf("\n******************************************************************\n");
	ispis(pokPop, m);
	printf("\nCestitam zavrsili ste igru u %d koraka, i za %.2f sekundi!", brPot, total);
	getch();
	unosPodataka(total, brPot, m);
	printf("\nPritisnite bilo koju tipku za povratak u glavni izbornik.");
	brPot = 0;
	getch();
}

int izlaz(char* pokZn, char** pokPop, char** pokPog)
{
	char izlaz[3] = "ne";
	char odabir[3];
	
	printf("\nJeste li sigurni da zelite izaci? [da/ne]\n");
	scanf("%2s", odabir);
	if(strcmp(izlaz, odabir) == 0)
	{
		free(pokZn);
		free(pokPop);
		free(pokPog);
		return 0;
	}else
	{
		return 1;
	}
}

int izbornik()							//IZBORNIK
{
	int i, j, mod2;
	int uvijet = 0;
	int mod = 0;
	
	char znakovi[18];
	char* pokZn = NULL;
	
	char plocaPopunjeno[6][6];													//ploca koja ce sluzit za usporedbu jednakosti znakova
	char **pokPop = NULL;

	char plocaPogodeno[6][6];													//ploca koja ce biti ispisana	
	char **pokPog = NULL;
	
	static IGRAC* poljeIgraca = NULL;
	static IGRAC* poljePronadenih = NULL;

	FILE* pokF = fopen("score_4.bin", "ab+");
	fread(&brIgr, sizeof(int), 1, pokF);
	if(brIgr == '\0')
	{
		fwrite(&brIgr, sizeof(int), 1, pokF);
	}
	fclose(pokF);

	pokF = fopen("score_6.bin", "ab+");
	fread(&brIgr, sizeof(int), 1, pokF);
	if(brIgr == '\0')
	{
		fwrite(&brIgr, sizeof(int), 1, pokF);
	}
	fclose(pokF);
	
	while(1)
	{
		ispisMemory();
		printf("\n\n******************************************************************\n");
		printf("\tOdaberi jednu od ponudenih opcija:\n");
		printf("******************************************************************\n");
		printf("\n\t1. Pravila i upute\n");
		printf("\n\t2. Nova igra\n");
		printf("\n\t3. Top 3\n");
		printf("\n\t4. Ispis svih odigranih igara\n");
		printf("\n\t5. Izlaz iz igre\n\n");
		printf("******************************************************************\n");
		printf("\t\nOdabir: ");
		scanf("%d", &uvijet);
		switch (uvijet)
		{
			case 1:
				pravila();
			break;
	
			case 2:
				system("cls");
				ispisMemory();
				printf("\n\n******************************************************************\n");
				printf("\tOdaberi mod igre:\n\
******************************************************************\n\
\n\t1. Ploca 4x4\n\
\n\t2. Ploca 6x6\n\
\n\t3. Povratak u glavni izbornik\n\n\
******************************************************************\n\
\nMod: ");
				scanf("%d", &mod);
				switch (mod) 
				{
					case 1:
						pokZn = zauzimanjeZn(pokZn, 8);
						
						for(i = 0; i < 8; i++)
						{
							*(pokZn + i) = rndZnak(pokZn);
							for(j = 0; j < i; j++)
							{
								if(*(pokZn + i) == *(pokZn + j))
								{
									*(pokZn + i) = rndZnak(pokZn);
								}
							}
						}
						pokPop = zauzimanje(pokPop, 16);
						if(pokPop == NULL)
						{
							return 1;
						}
						pokPop = popunjavanje(pokZn, pokPop, 16);
						pokPog = zauzimanje(pokPog, 16);
						if(pokPog == NULL)
						{
							return 1;
						}
						pokPog = popunjavanjeSkrivene(pokPog, 16);
						novaIgra(pokPog, pokPop, 4);
						
						free(pokPog);
						free(pokPop);
						free(pokZn);
					break;
					
					case 2:
						pokZn = zauzimanjeZn(pokZn, 18);
						
						for(i = 0; i < 18; i++)
						{
							*(pokZn + i) = rndZnak(pokZn);
							for(j = 0; j < i; j++)
							{
								if(*(pokZn + i) == *(pokZn + j))
								{
									*(pokZn + i) = rndZnak(pokZn);
								}
							}
						}
						pokPop = zauzimanje(pokPop, 36);
						if(pokPop == NULL)
						{
							return 1;
						}
						pokPop = popunjavanje(pokZn, pokPop, 36);
						pokPog = zauzimanje(pokPog, 36);
						if(pokPog == NULL)
						{
							return 1;
						}
						pokPog = popunjavanjeSkrivene(pokPog, 36);
						novaIgra(pokPog, pokPop, 6);
						
						free(pokPog);
						free(pokPop);
						free(pokZn);
					break;
					
					case 3:
					break;
				}
				
			break;
			
			case 3:
			system("cls");
				int mod1;
				ispisMemory();
				printf("\n\n******************************************************************\n");
				printf("\tOdaberi mod prikaza rezltata:\n\
******************************************************************\n\
\n\t1. Top 3 4x4 po vremenu\n\
\n\t2. Top 3 6x6 po vremenu\n\
\n\t3. Top 3 4x4 po broju poteza\n\
\n\t4. Top 3 6x6 po broju poteza\n\
\n\t5. Povratak u glavni izbornik\n\n\
******************************************************************\n\
\nMod: ");
				scanf("%d", &mod1);
				
				switch(mod1)
				{
					case 1:
					TopTri(4, 'v');
					break;
					
					case 2:
					TopTri(6, 'v');
					break;
				
					case 3:
					TopTri(4, 'k');
					break;
					
					case 4:
					TopTri(6, 'k');
					break;
					
					default:
					break;	
				}
				break;
			
			case 4:
				
				system("cls");
				ispisMemory();
				printf("\n\n******************************************************************\n");
				printf("\tOdaberi mod igre za koji zelis pokazati reultate:\n\
******************************************************************\n\
\n\t1. Svi 4x4\n\
\n\t2. Svi 6x6\n\
\n\t3. Povratak u glavni izbornik\n\n\
******************************************************************\n\
\nMod: ");
				scanf("%d", &mod2);
				switch(mod2)
				{
					case 1:	
						poljeIgraca = (IGRAC*)citanjeIgraca(4);
						if(!poljeIgraca)
						{
							perror("Ucitavanje u polje igraca");
							exit(EXIT_FAILURE);
						}
						ispisSvih(poljeIgraca);
						free(poljeIgraca);
					break;
				
					case 2:
						poljeIgraca = (IGRAC*)citanjeIgraca(6);
						if(!poljeIgraca)
						{
							perror("Ucitavanje u polje igraca");
							exit(EXIT_FAILURE);
						}
						ispisSvih(poljeIgraca);
						free(poljeIgraca);
					break;
				
					default:
					continue;
				}
				
				break;
			
			case 5:
			system("cls");
			ispisMemory();
			printf("\n\n******************************************************************\n");
			printf("\n");
			uvijet = izlaz(pokZn, pokPop, pokPog);
			return uvijet;
			break;
		}
	}
	return uvijet;
}
