#include <stdio.h>
#include <stdlib.h>

#define max 20



int main() {
	int n, pom;
	int m;
	int a[max];
	int b[max];
	int brpr, ukbr = 0;
	int k = 0;
	int radi = 1;
	int izbor;
	while (radi) {
		printf("Izbor?\n"
			"1.kada korisnik unosi \n"
			"2.kada se random generise \n"
			"3.pretrazivanje sa bacanjem na pocetak \n");

		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			printf("Unesi duzinu niza,maksimalna je %d\n", max);
			scanf("%d", &n);
			if (n<0 || n>max) exit(1);
			printf("Unesi elemente niza za pretragu\n");
			for (int i = 0; i < n; i++) {
				scanf("%d", &a[i]);
			}
			printf("Unesi duzinu niza kljuceva%d\n");
			scanf("%d", &m);
			if (m<0 || m>max) exit(1);
			printf("Unesi elemente niza kljuceva\n");
			for (int p = 0; p < m; p++) {
				scanf("%d ", &b[p]);
			}

			for (int i = 0; i < n; i++) {
				printf("%d ", a[i]);


			} printf("\n");

			for (int p = 0; p < m; p++) {
				printf("%d ", b[p]);
			}
			printf("\n");
			break;
		case 2:
			n = (max - 1 + 1)*(double)rand() / RAND_MAX + 1;
			for (int i = 0; i < n; i++) {
				a[i] = rand();
			}
			for (int i = 0; i < n; i++) {
				printf("%d ", a[i]);
			}
			m = (n - 1 + 1)*(double)rand() / RAND_MAX + 1;
			for (int i = 0; i < m; i++) {
				b[i] = rand();
			} printf("\n");

			for (int i = 0; i < m; i++) {
				printf("%d ", b[i]);
			}printf("\n"); break;
		case 3:
			for (int j = 0; j < m; j++) {
				brpr = 0;
				for (int i = 0; i < n; i++) {
					if (b[j] = a[i]) { pom = a[i]; int x = i;
					while (x>0) { a[x] = a[x - 1];  x--; } 
					a[0] = pom; ukbr = ukbr + brpr; k++; }
					else brpr++;
				}

				printf("Statistika uspesne pretrage za kljuc iznosi:%f\n posto", (ukbr / k)*100);
			}
		}
	}
}