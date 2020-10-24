#include <stdio.h>
#include <stdlib.h>

#define initial 1
#define waiting 2
#define visited 3
#define MAX 20
#define true 1
#define false 0

int broj_cvorova, broj_grana;
int state[MAX];

typedef struct sGraf {
	int grane[100];
	int index[100];
	int weight[100];
} Graf;





Graf ucitaj(int bc, int bg){
	int bsc, sused, tezina;
	Graf igraf;
	int i, j, g = 0;
	igraf.index[0] = 0;
	// trebaju mi 2 niza : grane i indeksi
	// treba da unesem susedne cvorove     

	for (i = 0; i<bc; i++)
	{
		printf(" broj susednih cvorova cvora %d?", i);
		scanf("%d", &bsc);
		igraf.index[i + 1] = igraf.index[i] + bsc;
	}
	for (i = 0; i<bc; i++) printf("%d\t", igraf.index[i]);

	for (i = 0; i<bc; i++)
	{
		printf("\n\n CVOR %d:\n", i);
		for (j = 0; j<igraf.index[i + 1] - igraf.index[i]; j++)
		{
			printf(" %d. sused cvora %d?", j + 1, i);
			scanf("%d", &sused);
			igraf.grane[g] = sused;
			printf("tezinski faktor?");
			scanf("%d", &tezina);
			igraf.weight[g] = tezina;
			g++;
		}
	}

	printf("grane\n");
	for (g = 0; g<bg; g++) printf("%d\t", igraf.grane[g]);
	printf("\n\n");
	printf("tezine\n");
	for (g = 0; g<bg; g++) printf("%d\t", igraf.weight[g]);
	return igraf;
} // end ucitaj    


pisi(Graf igraf){
	int g, i;
	printf(" Niz Edges\n");
	for (g = 0; g<broj_grana; g++) printf("%d\t", igraf.grane[g]);
	printf("\n Niz Indices\n");
	for (i = 0; i<broj_cvorova; i++) printf("%d\t", igraf.index[i]);

} // end pisi




void BFS(Graf igraf, int v){

	int isEmpty_queue, start, sused, i, j;
	int Q[MAX], front = -1, rear = -1;

	//na pocetku svi su neposeceni     
	//     for(i=0; i<broj_cvorova; i++) 
	//        state[i] = initial;    

	// ubaci izabrani cvor v u queue i promeni mu status u waiting
	//  insert_queue(Q,v);
	if (rear == MAX - 1)
		printf("Queue Overflow\n");
	else
	{
		if (front == -1)
			front = 0;
		rear = rear + 1;
		Q[rear] = v;
	}
	// end insert queue


	state[v] = waiting;
	// printf("Upravo ubacio pocetni cvor u Q\n"); 


	if (front == -1 || front > rear)
		isEmpty_queue = 1;
	else
		isEmpty_queue = 0;


	while (!isEmpty_queue)
	{
		if (front == -1 || front > rear)
		{
			printf("Queue Underflow\n");
			exit(1);
		}
		// citaj cvor iz queuq i brisi ga    
		v = Q[front];
		front = front + 1;

		// kazi da je posecen
		// printf("upravo sam posetio cvor %d i zato ga izbrisao ga iz Q\n ",v);
		printf("%d\t", v);
		state[v] = visited;

		// sve cvorove sa kojima on ima grane stavi u queue        

		//  printf("\n\n analiziram CVOR %d:\n", v);
		start = igraf.index[v];
		//    printf("njegov pocetni indeks je %d\n",start);  
		for (j = start; j<start + igraf.index[v + 1] - igraf.index[v]; j++)
		{ //printf(" sused cvora %d je %d\n",v,igraf.grane[j]);
			sused = igraf.grane[j];
			if (state[sused] == initial) // stavi ga u Q
			{
				if (rear == MAX - 1)
					printf("Queue Overflow\n");
				else
				{
					if (front == -1)
						front = 0;
					rear = rear + 1;
					Q[rear] = sused;
					state[sused] = waiting;
					//             printf(" posto sused %d analiziranog cvora %d nije posecen stavljam ga u Q\n", sused,v);
				}// end else


			}// end if sused nije posecen     

		} // end for za tekuci cvor



		//    printf("\n");
		// ponovo provera da li je prazan
		if (front == -1 || front > rear)
			isEmpty_queue = 1;
		else
			isEmpty_queue = 0;


	} // end while
	//   printf("stanje posle obilaska\n");
	//   printf("povezanu komponentu cine cvorovi:\n");
	//   for(i=0; i<broj_cvorova; i++) 
	//printf("state[%d]=%d\n",i,state[i]);    
	//     if (state[i]==visited) printf("%d\t",i);  
	//     putchar('\n');

} //end BFS


//****************************************************
povezane_komponente(Graf igraf){

	int i, n_cc = 0;

	//na pocetku svi su neposeceni     
	for (i = 0; i<broj_cvorova; i++)
		state[i] = initial;

	for (i = 0; i<broj_cvorova; i++){
		if (state[i] == initial)
		{
			n_cc = n_cc + 1;
			printf("\n\n\n\n");
			printf("%d. povezanu komponentu cine cvorovi:\n", n_cc);
			printf("\n");
			BFS(igraf, i);

		}//end if 
	}//end for
	printf("\n\n");
	printf("Broj povezanih komponenti: %d\n", n_cc);
} //end povezane_komponente 


//**********************************************************************
obuhvatno_stablo(Graf igraf){
	int isEmpty_queue, start, sused, i, j, g, v;
	int Q[MAX], front = -1, rear = -1;
	Graf ostablo;
	int Newadr = 0;

	//na pocetku svi su cvorovi neposeceni     
	for (i = 0; i<broj_cvorova; i++)
		state[i] = initial;

	printf("Unesi poctni cvor za obuhvatno stablo: \n");
	scanf("%d", &v);

	// ubaci izabrani pocetni cvor v u Q i promeni mu status u waiting
	//  insert_queue(Q,v);
	if (rear == MAX - 1)
		printf("Queue Overflow\n");
	else
	{
		if (front == -1)
			front = 0;
		rear = rear + 1;
		Q[rear] = v;
	}
	state[v] = waiting;
	printf("Upravo ubacio pocetni cvor u Q\n");

	//pocetno ispitivanje da li je Q prazan
	if (front == -1 || front > rear)
		isEmpty_queue = 1;
	else
		isEmpty_queue = 0;

	while (!isEmpty_queue)
	{
		if (front == -1 || front > rear)
		{
			printf("Queue Underflow\n");
			exit(1);
		}
		// citaj cvor iz Q i brisi ga    
		v = Q[front];
		front = front + 1;

		// Oznaci da je visited
		printf("upravo sam posetio cvor %d i zato ga izbrisao ga iz Q\n ", v);
		printf("%d\t", v);
		state[v] = visited;



		// trazim sve cvorove sa kojima on ima grane i stavlam  u Q ako nije vec posecen        

		printf("\n\n analiziram CVOR %d:\n", v);
		start = igraf.index[v];
		ostablo.index[v] = Newadr;
		printf("njegov pocetni indeks je %d\n", start);
		for (j = start; j<start + igraf.index[v + 1] - igraf.index[v]; j++)
		{
			printf(" sused cvora %d je %d\n", v, igraf.grane[j]);
			sused = igraf.grane[j];
			if (state[sused] == initial) // stavi ga u Q
			{
				if (rear == MAX - 1)
					printf("Queue Overflow\n");
				else
				{
					if (front == -1)
						front = 0;
					rear = rear + 1;
					Q[rear] = sused;
					state[sused] = waiting;
					printf(" posto sused %d analiziranog cvora %d nije posecen stavljam ga u Q\n", sused, v);
					// i definisem granu izmedju ispitivanog cvora (v) i suseda (sused)

					ostablo.grane[Newadr] = sused;
					Newadr++;

				}// end else


			}// end if sused nije posecen     

		} // end for za tekuci cvor


		// ponovo provera da li je prazan
		if (front == -1 || front > rear)
			isEmpty_queue = 1;
		else
			isEmpty_queue = 0;


	} // end while

	printf("Novi graf izgleda ovako\n");
	printf(" NOVI Niz Edges\n");
	for (g = 0; g<Newadr; g++) printf("%d\t", ostablo.grane[g]);
	printf("\n Novi Niz Indices\n");
	for (i = 0; i<broj_cvorova; i++) printf("%d\t", ostablo.index[i]);



}// end obuhvatno stablo


prim_mst(Graf igraf){

	int key[broj_cvorova]; // tezina cvora
	_Bool mstSet[broj_cvorova]; //niz cvorova koji su ukljuceni u MST
	int count, i, j; // brojaci
	int parent[broj_cvorova]; // niz koji cuva krajnji MST
	int start, sused, tezina;

	//printf("Unesi poctni cvor za MST: \n");
	//        scanf("%d", &v);



	//cvor v ce biti root MST



	// Initialize all keys as INFINITE
	for (i = 0; i < broj_cvorova; i++)
		key[i] = 9999, mstSet[i] = false;

	// Always include first 1st node in MST.
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST 

	for (count = 0; count < broj_cvorova - 1; count++)
	{
		// Pick thd minimum key vertex from the set of vertices
		// not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent nodes of
		// the picked nodes. Consider only those vertices which are not yet
		// included in MST
		//        for (v = 0; v < broj_cvorova; v++)

		// graph[u][v] is non zero only for adjacent vertices of m
		// mstSet[v] is false for vertices not yet included in MST
		// Update the key only if graph[u][v] is smaller than key[v]


		printf("\n\n analiziram CVOR %d:\n", u);
		start = igraf.index[u];
		printf("njegov pocetni indeks je %d\n", start);
		for (j = start; j<start + igraf.index[u + 1] - igraf.index[u]; j++)
		{
			printf(" sused cvora %d je %d\n", u, igraf.grane[j]);
			sused = igraf.grane[j];
			tezina = igraf.weight[j];
			printf(" tezina grane izmedju cvora %d  i suseda %d je %d\n", u, sused, tezina);

			if (mstSet[sused] == false && tezina <  key[sused])
				parent[sused] = u, key[sused] = tezina;

		} //end for

	}
	printf("Edge   Weight\n");
	for (i = 1; i < broj_cvorova; i++)
		printf("%d - %d    %d \n", parent[i], i, key[i]);



}//end prim

int minKey(int key[], _Bool mstSet[])
{
	int v;
	// Initialize min value
	int min = 9999, min_index;

	for (v = 0; v < broj_cvorova; v++)
	if (mstSet[v] == false && key[v] < min)
		min = key[v], min_index = v;

	return min_index;
}











int main() {
	Graf mojgraf;
	int izbor, v, i,broj_cvorova,broj_grana;
	_Bool kraj = 0;

	while (!kraj) {
		printf("\n   1.Ucitavanje grafa\n"
			"   2.Ispisivanje grafa\n"
			"   3.Obilazak grafa po sirini\n"
			"   4.Odredjivanje poveznih komponenti\n"
			"   5.Obuhvatno stablo\n"
			"   6.Minimalno obuhvatno stablo-Primov\n"
			"   7.EMPTY\n"
			"   8.EMPTY\n"
			"   9.EMPTY\n"
			"   0.Zavrsetak rada\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("Broj cvorova?");
			scanf("%d", &broj_cvorova);
			// dodaj ispitivanje
			printf("Broj grana?");
			scanf("%d", &broj_grana);

			mojgraf = ucitaj(broj_cvorova, broj_grana);
			break;

		case 2:
			pisi(mojgraf); putchar('\n'); break;



		case 3: //BFS
			for (i = 0; i<broj_cvorova; i++)
				state[i] = initial;
			printf("Unesi poctni cvor za BFS: \n");
			scanf("%d", &v);
			BFS(mojgraf, v);
			break;

		case 4: // odredjivanje povezanih komponenti
			povezane_komponente(mojgraf);
			break;

		case 5: //odredjivanje obuhvatnog stabla
			obuhvatno_stablo(mojgraf); break;

		case 6: //odredjivanje minimum cost spanning tree
			prim_mst(mojgraf); break;


		case 0:
			kraj = 1;
			break;
		default:
			printf("Pogresan izbor!!");
		}
	}
	return 0;
}