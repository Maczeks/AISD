#include <iostream>

using namespace std;

struct s_list
{
    s_list* next;
    int v, waga;
};

string names[9] = { "Wilno","Uciana","Poniewiez","Szawle","Bustynga","Klajpeda","Taurogi","Kowno","Mariampol"};

const int MAXINT = INT_MAX;

int i, j, m, n, start, u, x, y, w, s_wsk, *d, *p, *S;
bool* Q_S;
s_list** graf;
s_list* tmp, * tmp2;

bool BF(int v)
{
    int i, x;
    bool test;
    s_list* tmp;

    d[v] = 0;
    for (i = 1; i < n; i++)
    {
        test = true;
        for (x = 0; x < n; x++)
            for (tmp = graf[x]; tmp; tmp = tmp->next)
                if (d[tmp->v] > d[x] + tmp->waga)
                {
                    test = false;
                    d[tmp->v] = d[x] + tmp->waga;
                    p[tmp->v] = x;
                }
        if (test) return true;
    }
    return true;
}

int main()
{
    int choice;
   
    cout << "Wpisz wierzcholek startowy, liczbe wierzcholkow i krawedzi:" << endl;
    cin >> start >> n >> m;
    
    system("cls");

    cout << " --------------------------\n"
        "           MENU\n"
        " --------------------------\n"
        " 1  =  Algorytm Dijkstry   \n"
        " 2  =  Algorytm Bellmana-Forda  \n"
        " --------------------------\n"
        "Wpisz numer ktory Cie interesuje: ";
    cin >> choice;

    system("cls");
    switch (choice) {
    case 1:
        d = new int[n];          
        p = new int[n];          
        Q_S = new bool[n];        
        graf = new s_list * [n];
        S = new int[n];          
        s_wsk = 0;   

        for (i = 0; i < n; i++)
        {
            d[i] = MAXINT;
            p[i] = -1;
            Q_S[i] = false;
            graf[i] = NULL;
        }

        for (i = 0, j = 0; i < m; i++, j++)
        {
            cin >> x >> y >> w;    
            tmp = new s_list;
            tmp->v = y;
            tmp->waga = w;
            tmp->next = graf[x];
            graf[x] = tmp;

            tmp = new s_list;
            tmp->v = x;
            tmp->waga = w;
            tmp->next = graf[y];
            graf[y] = tmp;
        }

        cout << endl;

        d[start] = 0;             

        for (i = 0; i < n; i++)
        {
            for (j = 0; Q_S[j]; j++);
            for (u = j++; j < n; j++)
                if (!Q_S[j] && (d[j] < d[u])) u = j;

            Q_S[u] = true;

            for (tmp = graf[u]; tmp; tmp = tmp->next)
                if (!Q_S[tmp->v] && (d[tmp->v] > d[u] + tmp->waga))
                {
                    d[tmp->v] = d[u] + tmp->waga;
                    p[tmp->v] = u;
                }
        }
        for (int i = 0; i < 9; i++) {
            if (start == i) {
                cout << "Miasto startowe: " << names[i] << endl << endl;
            }
        }
        for (i = 0; i < n; i++)
        {
            cout << names[i] << ": ";

            for (j = i; j > -1; j = p[j])  
                S[s_wsk++] = j;

            while (s_wsk) 
                cout << S[--s_wsk] << " ";

            cout << "Koszt: " << d[i] << endl;
        }

        delete[] d;
        delete[] p;
        delete[] Q_S;
        delete[] S;

        for (i = 0; i < n; i++)
        {
            tmp = graf[i];
            while (tmp)
            {
                tmp2 = tmp;
                tmp = tmp->next;
                delete tmp2;
            }
        }

        delete[] graf; break;
    case 2:   
        graf = new s_list* [n]; 
        d = new int[n]; 
        p = new int[n];     
        S = new int[n];
        for (i = 0; i < n; i++) 
        {
            d[i] = MAXINT;
            p[i] = -1;
            graf[i] = NULL;
        }

        for (i = 0; i < m; i++)
        {
            cin >> x >> y >> w; 

            tmp = new s_list;
            tmp->v = y;
            tmp->waga = w;
            tmp->next = graf[x];
            graf[x] = tmp;

            tmp = new s_list;
            tmp->v = x;
            tmp->waga = w;
            tmp->next = graf[y];
            graf[y] = tmp;
        }

        cout << endl;

        for (int i = 0; i < 9; i++) {
            if (start == i) {
                cout << "Miasto startowe: " << names[i] << endl << endl;
            }
        }

        if (BF(start))
        {
            s_wsk = 0;

            for (i = 0; i < n; i++)
            {
                cout << names[i] << ": ";

                for (x = i; x != -1; x = p[x])
                    S[s_wsk++] = x;

                while (s_wsk)
                    cout << S[--s_wsk] << " ";

                cout << "Koszt: " << d[i] << endl;
            }
        }

        delete[] graf;
        delete[] d;
        delete[] p;
        delete[] S;

        for (i = 0; i < n; i++)
        {
            tmp = graf[i];
            while (tmp)
            {
                tmp2 = tmp;
                tmp = tmp->next;
                delete tmp2;
            }
        }
        
        break;
    }
        if ((choice >= 1) && (choice <= 2)) {
            cout << endl;
            system("pause");
        }

    return 0;
}