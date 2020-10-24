#include <stdio.h>
#include <stdlib.h>
#define max 30

typedef struct elem {
	int row;
	int col;
	int val;
	struct elem* nxt;
	struct elem* dwn;
} Elem;



int main(){
	int br = 0;
	int pv = 0;
	Elem* rows[max];
	Elem* columns[max];
	int n, m;
	_Bool kraj = 0;
	while (!kraj) {
		printf("\n1.  Stvaranje matrice\n"
			"2.  Unos podrazumevane vrednosti\n"
			"3.  Dohvatanje zadatog elementa\n"
			"4.  Postavljanje vrednosti zadatog elementa\n"
			"5.  Dohvatanje broja nepodrazumevanih elemenata\n"
			"6.  Ispis matrice\n"
			"7.  Brisanje matrice\n"
			"8.  Formiranje jedne gornje trougaone i jedne strogo donje trougaone matrice\n"
			"9.  Kraj rada \n\n"
			"Vas izbor ?"
			);


		int izbor; scanf("%d", &izbor);
		switch (izbor){
		case 1: // Stvaranje matrice
		{
					printf("Unesi br vrsta matrice ");
					scanf("%d", &n);
					if (n <= 0 || n > max) break;
					printf("Unesi br kolona matrice ");
					scanf("%d", &m);
					if (m <= 0 || m > max) break;
					for (int i = 1; i < n + 1; i++) {
						rows[i] = NULL;
					}
					for (int i = 1; i < m + 1; i++) {
						columns[i] = NULL;
					}
					printf("Koliko nepodrazumevanih elemenata zelite ");
					scanf("%d", &br);
					int pom = br;
					while (pom != 0) {
						Elem* novi = malloc(sizeof(Elem));
						printf("Unesi vrstu u koju stavljas element ");
						scanf("%d", &(novi->row));
						if (novi->row <= 0 || novi->row>n) { printf("/n Izvan opsega"); break; }
						printf("Unesi kolonu u koju stavljas element ");
						scanf("%d", &(novi->col));
						if (novi->col <= 0 || novi->col > m) { printf("/n Izvan opsega"); break; }
						printf("Unesi vrednost novog elementa ");
						scanf("%d", &(novi->val));
						novi->nxt = NULL;
						novi->dwn = NULL;
						if (rows[novi->row] == NULL && columns[novi->col] == NULL) { rows[novi->row] = novi; columns[novi->col] = novi; }
						else {
							if (rows[novi->row] != NULL) {
								Elem* tek = rows[novi->row];
								if (rows[novi->row]->col > novi->col) {
									novi->nxt = tek;
									rows[novi->row] = novi;
								}
								else {

									while (tek->nxt != NULL && tek->nxt->col < novi->col) { tek = tek->nxt; }

									novi->nxt = tek->nxt;
									tek->nxt = novi;
								}
							}
							else { rows[novi->row] = novi; }
							if (columns[novi->col] != NULL) {
								Elem* tek = columns[novi->col];
								if (columns[novi->col]->row > novi->row) {
									novi->dwn = tek;
									rows[novi->row] = novi;
								}
								else {
									while (tek->dwn != NULL && tek->dwn->row < novi->row) { tek = tek->dwn; }
									novi->dwn = tek->dwn;
									tek->dwn = novi;
								}
							}
							else { columns[novi->col] = novi; }
						}
						pom--;
					}
					break;
		}

		case 2: // Unos podrazumevane vrednosti
			printf("Unesi podrazumevanu vrednost \n"); scanf("%d", &pv);

			break;

		case 3: // Dohvatanje zadatog elementa
		{int tr;
		printf("vrsta elementa i=?"); int ii; scanf("%d", &ii);
		printf("kolona elementa j=?"); int ij; scanf("%d", &ij);
		printf("Ocitavanje vrednosti sa mesta %d,%d \n", ii, ij);
		if (ii > n || ij > m || ii <= 0 || ij <= 0)
		{
			printf(" Greska: izvan opsega");

		}
		else
		{
			tr = pv;
			for (int i = 1; i < n + 1; i++) {

				Elem* tek = rows[i];
				while (tek != NULL) {
					if (tek->row == ii && tek->col == ij) { tr = tek->val; break; }
					else { if (tek->nxt != NULL) { tek = tek->nxt; } else break; }
				}


			}
			printf("%d", tr);
		}
		break;
		}
		case 4: // Postavljanje  vrednosti zadatog elementa
		{int tr, vr;
		printf("vrsta elementa i=?"); int ii; scanf("%d", &ii);
		printf("kolona elementa j=?"); int ij; scanf("%d", &ij);
		printf("Postavljanje vrednosti zadatom elementu na mesto  %d,%d \n", ii, ij);
		printf("Unesite koju vrednost hocete da postavite");
		scanf("%d", &vr);
		if (ii > n || ij > m || ii <= 0 || ij <= 0)
		{
			printf(" Greska: izvan opsega");

		}
		else
		{
			tr = pv;
			for (int i = 1; i < n + 1; i++) {

				Elem* tek = rows[i];
				while (tek != NULL) {
					if (tek->row == ii && tek->col == ij) { tr = tek->val; tek->val = vr; break; }
					else { if (tek->nxt != NULL) { tek = tek->nxt; } else break; }
				}


			}

		}
		if (tr == pv) {
			Elem* novi = malloc(sizeof(Elem));
			novi->row = ii;
			novi->col = ij;
			novi->val = vr;
			novi->dwn = NULL;
			novi->nxt = NULL;
			if (rows[novi->row] == NULL && columns[novi->col] == NULL) { rows[novi->row] = novi; columns[novi->col] = novi; }
			else {
				if (rows[novi->row] != NULL) {
					Elem* tek = rows[novi->row];
					if (rows[novi->row]->col > novi->col) {
						novi->nxt = tek;
						rows[novi->row] = novi;
					}
					else {

						while (tek->nxt != NULL && tek->nxt->col < novi->col) { tek = tek->nxt; }

						novi->nxt = tek->nxt;
						tek->nxt = novi;
					}
				}
				else { rows[novi->row] = novi; }
				if (columns[novi->col] != NULL) {
					Elem* tek = columns[novi->col];
					if (columns[novi->col]->row > novi->row) {
						novi->dwn = tek;
						rows[novi->row] = novi;
					}
					else {
						while (tek->dwn != NULL && tek->dwn->row < novi->row) { tek = tek->dwn; }
						novi->dwn = tek->dwn;
						tek->dwn = novi;
					}
				}
				else { columns[novi->col] = novi; }
			}
			br++;
		}
		break;
		}
		case 5: // broj nepodrazumevanih elemenata
			printf("broj nepodrazumevanih elemenata je %d \n\n", br);
			break;


		case 6: // Ispis matrice
			printf("Matrica:\n");
			for (int i = 1; i < n + 1; i++) {
				Elem* tek = rows[i];
				for (int j = 1; j < m + 1; j++) {
					if (tek != NULL && tek->row == i && tek->col == j) { printf("%d ", tek->val); if (tek->nxt != NULL) { tek = tek->nxt; } else { tek = malloc(sizeof(Elem)); tek->col = 0; tek->col = 0; } }
					else printf("%d ", pv);
				}
				printf("\n");
			}
			break;



		case 7: //Brisanje matrice
			for (int i = 1; i < n + 1; i++) {
				Elem* tek = rows[i];
				rows[i] = NULL;
				for (int j = 1; j < m + 1; j++) {
					if (tek != NULL && tek->row == i && tek->col == j) { Elem* stari = tek; if (tek->nxt != NULL) { tek = tek->nxt; } else { tek = malloc(sizeof(Elem)); tek->col = 0; tek->col = 0; } free(stari); }
					columns[j] = NULL;
				}

			}
			printf("Matrica je obrisana");
			break;
		case 8:
		{
				  Elem* rowsa[max];
				  Elem* rowsb[max];
				  Elem* columnsa[max];
				  Elem* columnsb[max];
				  for (int i = 1; i < n + 1; i++) {
					  rowsa[i] = NULL;
					  rowsb[i] = NULL;
				  }
				  for (int i = 1; i < m + 1; i++) {
					  columnsa[i] = NULL;
					  columnsb[i] = NULL;
				  }
				  for (int i = 1; i < n + 1; i++) {
					  Elem* tek = rows[i];
					  for (int j = 1; j < m + 1; j++) {
						  if (tek != NULL && tek->row == i && tek->col == j) {
							  if (i >= j) {
								  Elem* novi = malloc(sizeof(Elem));
								  novi->row = tek->row;
								  novi->col = tek->col;
								  novi->val = tek->val;
								  novi->dwn = NULL;
								  novi->nxt = NULL;
								  if (rowsa[novi->row] == NULL && columnsa[novi->col] == NULL) { rowsa[novi->row] = novi; columnsa[novi->col] = novi; }
								  else {
									  if (rowsa[novi->row] != NULL) {
										  Elem* teku = rowsa[novi->row];
										  if (rowsa[novi->row]->col > novi->col) {
											  novi->nxt = teku;
											  rowsa[novi->row] = novi;
										  }
										  else {

											  while (teku->nxt != NULL && teku->nxt->col < novi->col) { teku = teku->nxt; }

											  novi->nxt = teku->nxt;
											  teku->nxt = novi;
										  }
									  }
									  else { rowsa[novi->row] = novi; }
									  if (columnsa[novi->col] != NULL) {
										  Elem* teku = columnsa[novi->col];
										  if (columnsa[novi->col]->row > novi->row) {
											  novi->dwn = teku;
											  rowsa[novi->row] = novi;
										  }
										  else {
											  while (teku->dwn != NULL && teku->dwn->row < novi->row) { teku = teku->dwn; }
											  novi->dwn = teku->dwn;
											  teku->dwn = novi;
										  }
									  }
									  else { columnsa[novi->col] = novi; }
								  }

							  }
							  else {
								  Elem* novi = malloc(sizeof(Elem));
								  novi->row = tek->row;
								  novi->col = tek->col;
								  novi->val = tek->val;
								  novi->dwn = NULL;
								  novi->nxt = NULL;
								  if (rowsb[novi->row] == NULL && columnsb[novi->col] == NULL) { rowsb[novi->row] = novi; columnsb[novi->col] = novi; }
								  else {
									  if (rowsb[novi->row] != NULL) {
										  Elem* teku = rowsb[novi->row];
										  if (rowsb[novi->row]->col > novi->col) {
											  novi->nxt = teku;
											  rowsb[novi->row] = novi;
										  }
										  else {

											  while (teku->nxt != NULL && teku->nxt->col < novi->col) { teku = teku->nxt; }

											  novi->nxt = teku->nxt;
											  teku->nxt = novi;
										  }
									  }
									  else { rowsb[novi->row] = novi; }
									  if (columnsb[novi->col] != NULL) {
										  Elem* teku = columnsb[novi->col];
										  if (columnsb[novi->col]->row > novi->row) {
											  novi->dwn = teku;
											  rowsb[novi->row] = novi;
										  }
										  else {
											  while (teku->dwn != NULL && teku->dwn->row < novi->row) { teku = teku->dwn; }
											  novi->dwn = teku->dwn;
											  teku->dwn = novi;
										  }
									  }
									  else { columnsb[novi->col] = novi; }
								  }

							  }
							  if (tek->nxt != NULL) { tek = tek->nxt; }
							  else { tek = malloc(sizeof(Elem)); tek->col = 0; tek->col = 0; }
						  }
					  }
				  }
				  printf("Strogo donje trougaona matrica izgleda ovako:\n");
				  for (int i = 1; i < n + 1; i++) {
					  Elem* tek = rowsa[i];
					  for (int j = 1; j < m + 1; j++) {
						  if (tek != NULL && tek->row == i && tek->col == j) { printf("%d ", tek->val); if (tek->nxt != NULL) { tek = tek->nxt; } else { tek = malloc(sizeof(Elem)); tek->col = 0; tek->col = 0; } }
						  else printf("%d ", pv);
					  }
					  printf("\n");
				  }
				  printf("Gornje trougaona matrica izgleda ovako:\n");
				  for (int i = 1; i < n + 1; i++) {
					  Elem* tek = rowsb[i];
					  for (int j = 1; j < m + 1; j++) {
						  if (tek != NULL && tek->row == i && tek->col == j) { printf("%d ", tek->val); if (tek->nxt != NULL) { tek = tek->nxt; } else { tek = malloc(sizeof(Elem)); tek->col = 0; tek->col = 0; } }
						  else printf("%d ", pv);
					  }
					  printf("\n");
				  }
				  break; }
		case 9:
			kraj = 1; break;

		} // end case

	} /* end while */
} /* end main */