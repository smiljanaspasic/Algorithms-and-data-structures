

#include <stdio.h>
#include <stdlib.h>

typedef struct { int *niz, kap, duz, prvi, posl; } Red;

Red create(int k) {
	return (Red) { malloc(k*sizeof(int)), k, 0, 0, 0 };
}



void sort(Red *rd)
{
	int i, j;
	for (i = rd->prvi; i<rd->posl - 1; i++)
	{
		for (j = i + 1; j<rd->posl; j++)
		{
			if (rd->niz[i] > rd->niz[j]) { int t = rd->niz[i]; rd->niz[i] = rd->niz[j]; rd->niz[j] = t; }
		}//end for i
	} // end for j


	if (rd->prvi >= rd->posl)
	{

		switch ((rd->kap - 1) - (rd->prvi)){
		case 0: break;
		case 1: if (rd->niz[rd->prvi] > rd->niz[rd->kap - 1]) { int t = rd->niz[rd->prvi]; rd->niz[rd->prvi] = rd->niz[rd->kap - 1]; rd->niz[rd->kap - 1] = t; }; break;
		case 2: {
					for (i = rd->prvi; i<rd->kap - 3; i++)
					{
						for (j = i + 1; j<rd->kap - 2; j++)
						{
							if (rd->niz[i] > rd->niz[j]) { int t = rd->niz[i]; rd->niz[i] = rd->niz[j]; rd->niz[j] = t; }
						}//end for i
					} // end for j                
		}; break;
		}// end switch

		switch (rd->posl) {

		case 0: break;
		case 1: if (rd->niz[rd->prvi] > rd->niz[0]) { int t = rd->niz[rd->prvi]; rd->niz[rd->prvi] = rd->niz[0]; rd->niz[0] = t; }; break;
		case 2:
			if (rd->niz[0] > rd->niz[1]) { int t = rd->niz[0]; rd->niz[0] = rd->niz[1]; rd->niz[1] = t; }
			if (rd->niz[rd->prvi] > rd->niz[0]) { int t = rd->niz[rd->prvi]; rd->niz[rd->prvi] = rd->niz[0]; rd->niz[0] = t; }
			break;
		other:
			for (i = 0; i<rd->posl - 2; i++)
			{
				for (j = i + 1; j<rd->posl - 1; j++)
				{
					if (rd->niz[i] > rd->niz[j]) { int t = rd->niz[i]; rd->niz[i] = rd->niz[j]; rd->niz[j] = t; }
				}//end for i
			}; // end for j  
			if (rd->niz[rd->prvi] > rd->niz[0]) { int t = rd->niz[rd->prvi]; rd->niz[rd->prvi] = rd->niz[0]; rd->niz[0] = t; }
			break;
		} // end switch


	} // end if( rd->prvi>= rd->posl)

}

void insert(Red *rd, int b) {
	int i = 0;
	int j = 0;
	int pp = 0;
	if (rd->duz == rd->kap) exit(1);
	rd->niz[rd->posl++] = b;
	rd->duz++;
	if (rd->posl == rd->kap) rd->posl = 0;

}




void pisi(Red rd) {
	int i, pp;
	for (i = 0; i < rd.duz; printf("%d ", rd.niz[(rd.prvi + i++) % rd.kap]));
	//printf("\n");
	// printf("detaljan\n\n");
	//    printf ("prvi,poslednji %d %d \n\n",rd.prvi,rd.posl);   
	//   for (pp=0;pp<rd.kap;pp++)
	//   printf ("a[%d]=%d\n",pp,rd.niz[pp]);

}
int uzmi(Red *rd) {
	if (rd->duz == 0) exit(2);
	int b = rd->niz[rd->prvi++]; rd->duz--;
	if (rd->prvi == rd->kap) rd->prvi = 0;
	return b;
}

int pocel(Red *rd) {
	if (rd->duz == 0) exit(3);
	int b = rd->niz[rd->prvi];
	return b;
}


int kapacitet(Red *rd) {
	int b = rd->kap;
	return b;
}

int zauzeto(Red *rd) {
	int b = rd->duz;
	return b;
}


_Bool pun(Red rd) { return rd.duz == rd.kap; }
_Bool prazan(Red rd) { return rd.duz == 0; }
void unisti(Red *rd) { rd->duz = rd->posl = rd->prvi = 0; free(rd->niz); }


int main() {
	Red rd = create(10);
	int izbor;
	_Bool kraj = 0;

	while (!kraj) {
		printf("\n 1.Stvaranje reda\n"
			"   2.Stavljanje podatka u red\n"
			"   3.Brisanje podatka iz reda\n"
			"   4.Dohvatanje elementa sa pocetka reda\n"
			"   5.Dohvatanje broja zauzetih mesta u redu\n"
			"   6.Dohvatanje maksimalnog kapaciteta reda\n"
			"   7.Ispisivanje reda\n"
			"   0.Zavrsetak rada\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("Kapacitet?");
			int k;
			scanf("%d", &k);
			if (k > 0) { unisti(&rd); rd = create(k); }
			else printf("Nedozvoljeni kapacitet!");
			break;
		case 2:
			if (!pun(rd))
			{
				printf("Broj?");
				int b;
				scanf("%d", &b);
				insert(&rd, b);
				sort(&rd);
			}
			else printf("Red je pun!");
			break;
		case 3:
			if (!prazan(rd)) { sort(&rd); printf("Broj=     %d\n", uzmi(&rd)); }
			else { printf("Red je prazan"); } break;
		case 4:
			if (!prazan(rd)) { printf("Broj sa pocetka je =     %d\n", pocel(&rd)); }
			else { printf("Red je prazan"); } break;

		case 5:
		{ printf("Broj zauzetih mesta  je =     %d\n", zauzeto(&rd)); }break;


		case 6:
		{ printf("Maksimalni kapacitet je =     %d\n", kapacitet(&rd)); }break;


		case 7:
			printf("RED=\n"); pisi(rd); putchar('\n'); break;
		case 0:
			kraj = 1;
			break;
		default:
			printf("Pogresan izbor!!");
		}
	}
	return 0;
}
