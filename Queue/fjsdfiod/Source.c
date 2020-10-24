#include <stdio.h>
#include <stdlib.h>

typedef struct { int *niz, kap, duz, prvi, posl; } Red;

Red create(int k) {
	return (Red) { calloc(k, sizeof(int)), k, 0, 0, 0 };
}

void insert(Red *rd, int b) {
	
	if (rd->duz == rd->kap) exit(1);
	//	if (rd->duz = 0) { rd->niz[rd->prvi++] = b; }
	rd->niz[rd->posl++] = b;
	rd->duz++;
	if (rd->posl == rd->kap) rd->posl = 0;
	int i = 0;
	int j = 0;
	printf("prvi,poslednji %d %d %d %d", rd->prvi, rd->posl, rd->niz[rd->prvi], rd->niz[rd->posl]);

	for (i = rd->prvi; i<rd->posl - 2; i++)
	for (j = rd->prvi + 1; j<rd->posl - 1; j++)
	{
		printf("CODE WAS HERE ALSO");
		printf("i,j  %d %d\n", i, j);
		printf("%d %d\n", rd->niz[i], rd->niz[j]);
		if (rd->niz[i] > rd->niz[j]) { int t = rd->niz[i]; rd->niz[i] = rd->niz[j]; rd->niz[j] = t; }

	}


}

void pisi(Red rd) {
	int i;
	for (i = 0; i < rd.duz; printf("%d ", rd.niz[(rd.prvi + i++) % rd.kap]));
}
int uzmi(Red *rd) {
	if (rd->duz == 0) exit(2);
	int b = rd->niz[rd->prvi++]; rd->duz--;
	if (rd->prvi == rd->kap) rd->prvi = 0;
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
			if (k > 0) { unisti(&rd); Red rd = create(k); }
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
			if (!prazan(rd)) { printf("Broj=     %d\n", uzmi(&rd)); }
			else { printf("Red je prazan"); } break;

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