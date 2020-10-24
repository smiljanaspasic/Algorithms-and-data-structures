#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#define MAX 700000
#define c 2
using namespace std;

int konverzijaosnove(string s,int n) {
	int q=13;
	int mul = 0;
	int num = 0;
	int sum = 0;
	for (int i = s.length()-1; i>=0 ; i--) {
		sum=sum + pow(q, num) * (int)s[i];
		num++;
	}
	sum=sum % n;
	if (sum < 0) sum = 0 - sum;
	return sum;
}

class Info {
private:
	string orglang, orgtitle, release, revenue, runtime;
public:
	Info(string o=" ", string o2="", string r="", string r2="", string runt="") {
		orglang = o;orgtitle=o2; release = r; revenue = r2; runtime = runt;
	}
	string dohvatikey() const { return orgtitle; }
	void setkey(string m) { orgtitle = m; }
	string dohvatisadrzaj() const { return orglang + " " + release + " " + revenue + " " + runtime; }
};
class AddressFunction {
	virtual int getAddress(string key, int matadr, int pokusaj, int n) = 0;
};

class QuadriaticHashing : public AddressFunction {
public:

	int getAddress(string key, int matadr, int pokusaj, int n) override {
		return (matadr + c * pokusaj*pokusaj) % n;
	}
};
class HashTable {
private:
	Info** niz;
	int n;
	QuadriaticHashing a;
	int pristupusp, pristupne;
	int numofkeysnotfound;
	int x, last;
public:
	HashTable(int nn, QuadriaticHashing ff) {
		niz = new Info*[n = nn];
		for (int i = 0; i < n; i++) { niz[i] = 0; }
		a = ff;
		resetStatistics();
	}
	string findKey(string key) {
		int tryy = 1;
		bool flag = false;
		x = konverzijaosnove(key, n);
		last = x;
		if (niz[x] == 0) { pristupne++; last = x; numofkeysnotfound++; return "0"; }
		else if (niz[x]->dohvatikey() == key) { pristupusp++;  return niz[x]->dohvatisadrzaj(); }
		else {
			if (niz[x]->dohvatikey() == "DELETED") last = x;
			pristupne++; pristupusp++;
			int j = a.getAddress(key, x, tryy, n);
			if (niz[last]->dohvatikey() != "DELETED") { last = j; }
			while (j !=x) {
				if (niz[j] == 0 ) { 
					if (last != j) {
						if (niz[last]->dohvatikey() != "DELETED")  last = j;
					}
					break; }
				else
				{
					if (niz[j]->dohvatikey() == key) { flag = true; x = j; break; }
					else {
						pristupusp++; pristupne++;
						tryy++;
						j = a.getAddress(key, j, tryy, n);
						if (niz[last]->dohvatikey() != "DELETED") { last = j; }
					}
				}
			}
			
			if (flag == false) {
				pristupusp = pristupusp - tryy;
				pristupne++;
				numofkeysnotfound++;
				return "0";
			}
			else {
				pristupne = pristupne - tryy;
				pristupusp++;   return niz[x]->dohvatisadrzaj();
			}
		
	}
}
	
	bool insertKey(string key, Info* in) {
		if (findKey(key) != "0") return false;
		else {
			if (niz[last] == 0) {
				niz[last] = in;
				return true;
			}
			else {
				if (niz[last]->dohvatikey() == "DELETED") {
					niz[last] = in;
					return true;
				}
				else return false;
			}

		}
		
	}
	bool deleteKey(string key) {
		if (findKey(key) == "0") return false;
		else {
			niz[x]->setkey("DELETED"); return true;
		}
	}
	void clear() {
		for (int i = 0; i < n; i++) { niz[i] = 0; }
	}
	~HashTable() { clear(); delete[] niz; }
	int keycount() {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (niz[i] != 0) {
				if (niz[i]->dohvatikey() != "DELETED") {
					cnt++;
				}
			}
			
		}
		return cnt;
	}
	int tableSize() const { return n; }
	double fillRatio() { return (double)keycount() /(double)tableSize(); }
	void resetStatistics() {
		pristupusp = 0; pristupne = 0;  numofkeysnotfound = 0;
	}
	int avgAccessSuccess() {
		return pristupusp /keycount();
	}
	int avgAccessUnsuccess() { return pristupne /numofkeysnotfound; }
	double avgUnsuccessEst() {
		double p;
		if (fillRatio() != 1) {
			 p = 1.00 - fillRatio();
			p = 1.00 / p;
		}
		else p = 0;
		return p;
	}
	friend ostream& operator<<(ostream& os, const HashTable& h) {
		for (int i = 0; i < h.n; i++) {
			if (h.niz[i] == 0) os << "EMPTY" << endl;
			else {
				if (h.niz[i]->dohvatikey() == "DELETED") os << h.niz[i]->dohvatikey() << endl;
				else os << h.niz[i]->dohvatikey() << " " << h.niz[i]->dohvatisadrzaj() << endl;
			}
		}
		return os;
	}

};
void funkcijazatestiranje(HashTable& h,string* ispniz,Info* nizo,int size1,int size2) {
	for (int i = 0; i < size1; i++) {
		h.insertKey(nizo[i].dohvatikey(),&nizo[i]);
	}
	h.resetStatistics();
	for (int i = 0; i < size2; i++) {
		h.findKey(ispniz[i]);
	}
	cout << h.avgAccessSuccess() << endl;
	cout << h.avgAccessUnsuccess() << endl;
	cout << h.avgUnsuccessEst() << endl;
}


int main() {
	string* ispitniniz = new string[MAX];
	Info* nizic = new Info[MAX];
	Info* noviniz = new Info[MAX];
	int n = -1;
	int n2 = 0;
	int vel;
	string jezik;
	string naslov;
	string godina;
	string prihod;
	string vremetrajanja;

	QuadriaticHashing d;
	cout << "Unesite velicinu tabele" << endl;
	cin >> vel;
	HashTable tabela(vel, d);
	int radi = 1;
	int izbor;
	while (radi) {
		
		cout << "Izbor?\n"
			"2. Ucitavanje podataka za test i pozivanje funkcije testiranja\n"
			"3. Trazi kljuc\n"
			"4. Dodaj kljuc\n"
			"5. Izbrisi kljuc\n"
			"6. Prosecan uspesni broj pristupa\n"
			"7. Prosecan neuspesni broj pristupa\n"
			"8. Prosecan neuspesni procenjeni broj pristupa\n"
			"9. Resetuj statistiku\n"
			"10. Isprazni tabelu\n"
			"11. Broj umetnutih kljuceva u tabeli\n"
			"12. Velicina tabele\n"
			"13. Ispis tabele\n"
			"14. Stepen popunjenosti\n"
			"15. Prekid programa\n"
			<< endl;
		cin >> izbor;
		switch (izbor)
		{

		case 2: {
			ifstream dat;
			dat.open("tmdb_movies.csv");
			if (!dat.is_open()) cout << "Greska";
			else {
				while (!dat.eof()) {

					getline(dat, jezik, ',');
					getline(dat, naslov, ',');
					getline(dat, godina, ',');
					getline(dat, prihod, ',');
					getline(dat, vremetrajanja, '\n');
					if (n >= 0) {
						nizic[n] = Info(jezik, naslov, godina, prihod, vremetrajanja);
					}
					n++;

				}
				ifstream dat2;
				dat2.open("movies_search_1.txt");
				if (!dat.is_open()) cout << "Greska";
				else {
					while (!dat2.eof()) {
						getline(dat2, naslov, '\n');
						ispitniniz[n2++] = naslov;
					}
				}
			}
		funkcijazatestiranje(tabela, ispitniniz, nizic, n, n2);
		break;
		}
		case 3:
		{ cout << "Napisi naslov filma koji zelis da nadjes" << endl;
		cin.get();
		getline(cin, naslov);
		cout << tabela.findKey(naslov) << endl;
		break;
		}
		case 4: {
		
			ifstream dato;
			cout << "Unesi ime datoteke" << endl;
			string ime;
			cin >> ime;
			n = 0;
			dato.open(ime);
			if (!dato.is_open()) cout << "Greska";
			else {
				while (!dato.eof()) {

					getline(dato, jezik, ',');
					getline(dato, naslov, ',');
					getline(dato, godina, ',');
					getline(dato, prihod, ',');
					getline(dato, vremetrajanja, '\n');
					noviniz[n] = Info(jezik, naslov, godina, prihod, vremetrajanja);
					n++;

				}
				for (int i = 0; i < n; i++) {
					tabela.insertKey(noviniz[i].dohvatikey(), &noviniz[i]);
				}
				break;
			} }
		case 5:
		{
			cout << "Unesi naslov filma koji zelis da izbrises" << endl;
			cin.get();
			getline(cin, naslov);
			tabela.deleteKey(naslov);
			break;
		}
		case 6: {
			cout << tabela.avgAccessSuccess() << endl;
			break;
		}
		case 7: {
			cout << tabela.avgAccessUnsuccess() << endl;
			break;
		}
		case 8: {
			cout << tabela.avgUnsuccessEst() << endl;
			break;
		}
		case 9: {
			tabela.resetStatistics();
			break;
		}
		case 10: {
			tabela.clear();
			break;
		}
		case 11:
		{
			cout << tabela.keycount() << endl;
			break;
		}

		case 12: {
			cout << tabela.tableSize() << endl;
			break;
		}
		case 13: {
			cout << tabela;
			break;
		}
		case 14: {
			cout << tabela.fillRatio() << endl;
			break;
		}
		case 15: {
			radi = 0;
			break; }
		}
	}
}