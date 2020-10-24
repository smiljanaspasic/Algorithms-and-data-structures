#include <stdio.h>
#include <stdlib.h>
#define MAX_N 20


typedef struct { int *a, MAX_VECTOR, redm, pv; } matrica;


//stvaranje matrice
matrica stvori(int n){
	return (matrica){ calloc((5 * n - 6), sizeof(int)), 5 * n - 6, n, 0 };
}


//postavljanje vrednosti zadatom elementu
void upis(matrica *M, int ii, int ij, int n, int x) {

	//printf ("upis vrednosti na mesto i,j \n");
	if (ii>M->redm || ij>M->redm)
		printf(" Greska: izvan opsega\n\n");

	else if (abs(ii - ij)>2)
		printf(" Nije dozvoljeno za petodijagonalnu matricu \n\n");

	else
	{
		int indeks = 4 * ii + ij - 6;
		if (ii == 1) indeks = indeks + 1;
		if (ii == n) indeks = indeks - 1;
		printf("indeks=%d\n", indeks);
		printf("broj=%d\n", x);
		M->a[indeks] = x;
		printf("a[%d]=%d", indeks, M->a[indeks]); //debug
	} // end else
}


//dohvatanje zadatog elementa
int citaj(matrica *M, int ii, int ij, int n) {
	printf("Ocitavanje vrednosti sa mesta %d,%d \n", ii, ij);
	if (ii>M->redm || ij>M->redm)
	{
		printf(" Greska: izvan opsega");
		return -1;
	}
	else
	{

		int indeks = 4 * ii + ij - 6;
		if (ii == 1) indeks = indeks + 1;
		if (ii == n) indeks = indeks - 1;
		int citaj = M->a[indeks];
		return citaj;
	} // end else
} //end citaj     


//zadavanje podrazumevane vrednosti 
void pod_vrednost(matrica *M, int pv){
	M->pv = pv;
}

//printanje matrice
void pisi(matrica M){
	int i = 0;
	int j = 0;

	printf("Uneli ste matricu:\n");
	for (i = 1; i<M.redm + 1; i++)
	{
		for (j = 1; j<M.redm + 1; j++)
		{
			if (abs(i - j) <= 2)
			{
				if (i == 1) printf("%5d", M.a[4 * i + j - 6 + 1]);
				else if (i == M.redm) printf("%5d", M.a[4 * i + j - 6 - 1]);
				else  printf("%5d", M.a[4 * i + j - 6]);
			}
			else
				printf("%5d", M.pv);
		}
		printf("\n");
	}
}// end pisi

int brojel(int k)
{
	int brojel = 5 * k - 6;
	return;
}

int usteda(int k)
{
	int usteda = 100 - ((5 * k - 6) * 100 / (k*k));
	return usteda;
}



void unisti(matrica *M) { free(M->a); }


int main(){
	matrica M = stvori(10);
	_Bool kraj = 0;
	while (!kraj) {
		printf("\n1.  Stvaranje matrice\n"
			"2.  Unos podrazumevane vrednosti\n"
			"3.  Dohvatanje zadatog elementa\n"
			"4.  Postavljanje vrednosti zadatog elementa\n"
			"5.  Ispis matrice\n"
			"6.  Dohvatanje broja nepodrazumevanih elemenata\n"
			"7.  Usteda memorijskog prostora\n"
			"8.  Kraj rada \n\n"
			"Vas izbor ?"
			);


		int izbor; scanf("%d", &izbor);
		switch (izbor){
		case 1: // Stvaranje matrice
			printf("Red matrice?"); int n; scanf("%d", &n);
			if (n <= 0 || n>MAX_N) break;
			else { unisti(&M); M = stvori(n); }
			break;


		case 2: // Unos podrazumevane vrednosti
			printf("Unesi podrazumevanu vrednost \n"); int pv; scanf("%d", &pv);
			pod_vrednost(&M, pv);
			break;

		case 3: // Dohvatanje zadatog elementa
			printf("vrsta elementa i=?"); int ii; scanf("%d", &ii);
			printf("kolona elementa j=?"); int ij; scanf("%d", &ij);
			switch (citaj(&M, ii, ij, n)){
			case -1: printf("\n\n"); break;
			default: printf("Na mestu nalazi se element cija je vrednost %d \n\n", citaj(&M, ii, ij, n));
			}
			break;


		case 4: // Postavljanje  vrednosti zadatog elementa
			printf("vrsta elementa i=?"); scanf("%d", &ii);
			printf("kolona elementa j=?"); scanf("%d", &ij);
			printf("vrednost elementa X=?"); int x; scanf("%d", &x);
			upis(&M, ii, ij, n, x);
			break;

		case 5: // Ispis matrice
			printf("Matrica:"); pisi(M); break;

		case 6: // broj nepodrazumevanih elemenata
			printf("broj nepodrazumevanih elemenata je %d \n\n", brojel(n));
			break;

		case 7: //Usteda memorije
			printf("usteda memorije je %d procenata\n\n", usteda(n));
			break;
		case 8:
			kraj = 1; break;

		} // end case

	} /* end while */
} /* end main */