#include <stdio.h>
#include <stdlib.h>

typedef struct elem { 
	int broj;
struct	elem* sled;
} Elem;

typedef Elem* Stek;

Stek stvori() { return NULL; }
void stavi(Stek* s, int b) {
	Elem* novi = malloc(sizeof(Elem));
	novi->broj = b;
	novi->sled = *s;
	*s = novi;
}
int prazan(Stek s) { return s == NULL; }
int uzmi(Stek* s) {
	if (*s == NULL) exit(1);
	int b = (*s)->broj;
	Elem* stari = *s;
	(*s) = (*s)->sled;
	free(stari);
	return b;
}
int vrati(Stek* s) {
	if (*s == NULL) exit(2);
	int b = (*s)->broj;
	return b;
}
int zauzeto(Stek * s) {
	if (*s == NULL) exit(3);
	int z = 0;
	Elem* tek = (*s);
	while (tek != NULL) { z++; tek = tek->sled; }
	return z;
}
void pisi(Stek s) {
	for (Elem* tek = s; tek; tek = tek->sled) printf("%d", tek->broj);
}
void prazni(Stek* s) { while (*s) { Elem* stari = *s; (*s) = (*s)->sled; free(stari); } }
int main() {
	Stek s = stvori();

	int izbor;
	_Bool kraj = 0;

	while (!kraj) {
		printf("\n 1.Stavljanje podatka na stek\n"
			"   2.Uklanjanje elementa sa steka uz vracanje vrednosti\n"
			"   3.Dohvatanje elementa sa steka bez uklanjanja\n"
			"   4.Dohvatanje broja zauzetih mesta na steku\n"
			"   5.Ispisivanje steka\n"
			"   6.Praznjenje steka\n"
			"   0.Zavrsetak rada\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("Broj?");
			int b;
			scanf("%d", &b);
			stavi(&s, b);
			break;
		case 2:
			if (!prazan(s))  { printf("Broj=     %d\n", uzmi(&s)); }
			else { printf("Stek je prazan"); } break;
		case 3:
			if (!prazan(s))  { printf("Broj=     %d\n", vrati(&s)); }
			else { printf("Stek je prazan"); } break;
		case 4:
			if (!prazan(s))  { printf("Broj zauzetih mesta na steku je=     %d\n", zauzeto(&s)); }
			else { printf("Stek je prazan"); } break;
		case 5:
			printf("Stek=\n"); pisi(s); putchar('\n'); break;
		case 6:
			prazni(&s); break;
		case 0:
			kraj = 1;
			break;
		default:
			printf("Pogresan izbor!!");
		}
	}
	return 0;
}
