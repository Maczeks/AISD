#include <iostream>

using namespace std;

struct Edge
{
    int v1, v2; //wierzcholki 
    int weight;  //waga 
};

class Queue
{
private:
    Edge* Heap;
    int hpos;
public:
    Queue(int n);
    ~Queue();
    Edge front();
    void push(Edge e);
    void pop();
};

struct DS
{
    int up, rank;
};

class Struct
{
private:
    DS* Z;
public:
    Struct(int n);
    ~Struct();
    void MakeSet(int v);
    int FindSet(int v);
    void Merge(Edge e);
};

//Minimalne drzewo rozpinaj¹ce
struct Tree
{
    Tree* next;
    int v, weight;
};

class ListTree
{
private:
    Tree** A; //Tablica list s¹siedztwa
    int Size; //Wielkosc tablicy
    int weight; //Waga ca³ego drzewa
public:
    ListTree(int n);
    ~ListTree();
    void addEdge(Edge e);
    Tree* getlist(int n); //Prima
    void print();
};

//Konstruktor
Queue::Queue(int n)
{
    Heap = new Edge[n];   // Tworzymy tablicê
    hpos = 0;                // Pozycja w kopcu
}

//Destruktor 
Queue::~Queue()
{
    delete[] Heap;
}

//Zwraca krawêdŸ z pocz¹tku kopca
Edge Queue::front()
{
    return Heap[0];
}

//Umieszcza w kopcu now¹ krawêdŸ
void Queue::push(Edge e)
{
    int i, j;

    i = hpos++;              
    j = (i - 1) >> 1;     

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;
}

//Usuwa korzeñ z kopca
void Queue::pop()
{
    int i, j;
    Edge e;

    if (hpos)
    {
        e = Heap[--hpos];

        i = 0;
        j = 1;

        while (j < hpos)
        {
            if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
            if (e.weight <= Heap[j].weight) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = e;
    }
}

//Konstruktor
Struct::Struct(int n)
{
    Z = new DS[n];
}

//Destruktor
//-----------
Struct::~Struct()
{
    delete[] Z;
}

//Tworzy wpis w tablicy
void Struct::MakeSet(int v)
{
    Z[v].up = v;
    Z[v].rank = 0;
}

//Zwraca indeks, wierzcho³ka v
int Struct::FindSet(int v)
{
    if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
    return Z[v].up;
}

//£¹czy ze sob¹ zbiory z v i u
void Struct::Merge(Edge e)
{
    int ru, rv;

    ru = FindSet(e.v1);   
    rv = FindSet(e.v2);   
    if (ru != rv)           
    {
        if (Z[ru].rank > Z[rv].rank) 
            Z[rv].up = ru;    
        else
        {
            Z[ru].up = rv;    
            if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
        }
    }
}



//Konstruktor
ListTree::ListTree(int n)
{
    int i;

    A = new Tree * [n];   
    for (i = 0; i < n; i++) A[i] = NULL; 
    Size = n - 1; 
    weight = 0;  
}

//Destruktor
ListTree::~ListTree()
{
    int i;
    Tree* p, * r;

    for (i = 0; i <= Size; i++)
    {
        p = A[i];
        while (p)
        {
            r = p;               
            p = p->next;         
            delete r;           
        }
    }

    delete[] A;
}

//Dodaje krawêdŸ do drzewa
void ListTree::addEdge(Edge e)
{
    Tree* p;

    weight += e.weight;      
    p = new Tree;          
    p->v = e.v2;            
    p->weight = e.weight;   
    p->next = A[e.v1];
    A[e.v1] = p;

    p = new Tree;           
    p->v = e.v1;            
    p->weight = e.weight; 
    p->next = A[e.v2]; 
    A[e.v2] = p;
}

//Zwraca wskaŸnik pocz¹tku listy s¹siadów wierzcho³ka
Tree* ListTree::getlist(int n)
{
    return A[n];
}

//Drukuje wartosc drzewa i wage 
void ListTree::print()
{
    int i;
    Tree* p;

    cout << endl;
    for (i = 0; i <= Size; i++)
    {
        cout << "Wierzcholek " << i << " - ";
        for (p = A[i]; p; p = p->next) cout << p->v << ":" << p->weight << " ";
        cout << endl;
    }
    cout << endl << "Minimalna wartosc drzewa = " << weight << endl << endl;
}


int main()
{
    int choice;
    int n, m;
    Edge k;
    int i;
    Tree* p;
    int v;
    cout << "Wpisz liczbe wierzcholkow i krawedzi:" << endl;
    cin >> n >> m;
    Struct S(n);
    Queue Q(m);
    ListTree T(n);
    ListTree G(n);

    
        system("cls");

        cout << " --------------------------\n"
            "           MENU\n"
            " --------------------------\n"
            "  1  =  Algorytm Kruskala  \n"
            "  2  =  Algorytm Prima     \n"
            " --------------------------\n"
            "Wpisz numer ktory Cie interesuje: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: 
            cout << "ALGORYTM KRUSKALA" << endl << endl;
            for (i = 0; i < n; i++)
                S.MakeSet(i);

            for (i = 0; i < m; i++)
            {
                cin >> k.v1 >> k.v2 >> k.weight;
                Q.push(k);
            }
            for (i = 1; i < n; i++)
            {
                do
                {
                    k = Q.front();
                    Q.pop();
                } while (S.FindSet(k.v1) == S.FindSet(k.v2));
                T.addEdge(k);
                S.Merge(k);
            }

            T.print(); break;
        case 2:
            cout << "ALGORYTM PRIMA" << endl << endl;
            bool* visited = new bool[n];

            for (i = 0; i < n; i++)
                visited[i] = false;       

            for (i = 0; i < m; i++)
            {
                cin >> k.v1 >> k.v2 >> k.weight; 
                G.addEdge(k);            
            }
            v = 0;                         
            visited[v] = true;          

            for (i = 1; i < n; i++)       
            {
                for (p = G.getlist(v); p; p = p->next) 
                    if (!visited[p->v])    
                    {
                        k.v1 = v;                
                        k.v2 = p->v;
                        k.weight = p->weight;
                        Q.push(k);            
                    }
                do
                {
                    k = Q.front();            
                    Q.pop();
                } while (visited[k.v2]); 

                T.addEdge(k);             
                visited[k.v2] = true;  
                v = k.v2;
            }
            T.print();
            delete[] visited; break;
        }
        if ((choice >= 1) && (choice <= 2)) {
            cout << endl;
            system("pause");
        }

    return 0;
}