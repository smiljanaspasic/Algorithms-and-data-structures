#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class BTreeNode
{
	int *keys;  // niz kljuceva 
	int t;      //min br kljuceva 
	BTreeNode **Child; // niz pokazivaca na decu
	int n;     // trenutni  br kljuceva
	bool listic; // list ili nije
public:
	BTreeNode(int t1, bool list1) {
		t = t1;
		listic = list1;
		keys = new int[2 * t - 1];
		Child = new BTreeNode *[2 * t];
		n = 0;
	}
	friend class BTree;
	void splitChild(int i, BTreeNode *y) {
		BTreeNode *z = new BTreeNode(y->t, y->listic);
		z->n = t - 1;

		for (int j = 0; j < t - 1; j++)
			z->keys[j] = y->keys[j + t];

		if (y->listic == false)
		{
			for (int j = 0; j < t; j++)
				z->Child[j] = y->Child[j + t];
		}

		y->n = t - 1;

		for (int j = n; j >= i + 1; j--)
			Child[j + 1] = Child[j];

		Child[i + 1] = z;


		for (int j = n - 1; j >= i; j--)
			keys[j + 1] = keys[j];


		keys[i] = y->keys[t - 1];


		n = n + 1;
	}

	void insertNonFull(int k)
	{

		int i = n - 1;
		if (listic == true)
		{
			//trazenje pozicije cvora i pomeranje drugih kljuceva
			while (i >= 0 && keys[i] > k)
			{
				keys[i + 1] = keys[i];
				i--;
			}

			keys[i + 1] = k;
			n = n + 1;
		}
		else
		{
			// Trazenje deteta u kome ce biti novi kljuc 
			while (i >= 0 && keys[i] > k)
				i--;

			if (Child[i + 1]->n == 2 * t - 1)
			{

				splitChild(i + 1, Child[i + 1]);

				if (keys[i + 1] < k)
					i++;
			}
			Child[i + 1]->insertNonFull(k);
		}
	}

		
		
		void remove(int k) {
			int xx = TraziKlj(k);

			
			if (xx < n && keys[xx] == k)
			{

				
				if (listic)
					izbaciizlista(xx);
				else
					removeFromNonLeaf(xx);
			}
			else
			{

				
				if (listic)
				{
					cout << "Kljuc " << k << " ne postoji u stablu\n";
					return;
				}

				
				bool flag = ((xx == n) ? true : false);

				
				if (Child[xx]->n < t)
					fill(xx);

				
				if (flag && xx > n)
					Child[xx - 1]->remove(k);
				else
					Child[xx]->remove(k);
			}
			return;
		}

		
		void izbaciizlista(int idx) {

			
			for (int i = idx + 1; i < n; ++i)
				keys[i - 1] = keys[i];

			
			n--;

			return;
		}

		
		void removeFromNonLeaf(int idx) {

			int k = keys[idx];

			
			if (Child[idx]->n >= t)
			{
				int pred = getPred(idx);
				keys[idx] = pred;
				Child[idx]->remove(pred);
			}

			
			else if (Child[idx + 1]->n >= t)
			{
				int succ = getSucc(idx);
				keys[idx] = succ;
				Child[idx + 1]->remove(succ);
			}

			
			else
			{
				spajanje(idx);
				Child[idx]->remove(k);
			}
			return;
		}

		
		int getPred(int idx) {
			
			BTreeNode *cur = Child[idx];
			while (!cur->listic)
				cur = cur->Child[cur->n];

			
			return cur->keys[cur->n - 1];
		}

		
		int getSucc(int idx) {

			BTreeNode *cur = Child[idx + 1];
			while (!cur->listic)
				cur = cur->Child[0];

			 
			return cur->keys[0];
		}

		
		void fill(int idx) {

			
			if (idx != 0 && Child[idx - 1]->n >= t)
				pozajmiodPrethodnog(idx);

			
			else if (idx != n && Child[idx + 1]->n >= t)
				pozajmiodSledbenika(idx);

			
			else
			{
				if (idx != n)
					spajanje(idx);
				else
					spajanje(idx - 1);
			}
			return;
		}

		
		void pozajmiodPrethodnog(int idx) {

			BTreeNode *child = Child[idx];
			BTreeNode *sibling = Child[idx - 1];

			
			for (int i = child->n - 1; i >= 0; --i)
				child->keys[i + 1] = child->keys[i];

			
			if (!child->listic)
			{
				for (int i = child->n; i >= 0; --i)
					child->Child[i + 1] = child->Child[i];
			}

			
			child->keys[0] = keys[idx - 1];

			
			if (!child->listic)
				child->Child[0] = sibling->Child[sibling->n];

		
			keys[idx - 1] = sibling->keys[sibling->n - 1];

			child->n += 1;
			sibling->n -= 1;

			return;
		}


		
		void pozajmiodSledbenika(int idx) {

			BTreeNode *child = Child[idx];
			BTreeNode *sibling = Child[idx + 1];

			
			child->keys[(child->n)] = keys[idx];

			
			if (!(child->listic))
				child->Child[(child->n) + 1] = sibling->Child[0];

			
			keys[idx] = sibling->keys[0];

			
			for (int i = 1; i < sibling->n; ++i)
				sibling->keys[i - 1] = sibling->keys[i];

			 
			if (!sibling->listic)
			{
				for (int i = 1; i <= sibling->n; ++i)
					sibling->Child[i - 1] = sibling->Child[i];
			}

			
			child->n += 1;
			sibling->n -= 1;

			return;
		}

		
		void spajanje(int idx) {
			BTreeNode *child = Child[idx];
			BTreeNode *sibling = Child[idx + 1];

			
			child->keys[t - 1] = keys[idx];

			
			for (int i = 0; i < sibling->n; ++i)
				child->keys[i + t] = sibling->keys[i];

			
			if (!child->listic)
			{
				for (int i = 0; i <= sibling->n; ++i)
					child->Child[i + t] = sibling->Child[i];
			}

			
			for (int i = idx + 1; i < n; ++i)
				keys[i - 1] = keys[i];

			
			for (int i = idx + 2; i <= n; ++i)
				Child[i - 1] = Child[i];

			
			child->n += sibling->n + 1;
			n--;

			
			delete(sibling);
			return;
		}
	
		int TraziKlj(int k) {
			int idx = 0;
			while (idx < n && keys[idx] < k)
				++idx;
			return idx;
		}
	
	void traverse(int tab)
	{
		int i;
		string s;

		 
		for (int j = 0; j < tab; j++) {
			s += '\t';
		}
		for (i = 0; i < n; i++) {

			
			if (listic == false)
				Child[i]->traverse(tab + 1);
			cout << s << keys[i] << endl;
		}

		
		if (listic == false) {
			Child[i]->traverse(tab + 1);
		}
	}

};

	
	class BTree
	{
		BTreeNode *root;
		int t;  // Minimalni stepen
	public:

		BTree(int tt)
		{
			root = NULL;  t = tt;
		}

		void insert(int k)
		{
			
			if (root == NULL)
			{
				 
				root = new BTreeNode(t, true);
				root->keys[0] = k;  
				root->n = 1;  
			}
			else 
			{
			
				if (root->n == 2 * t - 1)
				{
				
					BTreeNode *s = new BTreeNode(t, false);

					 
					s->Child[0] = root;

			
					s->splitChild(0, root);

					
					int i = 0;
					if (s->keys[0] < k)
						i++;
					s->Child[i]->insertNonFull(k);

					
					root = s;
				}
				else
					root->insertNonFull(k);
			}
		}

		
		void display() {
	root->traverse(0);
		}
		void remove(int k) {
			if (!root)
			{
				cout << "Stablo je prazno\n";
				return;
			}

			
			root->remove(k);

			
			if (root->n == 0)
			{
				BTreeNode *tmp = root;
				if (root->listic)
					root = NULL;
				else
					root = root->Child[0];

				 
				delete tmp;
			}
			return;
		}
	
	};

	int main() {
		int p=0;
		int t = 0;
		BTree tree(t);
		char c[30];
		string line;
		int niz[1000];
		ifstream dat;
		dat.open("numbers_10_unique.txt");
		if (!dat.is_open()) cout << "Nesto";
		int i = 0;
		int k;
		int j = 0;
		while (!dat.eof())
		{
			dat >> c;
			while (c[i] != 0)
			{
				line += c[i++];
			}
			if (line != "") {
				niz[j++] = stoi(line);
				line = "";
				i = 0;
			}
		}
		dat.close();
		int radi = 1;
		int izbor;
		while (radi) {
			cout << "Izbor?\n"
				"1. Stvaranje stabla\n"
				"2. Brisanje stabla\n"
				"3. Umetni u stablo.\n"
				"4. Izbrisi iz stabla\n"
				"5. Ispis stabla\n"
				"6. Prekid programa\n"
				<< endl;
			cin >> izbor;
			switch (izbor)
			{
			case 1:
			{	int red;
			p = 1;
			cout << "Unesite red stabla" << endl;
			cin >> red;
			if (red < 3 || red>10) cout << "Greska"; 
			int	t = red / 2 + 1;
			tree =BTree(t);
			for (int i = 0; i < j; i++) {
				tree.insert(niz[i]);
			}

			break;
			}
			case 2:
				
			{	if (p==0) cout << "Stablo je prazno" << endl;
			else {

				for (int i = 0; i < j; i++) {
					tree.remove(niz[i]);
				}
			}
			p = 0;
			break; }
			case 3: {
				cout << "Kljuc za dodavanje?" << endl;
				cin >> k;
				niz[j++] = k;
				tree.insert(k);
				break; }
			case 4: {
				cout << "Kljuc za brisanje" << endl;
				cin >> k;
				tree.remove(k);
				break; }
			case 5: {
				if (p == 0) cout << "Stablo je prazno" << endl;
				else
					tree.display();
				break; }
			case 6: {
				radi = 0;
				break; }
			}
		}
	}
