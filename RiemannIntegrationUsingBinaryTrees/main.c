#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100

// cvor stabla
typedef struct cvor
{
	char key;
	struct cvor *right, *left;
}Cvor;

// element liste za level order
typedef struct elem
{
	Cvor *cvor;
	int lvl;
	struct elem *sled;
}Elem;

// pravi stablo po zadatom postfix obliku
Cvor* constructTree(char postfix[])
{
	Cvor* st[MAX];
	int cnt = -1;
	Cvor *t, *t1, *t2;

	for (int i = 0; i < strlen(postfix); i++)
	{
		// ako je operand ide na stek
		if (postfix[i] >= 'A' && postfix[i] <= 'Z')
		{
			t = malloc(sizeof(Cvor));
			t->key = postfix[i];
			t->right = t->left = NULL;
			st[++cnt] = t;
		}
		else // operator
		{

			t = malloc(sizeof(Cvor));
			t->key = postfix[i];
			t->right = t->left = NULL;

			if (t->key == '!' || t->key == '?')
			{
				t1 = malloc(sizeof(Cvor));
				t1->key = postfix[++i];
				t1->left = t1->right = NULL;
				t->left = t1;
				st[++cnt] = t;
				continue;
			}
			// popujemo 2 cvora
			t1 = st[cnt--];
			if (t->key != 'a')
			{
				t2 = st[cnt--];
				t->left = t2;
				t->right = t1;
			}
			else
				t->left = t1;

			// dobijeni izraz se stavlja na stek
			st[++cnt] = t;
		}
	}

	// koren stabla
	t = st[cnt--];

	return t;
}

// prioritet operacija
int priority(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/' || x == '%')
		return 2;
	if (x == '^')
		return 3;
	return 4;
}

// brisanje liste koja se dobije level orderom
void del_list(Elem *prvi)
{
	Elem *tek = prvi;
	while (tek != NULL)
	{
		tek = tek->sled;
		free(prvi);
		prvi = tek;
	}
}

// pravljenje liste level orderom
Elem* level_order(Cvor* root) {
	Elem *head, *tek, *pom;

	if (root == NULL) return NULL;
	head = tek = pom = calloc(1,sizeof(Elem));
	head->cvor = root;
	head->lvl = 1;

	while (pom != NULL) {
		if (pom->cvor->left != NULL) {
			tek->sled = calloc(1, sizeof(Elem));
			tek = tek->sled;
			tek->cvor = pom->cvor->left;
			tek->lvl = pom->lvl + 1;
		}
		if (pom->cvor->right != NULL) {
			tek->sled = calloc(1, sizeof(Elem));
			tek = tek->sled;
			tek->cvor = pom->cvor->right;
			tek->lvl = pom->lvl + 1;
		}
		pom = pom->sled;
	}

	return head;
}

// brisanje stabla
void del_tree(Cvor* root)
{
	Elem *prvi = level_order(root);
	Elem *tek = prvi;

	while (tek != NULL)
	{
		tek = tek->sled;
		free(prvi->cvor);
		free(prvi);
		prvi = tek;
	}
}

// pomocna funkcija za crtanje stabla
int draw(Cvor *root, int levi, int pomeraj, int dubina, char **s)
{
	char b[20];
	int sirina, i;

	if (root == NULL) return 0;

	sprintf(b, "%c", root->key);
	sirina = strlen(b);

	int left = draw(root->left, 1, pomeraj, dubina + 1, s);
	int right = draw(root->right, 0, pomeraj + left + sirina, dubina + 1, s);

	for (i = 0; i < sirina; i++)
		s[2 * dubina][pomeraj + left + i] = b[i];

	if (dubina != 0 && levi == 1)
	{

		for (i = 0; i < sirina + right; i++)
			s[2 * dubina - 1][pomeraj + left + sirina / 2 + i] = '~';

		s[2 * dubina - 1][pomeraj + left + sirina / 2] = '~';
		s[2 * dubina - 1][pomeraj + left + sirina + right + sirina / 2] = '~';

	}
	else if (dubina != 0 && levi == 0)
	{

		for (i = 0; i < left + sirina; i++)
			s[2 * dubina - 1][pomeraj - sirina / 2 + i] = '~';

		s[2 * dubina - 1][pomeraj + left + sirina / 2] = '~';
		s[2 * dubina - 1][pomeraj - sirina / 2 - 1] = '~';
	}

	return left + sirina + right;

}

// funkcija za crtanje stabla
void draw_tree(Cvor *root)
{
	int i, j, dubina;
	char **s;
	Elem *prvi = level_order(root);
	Elem *posl = prvi;

	if (prvi == NULL) return;
	while (posl->sled != NULL) posl = posl->sled;

	dubina = posl->lvl * 2;
	del_list(prvi);
	s = (char**)malloc((dubina)*sizeof(char*));
	if (s == NULL) exit(1);
	for (i = 0; i < dubina; i++)
	{
		s[i] = (char*)malloc(255 * sizeof(char));
		if (s[i] == NULL) exit(1);
	}

	for (i = 0; i < dubina; i++)
	{
		for (j = 0; j < 80; j++)
			s[i][j] = ' ';
		s[i][j] = '\0';
	}

	draw(root, 0, 0, 0, s);

	for (i = 0; i < dubina; i++)
	for (j = 0; j < 255; j++)
	{
		if (s[i][j] == '!') s[i][j] = '+';
		else if (s[i][j] == '?') s[i][j] = '-';
	}

	for (i = 0; i < dubina; i++)
		printf("%s", s[i]);

	printf("\n");

	for (i = 0; i < dubina; i++)
		free(s[i]);
	free(s);
}

// racuna vrednost izraza u stablu
double calc(Cvor *root, double val[26], char init[26])
{
	double x;
	switch (root->key)
	{
		case '+': return calc(root->left, val, init) + calc(root->right, val, init);
		case '-': return calc(root->left, val, init) - calc(root->right, val, init);
		case '*': return calc(root->left, val, init) * calc(root->right, val, init);
		case '/': return calc(root->left, val, init) / calc(root->right, val, init);
		case '%': return (int)calc(root->left, val, init) % (int)calc(root->right, val, init);
		case '^': return pow(calc(root->left, val, init), calc(root->right, val, init));
		case 'x':
			if (init[root->left->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->left->key);
				scanf("%lf", &x);
				val[root->left->key - 'A'] = x;
				init[root->left->key - 'A'] = '1';
			}
			if (init[root->right->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->right->key);
				scanf("%lf", &x);
				val[root->right->key - 'A'] = x;
				init[root->right->key - 'A'] = '1';
			}

			return val[root->left->key - 'A'] > val[root->right->key - 'A'] ? val[root->left->key - 'A'] : val[root->right->key - 'A'];
		case 'n':
			if (init[root->left->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->left->key);
				scanf("%lf", &x);
				val[root->left->key - 'A'] = x;
				init[root->left->key - 'A'] = '1';
			}
			if (init[root->right->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->right->key);
				scanf("%lf", &x);
				val[root->right->key - 'A'] = x;
				init[root->right->key - 'A'] = '1';
			}
			return val[root->left->key - 'A'] < val[root->right->key - 'A'] ? val[root->left->key - 'A'] : val[root->right->key - 'A'];
		case 'a': 
			if (init[root->left->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->left->key);
				scanf("%lf", &x);
				val[root->left->key - 'A'] = x;
				init[root->left->key - 'A'] = '1';
			}
			return val[root->left->key - 'A'] < 0 ? -val[root->left->key - 'A'] : val[root->left->key - 'A'];
		case '!': 
			if (init[root->left->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->left->key);
				scanf("%lf", &x);
				val[root->left->key - 'A'] = x;
				init[root->left->key - 'A'] = '1';
			}
			return val[root->left->key - 'A'] + 1;
		case '?':
			if (init[root->left->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->left->key);
				scanf("%lf", &x);
				val[root->left->key - 'A'] = x;
				init[root->left->key - 'A'] = '1';
			}
			return val[root->left->key - 'A'] - 1;
		case '0': return 0;
		case '1': return 1;
		default:
			if (init[root->key - 'A'] == 0)
			{
				printf("Unesite %c: ", root->key);
				scanf("%lf", &x);
				val[root->key - 'A'] = x;
				init[root->key - 'A'] = '1';
			}
			else
				x = val[root->key - 'A'];
	}
	return x;
}

// ispisuje izraz u stablu u postfixnom obliku
void make_postfix(Cvor *root, char* p)
{
	Cvor *next = root;
	Cvor *stek[MAX];

	int i = 0;
	int top = 0;

	while (next != NULL)
	{
		stek[top++] = next;
		next = next->left;
	}
	while (top > 0)
	{
		next = stek[--top];
		if (next->key > 0)
		{
			next->key = -next->key;
			stek[top++] = next;
			next = next->right;
			while (next != NULL)
			{
				stek[top++] = next;
				next = next->left;
			}
		}
		else
		{
			next->key = -next->key;
			if (next->key == '!') p[i++] = '+';
			else if (next->key == '?') p[i++] = '-';
			else p[i++] = next->key;
		}
	}
}

// pomocna funkcija za kloniranje stabla
Cvor* clone(Cvor* root)
{
	Cvor *temp;
	if (root == NULL)
		return NULL;
	temp = malloc(sizeof(Cvor));
	temp->key = root->key;
	temp->left = clone(root->left);
	temp->right = clone(root->right);

	return temp;
}

// funkcija koja trazi izvod izraza po zadatoj promenljivoj za +,-,*,/, konstante
Cvor* izvod(Cvor* root, char x)
{
	Cvor *temp, *tek;
	if (root->key == x) root->key = '1';
	else
	{
		switch (root->key)
		{
			case '+':
			case '-':
				root->left = izvod(root->left, x);
				root->right = izvod(root->right, x);
				break;
			case '*':
				tek = malloc(sizeof(Cvor));
				tek->key = '*';
				tek->left = clone(root->left);
				tek->right = clone(root->right);
				temp = malloc(sizeof(Cvor));
				temp->key = '*';
				temp->left = root->left;
				temp->right = root->right;
				root->left = temp;
				root->right = tek;
				root->key = '+';
				temp->left = izvod(temp->left, x);
				tek->right = izvod(tek->right, x);
				break;
			case '/':
				tek = malloc(sizeof(Cvor));
				tek->key = '*';
				tek->left = clone(root->right);
				tek->right = clone(root->right);
				temp = malloc(sizeof(Cvor));
				temp->key = '-';
				temp->left = malloc(sizeof(Cvor));
				temp->right = malloc(sizeof(Cvor));
				temp->left->key = temp->right->key = '*';
				temp->left->left = clone(root->left);
				temp->left->right = clone(root->right);
				temp->right->left = root->left;
				temp->right->right = root->right;
				root->left = temp;
				root->right = tek;
				root->left->left->left = izvod(root->left->left->left, x);
				root->left->right->right = izvod(root->left->right->right, x);
				break;
			default:
				root->key = '0';

		}
	}
	return root;
}

double calcInt(Cvor *root, double val[26])
{
	double x;
	switch (root->key)
	{
		case '+': return calcInt(root->left, val) + calcInt(root->right, val);
		case '-': return calcInt(root->left, val) - calcInt(root->right, val);
		case '*': return calcInt(root->left, val) * calcInt(root->right, val);
		case '/': return calcInt(root->left, val) / calcInt(root->right, val);
		case '%': return (int)calcInt(root->left, val) % (int)calcInt(root->right, val);
		case '^': return pow(calcInt(root->left, val), calcInt(root->right, val));
		case 'x': return val[root->left->key - 'A'] > val[root->right->key - 'A'] ? val[root->left->key - 'A'] : val[root->right->key - 'A'];
		case 'n': return val[root->left->key - 'A'] < val[root->right->key - 'A'] ? val[root->left->key - 'A'] : val[root->right->key - 'A'];
		case 'a': return val[root->left->key - 'A'] < 0 ? -val[root->left->key - 'A'] : val[root->left->key - 'A'];
		case '!': return val[root->left->key - 'A'] + 1;
		case '?': return val[root->left->key - 'A'] - 1;
		case '0': return 0;
		case '1': return 1;
		default: x = val[root->key - 'A'];
	}
	return x;
}

double integral(Cvor* root, char promenljiva, double a, double b, double dx)
{
	char init[26] = { 0 }, p[MAX] = { 0 };
	double val[26] = { 0 }, y;
	make_postfix(root, p);
	for (int i = 0; i < strlen(p); i++)
	if (p[i] >= 'A' && p[i] <= 'Z' && (p[i] != promenljiva) && (init[p[i] - 'A'] == 0))
	{
		printf("Unesite %c: ", p[i]);
		scanf("%lf", &y);
		val[p[i] - 'A'] = y;
		init[p[i] - 'A'] = '1';
	}

	double s = 0;

	for (double x = a; x <= b; x += dx)
	{
		val[promenljiva - 'A'] = x;
		s += calcInt(root, val);
	}

	s *= dx;
	return s;
}

void main()
{
	Cvor *root;
	char s[MAX], pom;
	char x, postfix[MAX] = {0};
	int c, i = 0;
	int top = 0;
	int unarFlag = 1;
	printf("Unesite infiksni izraz:");
	while ((c = getchar()) != '\n')
	{
		if ((c < 'A' || c > 'Z') && c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != '%' && c != 'a' && c != 'm' && c != '(' && c != ')')
			exit(1);
		if (c == 'a')
		{
			while (top > 0 && priority(c) <= priority(s[top - 1]))
			{
				x = s[--top];
				postfix[i++] = x;
			}
			s[top++] = c;
			c = getchar();
			c = getchar();
			c = getchar();
			c = getchar();
			postfix[i++] = c;
			c = getchar();
			unarFlag = 0;
		}
		else if (c == 'm')
		{
			pom = getchar();
			if (pom == 'i')
				c = 'n';
			else
				c = 'x';
			
			while (top > 0 && priority(c) <= priority(s[top - 1]))
			{
				x = s[--top];
				postfix[i++] = x;
			}
			s[top++] = c;
			c = getchar();
			c = getchar();
			c = getchar();
			postfix[i++] = c;
			c = getchar();
			c = getchar();
			postfix[i++] = c;
			c = getchar();
			unarFlag = 0;
		}
		else if (c >= 'A' && c <= 'Z')
		{
			postfix[i++] = c;
			unarFlag = 0;
		}
		else if (c == '(')
		{
			s[top++] = '(';
			unarFlag = 1;
		}
		else
		{
			if (c == ')')
			{
				while ((x = s[--top]) != '(')
					postfix[i++] = x;
				unarFlag = 0;
			}
			else
			{
				if (top > 0 && s[top - 1] == '^' && c == '^')
					s[top++] = c;
				else
				{ // unarna operacija
					if (unarFlag == 1)
					{
						if (c == '+') c = '!';
						else if (c == '-') c = '?';
						postfix[i++] = c;
						unarFlag = 0;
					}
					else //binarna operacija
					{
						while (top > 0 && priority(c) <= priority(s[top - 1]))
						{
							x = s[--top];
							postfix[i++] = x;
						}
						s[top++] = c;
						unarFlag = 1;
					}
				}
			}
		}
	}
	while (top > 0)
	{
		x = s[--top];
		postfix[i++] = x;
	}
	root = constructTree(postfix);

	int radi = 1;

	while (radi) 
	{
		int izbor;
		double res;
		char ch, init[26] = { 0 };
		double val[26], a, b, dx;
		char *post;
		printf("Izbor?\n"
			"1. Iscrtavanje stabla.\n"
			"2. Racunanje vrednosti izraza.\n"
			"3. Izraz u postfiksnoj notaciji.\n"
			"4. Izvod.\n"
			"5. Integracija.\n"
			"6. Kraj.\n");
		scanf("%d", &izbor);
		switch (izbor)
		{
			case 1:
				draw_tree(root);
				break;
			case 2:
				res = calc(root, val, init);
				printf("Rezultat je %.2lf\n\n", res);
				break;
			case 3:
				post = calloc(MAX, sizeof(char));
				make_postfix(root, post);
				printf("\n\n%s\n\n", post);
				free(post);
				break;
			case 4:
				printf("\nUnesite promenljivu po kojoj se radi izvod: ");
				getchar();
				scanf("%c", &ch);
				root = izvod(root, ch);
				break;
			case 5:
				printf("\nUnesite promenljivu po kojoj se radi integral: ");
				getchar();
				scanf("%c", &ch);
				printf("Unesite donju granicu integracije: ");
				scanf("%lf", &a);
				printf("Unesite gornju granicu integracije: ");
				scanf("%lf", &b);
				if (b < a)
				{
					int swap;
					swap = b;
					b = a;
					a = swap;
				}
				printf("Unesite korak integracije: ");
				scanf("%lf", &dx);
				printf("\nRezultat: %lf\n\n", integral(root, ch, a, b, dx));
				break;
			case 6:
				del_tree(root);
				radi = 0;
				break;
			default:
				printf("Pogresan izbor!\n");
				break;
		}
	}
}

/*
	-Ne mogu izvodi i max, min, abs, unarnih + i -, %, ^
	-potpisi funkcija:
		min(A,B)
		max(A,B)
		abs(A)
	-Ne mogu se ugnjezdavati max, min i abs
*/

