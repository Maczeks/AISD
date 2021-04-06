#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int MorrisPratt(string s, string w)
{
	int i;
	int N, M;
	N = s.length();
	M = w.length();
	int* PI;
	PI = new int[M+1];

	int b = -1;
	PI[0] = -1;

	for (i = 1; i <= M; i++)
	{
		while ((b > -1) && w[b] != w[i - 1]) 
		{
			b = PI[b];
		}
			PI[i] = ++b;
	}
	int pos = 0;
	b = 0;
	for (i = 0; i < N; i++)
	{
		while ((b > -1) && (w[b] != s[i]))
		{
			b = PI[b];

		}
		if (++b == M)
		{
			while (pos < i - b + 1)
			{
				pos++;
			}
			b = PI[b];
		}
	}

	return pos;
}

void ELSET_NSET(string s)
{
	string w1 = "Nset, nset=";
	string w2 = "Elset, elset=";
	int pozycja1, pozycja2;

	pozycja1 = MorrisPratt(s,w1);
	int l_w1;
	l_w1 = w1.length();
	if (pozycja1 != -1 && pozycja1 != 0) {

		cout << "Nazwa NSET: ";
		for (int i = 0; i < s.length(); i++) {
			if (i > l_w1) {
				cout << s[i];
			}
		}
		cout << endl;
	}

	pozycja2 = MorrisPratt(s, w2);
	int l_w2;
	l_w2 = w2.length();
	if (pozycja2 != -1 && pozycja2 != 0) {

		cout << "Nazwa ELSET: ";
		for (int i = 0; i < s.length(); i++) {
			if (i > l_w2) {
				cout << s[i];
			}
		}
		cout << endl;
	}
}

int main()
{
	string s;
	string w;
	ifstream plik("Job-case1.inp");
	int menu;
	bool tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	cout << "Ktore zadanie Cie interesuje (1-5): " << endl;
	cin >> menu;
	system("cls");
	switch (menu)
	{
	case 1:
		if (plik.is_open())
		{
			w = "Part, name=";
			int l_w;
			l_w = w.length(); 
			while (getline(plik, s))
			{
				//cout << "S: " << s.length() << endl;
				int pozycja;
				pozycja = MorrisPratt(s, w);
				if (pozycja != -1 && pozycja != 0) {
					
					cout << "Nazwa czesci: ";
					for (int i = 0; i < s.length(); i++) {
						if (i > l_w) {
							cout << s[i];
						}
					}
					cout << endl;				
				}
			}
		}
		else {
			cout << "Nie mozna otworzyc pliku" << endl;
		}
		plik.close();
		break;

	case 2:
		if (plik.is_open())
		{
			while (getline(plik, s))
			{
				ELSET_NSET(s);
			}
		}
		else {
			cout << "Nie mozna otworzyc pliku" << endl;
		}
		plik.close();
		break;

	case 3:
		if (plik.is_open())
		{
			string w = "Element, type=";
			int l_w;
			l_w = w.length();
			while (getline(plik, s))
			{
				//cout << "S: " << s.length() << endl;
				int pozycja;
				pozycja = MorrisPratt(s,w);
				if (pozycja != -1 && pozycja != 0) {
					cout << "Typ elementu: ";
					for (int i = 0; i < s.length(); i++) {
						if (i > l_w) {
							cout << s[i];
						}
					}
					cout << endl;
				}
			}
		}
		else {
			cout << "Nie mozna otworzyc pliku" << endl;
		}
		plik.close();
		break;

	case 4:
		if (plik.is_open())
		{
			while (getline(plik, s))
			{
				string w1 = "Material, name=";
				string w2 = "Conductivity";
				string w3 = "Density";
				string w4 = "Specific Heat";

				int pozycja1, pozycja2, pozycja3, pozycja4;

				pozycja1 = MorrisPratt(s, w1);
				int l_w1;
				l_w1 = w1.length();
				if (pozycja1 != -1 && pozycja1 != 0) {

					cout << "Nazwa materialu: ";
					for (int i = 0; i < s.length(); i++) {
						if (i > l_w1) {
							cout << s[i];
						}
					}
					cout << endl;
				}

				pozycja2 = MorrisPratt(s, w2);
				int l_w2;
				l_w2 = w2.length();
				if (pozycja2 != -1 && pozycja2 != 0) {
					for (int i = 0; i <= l_w2; i++) {
						cout << s[i];
					}
					cout << ": ";
					cout << endl;
					getline(plik, s);
					cout << s << endl;
				}

				pozycja3 = MorrisPratt(s, w3);
				int l_w3;
				l_w3 = w3.length();
				if (pozycja3 != -1 && pozycja3 != 0) {
					for (int i = 0; i <= l_w3; i++) {
						cout << s[i];
					}
					cout << ": ";
					cout << endl;
					getline(plik, s);
					cout << s << endl;
				}

				pozycja4 = MorrisPratt(s, w4);
				int l_w4;
				l_w4 = w4.length();
				if (pozycja4 != -1 && pozycja4 != 0) {
					for (int i = 0; i <= l_w4; i++) {
						cout << s[i];
					}
					cout << ": ";
					cout << endl;
					getline(plik, s);
					cout << " " << s << endl;
					cout << endl;
				}
			}
		}
		else {
			cout << "Nie mozna otworzyc pliku" << endl;
		}
		plik.close();
		break;

	case 5:
		if (plik.is_open())
		{
				string w1 = "* STEP";
				string w2 = "* INTERACTIONS";
				string w3 = "* OUTPUT REQUESTS";
				string w4 = "* FIELD OUTPUT";
				string w5 = "* HISTORY OUTPUT";
				string w6 = "End Step";

				int pozycja1, pozycja2, pozycja3, pozycja4, pozycja5, pozycja6;
				bool tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
				bool tmp = false;
				tmp1 = false;
				tmp2 = false;
				tmp3 = false;
				tmp4 = false;
				tmp5 = false;
				tmp6 = false;

				while (getline(plik, s)) {
					pozycja1 = MorrisPratt(s, w1);
					if (pozycja1 > 0) {
						tmp1 = true;
					}
					pozycja2 = MorrisPratt(s, w2);
					if (pozycja2 > 0) {
						tmp2 = true;
					}
					pozycja3 = MorrisPratt(s, w3);
					if (pozycja3 > 0) {
						tmp3 = true;
					}
					pozycja4 = MorrisPratt(s, w4);
					if (pozycja4 > 0) {
						tmp4 = true;
					}
					pozycja5 = MorrisPratt(s, w5);
					if (pozycja5 > 0) {
						tmp5 = true;
					}
					pozycja6 = MorrisPratt(s, w6);
					if (pozycja6 > 0) {
						tmp6 = true;
					}
				}

			if (tmp1 == true && tmp2==true && tmp3 == true && tmp4 == true && tmp5 == true && tmp6 == true) {
				cout << "Step zostal zdefiniowany poprawnie!" << endl;
			} 
			else {
				cout << "Step zle zdefiniowany!" << endl;
			}
		}
		else {
			cout << "Nie mozna otworzyc pliku!" << endl;
		}
		plik.close();
		break;
	default: 
		cout << "Zly numer zadania!" << endl;
	}
	system("pause");
	return 0;
}