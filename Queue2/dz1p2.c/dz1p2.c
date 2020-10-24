#include <stdio.h>
#include <stdlib.h>

typedef struct { int *niz, kap, duz, prvi, posl; } Red;

Red create(int k) {
	return (Red) { malloc(k*sizeof(int)), k, 0, 0, 0 };
}

void brisi(Red* rd, int y) {
	if (rd->niz[y] - rd->niz[rd->prvi] < rd->niz[rd->posl] - rd->niz[y])
	{
		while (y != rd->prvi) {
			rd->niz[y] = rd->niz[y - 1];
			y = y - 1;
		}
		rd->prvi = rd->prvi + 1;
	}
	else {
		while (y != rd->posl)
		{
			rd->niz[y] = rd->niz[y + 1];
			y = y + 1;
		} rd->posl = rd->posl - 1;
	}
	rd->duz = rd->duz--;
}


void insert(Red *rd, int b) {

	if (rd->duz == rd->kap) exit(1);
	if (rd->duz != 0) { rd->posl++; }
	rd->niz[rd->posl] = b;
	rd->duz++;


}




void pisi(Red* rd) {
	int i;
	for (i = rd->prvi; i < rd->posl + 1; i++) { printf("%d  ", rd->niz[i]); };
	printf("\n");
	printf("Maksimalna duzina reda je %d", rd->kap);
	printf("\n");
	printf("Trenutna duzina reda je %d", rd->duz);
	printf("\n");
	printf("Prvi element je: %d ", rd->niz[rd->prvi]);
	printf("\n");
	printf("Poslednji element je: %d ", rd->niz[rd->posl]);

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
int findminpos(Red* rd) {
	int p = rd->prvi;
	for (int i = rd->prvi; i < rd->posl + 1; i++) {
		if (rd->niz[i] < rd->niz[p]) { p = i; }


	}
	return p;
}


_Bool pun(Red rd) { return rd.duz == rd.kap; }
_Bool prazan(Red rd) { return rd.duz == 0; }
void unisti(Red *rd) { rd->duz = rd->posl = rd->prvi = 0; free(rd->niz); }


int main() {
	Red rd = create(10);
	int izbor;
	_Bool kraj = 0;

	while (!kraj) {
		printf("\n "
			"    1.Stvaranje reda\n"
			"     2.Stavljanje podatka u red\n"
			"     3.Brisanje podatka iz reda\n"
			"     4.Dohvatanje elementa sa pocetka reda\n"
			"     5.Dohvatanje broja zauzetih mesta u redu\n"
			"     6.Dohvatanje maksimalnog kapaciteta reda\n"
			"     7.Ispisivanje reda\n"
			"     0.Zavrsetak rada\n");
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

			}
			else printf("Red je pun!");
			break;
		case 3:
			if (!prazan(rd)) { int x; x = findminpos(&rd); brisi(&rd, x); }
			else { printf("Red je prazan"); } break;
		case 4:
			if (!prazan(rd)) { printf("Broj sa pocetka je =     %d\n", pocel(&rd)); }
			else { printf("Red je prazan"); } break;

		case 5:
		{ printf("Broj zauzetih mesta  je =     %d\n", zauzeto(&rd)); }break;


		case 6:
		{ printf("Maksimalni kapacitet je =     %d\n", kapacitet(&rd)); }break;


		case 7:
			if (!prazan(rd)) { printf("RED=\n"); pisi(&rd); putchar('\n'); }
			else { printf("Red je prazan"); }
			break;
		case 0:
			kraj = 1;
			break;
		default:
			printf("Pogresan izbor!!");
		}
	}
	return 0;
}