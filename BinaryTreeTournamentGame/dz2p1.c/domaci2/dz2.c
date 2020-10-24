#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max 100

typedef struct node {
	char ime[30];
	char prezime[30];
	int rank;
	struct node *left, *right;
	int runda;
} Node;
typedef Node* Stablo;
Stablo stvori(void) {
	return NULL;
}
typedef struct elem {
	char ime[30];
	char prezime[30];
	int rank;
	struct elem* sled;
} Elem;


int height(Stablo stb) {
	int min = max;
	int v = 0;
	int top = 0;
	Node* niz[max];
	for (int i = 0; i < max; i++) { niz[i] = NULL; }
	Node* next;

	top++;

	niz[top] = stb;
	while (top != 0)
	{
		next = niz[top];
		top--;
		while (next != NULL) {
			if (min>next->runda) { min = next->runda; v++; }
			if (next->right != NULL) {
				top++;
				
				niz[top] = next->right;
			}
			next = next->left;
		}
	}

	return v;
}

int main() {
	Stablo stb = stvori();
	Elem* lst = NULL;
	Node* niz[max];
	int radi = 1;
	int n;
	int izbor;
	while (radi) {
		printf("Izbor?\n"
			"1. Formiranje kostura turnira\n"
			"2. Popunjavanje stabla rezultata meceva\n"
			"3. Pobednik takmicenja\n"
			"4. Ispis parova u zadatoj rundi\n"
			"5. Crtaj\n"
			"6. Brisi\n"
			"7. Odredjivanje visine stabla\n"
		    "8. Inorder poredak ovog stabla\n");
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1: {
					printf("br takmicara?");
					
					scanf("%d", &n);
					if (n < 0) { printf("Ne moze negativan broj takmicara"); break; }
					if (n % 2 != 0) {
						printf("Greska,morate da imate paran broj igraca");
						break;
					}


					for (int i = 1; i < n + 1; i++) {
						Elem* novi = malloc(sizeof(Elem));
						novi->sled = NULL;
						Node* newnode = malloc(sizeof(Node));
						newnode->left = NULL;
						newnode->right = NULL;
						printf("Unesite ime takmicara\n");
						scanf("%s", &novi->ime);
						strcpy(newnode->ime, novi->ime);
						printf("Unesite prezime takmicara\n");
						scanf("%s", &novi->prezime);
						strcpy(newnode->prezime, novi->prezime);
						novi->rank = i;
						newnode->rank = novi->rank;
						niz[i] = newnode;
						if (!lst) { lst = novi; }
						else {
							Elem* tek = lst;
							while (tek->sled) tek = tek->sled;
							tek->sled = novi;
						}


					}
					printf("Ovo su nasi takmicari\n");
					Elem* tek = lst;
					while (tek) {

						printf("Takmicar %s %s sa rankom %d\n", tek->ime, tek->prezime, tek->rank);
						tek = tek->sled;

					}

					int ukbrcv = 2 * n - 1;
					int brcvnaniv = 1;
					int sum = 0;
					int index = 0;
					int rund = 0;
					int brelem = n + 1;
					int nivo = 1;
					while (n > brcvnaniv) {
						brcvnaniv = brcvnaniv * 2;
						nivo = nivo + 1;
					}
					sum = pow(2, nivo - 1) - 1;

					if (ukbrcv - sum != 0) {
						rund++;
						brcvnaniv = brcvnaniv / 2;
						index = n - (ukbrcv - sum) + 1;
						while (index != brelem) {
							brelem = brelem - 1;
							Node* newnode = malloc(sizeof(Node));
							newnode->left = niz[index];
							newnode->right = niz[brelem];
							newnode->left->runda = rund;
							newnode->right->runda = rund;
							if (newnode->left->rank < newnode->right->rank) {
								strcpy(newnode->ime, newnode->left->ime);
								strcpy(newnode->prezime, newnode->left->prezime);
								newnode->rank = newnode->left->rank;
							}
							else {
								strcpy(newnode->ime, newnode->right->ime);
								strcpy(newnode->prezime, newnode->right->prezime);
								newnode->rank = newnode->right->rank;
							}
							niz[brelem] = NULL;
							niz[index] = newnode;
							index = index + 1;


						}
					} //kraj if za ispitivanje prekvalifikacija



					while (brcvnaniv != 1) {
						index = 1;
						int pom = brcvnaniv;
						rund++;
						while (pom != 0) {
							brelem = brelem - 1;
							Node* newnode = malloc(sizeof(Node));
							newnode->left = niz[index];
							newnode->right = niz[brelem];
							newnode->left->runda = rund;
							newnode->right->runda = rund;
							if (newnode->left->rank < newnode->right->rank) {
								strcpy(newnode->ime, newnode->left->ime);
								strcpy(newnode->prezime, newnode->left->prezime);
								newnode->rank = newnode->left->rank;
							}
							else {
								strcpy(newnode->ime, newnode->right->ime);
								strcpy(newnode->prezime, newnode->right->prezime);
								newnode->rank = newnode->right->rank;
							}
							niz[brelem] = NULL;
							niz[index] = newnode;
							index = index + 1;

							pom = pom - 2;
						}
						brcvnaniv = brcvnaniv / 2;

					} // end while-a 
					rund++;
					stb = niz[1];
					stb->runda = rund;
					break; }
		case 2:
		{
				  int n = 0;
				  int p = 0;
				  Node* tek = stb;
				  if (!stb) { printf("Ne mogu se uneti rezultati,stablo je prazno!\n"); break; }
				  niz[n++] = tek;
				  while (p != n) {
					  if (p == 0) { p++; }
					  if (tek->left != NULL && tek->right != NULL) {
						  niz[n++] = tek->left;
						  niz[n++] = tek->right;
					  }
					  tek = niz[p++];
				  }
				  p = p - 1;
				  while (p >= 0) {
					  tek = niz[p];
					  if (tek->left != NULL && tek->right != NULL)
					  {
						  int answer;
						  printf("Ko je pobedio u mecu izmedju takmicara sa rankom %d i rankom %d\n", tek->left->rank, tek->right->rank);
						  scanf("%d", &answer);


						  tek->rank = answer;
						  if (tek->rank == tek->left->rank) {
							  strcpy(tek->ime, tek->left->ime);
							  strcpy(tek->prezime, tek->left->prezime);
						  }
						  else {
							  strcpy(tek->ime, tek->right->ime);
							  strcpy(tek->prezime, tek->right->prezime);
						  }

					  }
					  p--;
				  }
				  break;
		}
		case 3:
		{         if (!stb) { printf("Takmicenje nije jos pocelo!\n"); break; }
		printf("Pobednik ovog takmicenja je takmicar %s %s sa rankom %d\n", stb->ime, stb->prezime, stb->rank);
		break; }
		case 4:
		{         int rundica;
		printf("Unesite rundu takmicenja koja vas interesuje\n");
		scanf("%d", &rundica);
		printf("Parovi u rundi su:\n");
		int n = 0;
		int p = 0;
		Node* tek = stb;
		if (!stb) { printf("Takmicenje nije jos pocelo!\n"); break; }
		niz[n++] = tek;
		while (p != n) {
			if (p == 0) { p++; }
			if (tek->left != NULL && tek->right != NULL) {
				niz[n++] = tek->left;
				niz[n++] = tek->right;
			}
			tek = niz[p++];
		}
		p = p - 1;
		while (p >= 0) {
			tek = niz[p];
			if (tek->left != NULL && tek->right != NULL)
			{
				if (tek->left->runda == rundica && tek->right->runda == rundica) {
					printf("Takmicar %s %s sa rangom %d i takmicar %s %s sa rangom %d\n", tek->left->ime, tek->left->prezime, tek->left->rank, tek->right->ime, tek->right->prezime, tek->right->rank);
				}
			}
			p = p - 1;
		}

		break;
		}
		case 5: {
					int n = 0;
					int nivo = 0;
					int br = pow(2, nivo);
					int p = 0;
					Node* tek = stb;
					if (!stb) { printf("Nema stabla!\n"); break; }
					niz[n++] = tek;
					while (p != n) {
						if (p == 0) { p++; }
						if (tek->left != NULL && tek->right != NULL) {
							niz[n++] = tek->left;
							niz[n++] = tek->right;
						}
						tek = niz[p++];
					}

					for (int i = 0; i < p; i++) {
						int pomoc = 2 * p;
						Node* cvor = niz[i];
						printf("%*s", 4 * (p/2-nivo), "  ");
						printf("%*s%d", nivo, "", cvor->rank);
						if (i % 2 == 0) { printf("%*s", 4 * nivo, "  "); }
						br--;
						if (br == 0) { nivo++; br = pow(2, nivo); printf("\n"); }
					}
					printf("\n");
					break; }
		case 6: {
					int n = 0;
					int nivo = 0;
					int br = pow(2, nivo);
					int p = 0;
					Node* tek = stb;
					if (!stb) { printf("Nema stabla!\n"); break; }
					niz[n++] = tek;
					while (p != n) {
						if (p == 0) { p++; }
						if (tek->left != NULL && tek->right != NULL) {
							niz[n++] = tek->left;
							niz[n++] = tek->right;
						}
						tek = niz[p++];
					}
					for (int i = 0; i < p; i++) {
						stb = niz[i];
						free(stb);
						stb= NULL;
					}
					
					break;
		}
		case 7:
		{int visina = height(stb);
		printf("Visina stabla je %d\n", visina); }
		case 8:
		{   int top = 0;
		Node* next = stb;
		Node* array[max];
		int ukbr = 2 * n - 1;
		while (ukbr != 0) {
			while (next != NULL) {
				top++;
				array[top] = next;
				next = next->left;

			}
			if (top != 0) {
				next = array[top];
				top--;
				printf("%d ", next->rank);
				next = next->right;
				ukbr--;
			}
		} 
		printf("\n");
		break;
		}
		
			} // switch end
		}
	}

