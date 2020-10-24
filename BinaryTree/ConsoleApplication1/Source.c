# include <stdio.h>
# include <conio.h>
# include <stdlib.h>

typedef struct node {
	int data;
	struct node *left, *right;
} Node;
typedef Node* Stablo;
Stablo stvori(void) {
	return NULL;
}
Stablo dodaj(Stablo stb, int b) {

	Node *ptr=NULL;
	Node *ptr_parent;
	Node *newNode;
	if (!stb)
	{
		stb = malloc(sizeof(Node));
		stb->data = b;
		stb->left = NULL;
		stb->right = NULL;

		ptr = stb;
	}
	else {
		ptr = stb;
		while (ptr != NULL)
		{
			

			if (b < (ptr->data))
			{
				ptr_parent = ptr;
				ptr = ptr->left;
			}
			else {
				ptr_parent = ptr;
				ptr = ptr->right;
			}
		}

		newNode = malloc(sizeof(Node));
		newNode->data = b;
		newNode->left = NULL;
		newNode->right = NULL;


		if (b < (ptr_parent->data))
			ptr_parent->left = newNode;
		else
			ptr_parent->right = newNode;
	}

	return stb;
}

Node *find(Stablo stb, int b) {
	Node *ptr;
	Node *ptr_parent;
	
	if (!stb) return NULL;
	int pom;
	
	if (!stb) return NULL;
	if (stb->data == b) return stb;
	ptr = stb;
	pom = 1;
	while (ptr != NULL && b != ptr->data)
	{

		if (b < (ptr->data))
		{
			ptr_parent = ptr;
			ptr = ptr->left;
		}
		else {
			ptr_parent = ptr;
			ptr = ptr->right;
		}

	}
	return ptr;
}

Stablo nadjimax(Stablo stb) {                          
	Node* pom;
	pom = stb;
	while (pom->right != NULL) { pom = pom->right; }
	return pom;
}


Node *nadji_prethodnik(Stablo stb, int b) {
	Node *ptr;
	Node *pret = NULL;
	
	if (!stb) return NULL;

	

	ptr = find(stb, b);

	if (ptr->left != NULL) return nadjimax(ptr->left);

	
	while (stb != NULL)
	{
		if (ptr->data > stb->data)
		{
			pret = stb;
			stb = stb->right;
		}
		else if (ptr->data < stb->data)
			stb = stb->left;
		else
			break;
	}

	return pret;
}




void crtaj(Stablo stb, int nivo) {
	if (stb) {
		crtaj(stb->right, nivo + 1);
		printf("%*s%d\n", 4 * nivo, "", stb->data);
		crtaj(stb->left, nivo + 1);
	} //end if
}//end crtaj              


int main() {
	Stablo stb = stvori();
	int radi = 1;
	int izbor;
	while (radi) {
		printf("Izbor?\n"
			"1. dodaj u stablo\n"
			"2. trazi kljuc.\n"
			"3. umetni u stablo.\n"
			"4. brisi.\n"
			"5. Invertovanje.\n"
			"6. Crtaj.\n"
			"7. Nalazenje prethodnika.\n"
			"8. Kraj.\n");
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			printf("Kljuc?");
			int k;
			scanf("%d", &k);
			stb = dodaj(stb, k);
			break;

		case 2:
			printf("Trazi?");
			int t;
			scanf("%d", &t);
			printf("Broj se %s nalazi u stablu.\n", (find(stb, t) != NULL ? "" : "NE"));
			break;


		case 6:
			crtaj(stb, 0);
			break;



		case 7:
			printf("Kljuc?");
			int p;
			scanf("%d", &p);
			printf("Prethodnik cvora sa kljucem %d je cvor %d \n", p, nadji_prethodnik(stb, p)->data);
			break;

		case 8:
			break;
		}
	}
}