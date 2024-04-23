#ifndef HEADE_H
#define HEADER_H

#include "datatype.h"

int izbornik();	              						    //glavni izbornik --gotovo
int novaIgra(char**, char**, int);	                    //nova igra --gotovo  
int provjera(char**, char**, int, int, int, int);		//provjera jednakostu vrijednosti u poljima --gotovo 
char* zauzimanjeZn(char*, int);							//dinamicko zauzimanje za polje znakova --gotovo
char* popunjavanjeZn(char*, int);                       //popunjavanje igraceg polja znakovima
char** zauzimanje(char**, int);							//dinamicko zauzimanje m*m memorije  --gotovo
char rndZnak(char*);									//generiranje random znaka --gotovo
char* mjesanje(char*, int);								//mjesanje polja znakova  --gotovo
char** popunjavanjeSkrivene(char**, int);				//popunjavanje polja sa znakom '@'  --gotovo
char** popunjavanje(char*, char**);						//popunjavanje polja sa znakovima  --gotovo
void ispis(char**, int);								//ispis igrace ploce  --gotovo
void unosPodataka(float, int, int);						//unos podataka nakog odigranog + upisivanje u file --gotovo
void* citanjeIgraca(int);
void ispisSvih(const IGRAC* const);						//ispis svih odigranih igara --gotovo
void TopTri(int, char);									//ispis top 3 igraca --gotovo
void pravila();											//ispis pravila	--gotovo
void ispisMemory();										//ispis naslova --gotovo
void sortVrijeme(IGRAC* const, GRAC* const, int);		//bb sort po vremenu --gotovo
void sortKoraci(IGRAC* const, GRAC* const, int);		//bb sort po koracima --gotovo
int izlaz(char*, char**, char**);						//izlaz iz programa --gotovo

#endif
