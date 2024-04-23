#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "header.h"



int main()
{
	srand((unsigned) time (NULL));

	int uvijet;
	
	do
	{
		uvijet = izbornik();
	} while (!uvijet == 1);
	
	return 0;
}
