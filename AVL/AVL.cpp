#include <iostream>
#include <iomanip>

using namespace std;

struct AVLNode
{
    int score;
    string name;
    int bf;
    AVLNode* up;
    AVLNode* left;
    AVLNode* right;
};


void RR(AVLNode*& root, AVLNode* A)
{
    AVLNode* B = A->right, * p = A->up;

    A->right = B->left;
    if (A->right) A->right->up = A;

    B->left = A;
    B->up = p;
    A->up = B;

    if (p)
    {
        if (p->left == A) p->left = B; else p->right = B;
    }
    else root = B;

    if (B->bf == -1) A->bf = B->bf = 0;
    else
    {
        A->bf = -1; B->bf = 1;
    }
}

void LL(AVLNode*& root, AVLNode* A)
{
    AVLNode* B = A->left, * p = A->up;

    A->left = B->right;
    if (A->left) A->left->up = A;

    B->right = A;
    B->up = p;
    A->up = B;

    if (p)
    {
        if (p->left == A) p->left = B; else p->right = B;
    }
    else root = B;

    if (B->bf == 1) A->bf = B->bf = 0;
    else
    {
        A->bf = 1; B->bf = -1;
    }
}

void RL(AVLNode*& root, AVLNode* A)
{
    AVLNode* B = A->right, * C = B->left, * p = A->up;

    B->left = C->right;
    if (B->left) B->left->up = B;

    A->right = C->left;
    if (A->right) A->right->up = A;

    C->left = A;
    C->right = B;
    A->up = B->up = C;
    C->up = p;

    if (p)
    {
        if (p->left == A) p->left = C; else p->right = C;
    }
    else root = C;

    if (C->bf == -1) A->bf = 1; else A->bf = 0;
    if (C->bf == 1) B->bf = -1; else B->bf = 0;

    C->bf = 0;
}

void LR(AVLNode*& root, AVLNode* A)
{
    AVLNode* B = A->left, * C = B->right, * p = A->up;

    B->right = C->left;
    if (B->right) B->right->up = B;

    A->left = C->right;
    if (A->left) A->left->up = A;

    C->right = A;
    C->left = B;
    A->up = B->up = C;
    C->up = p;

    if (p)
    {
        if (p->left == A) p->left = C; else p->right = C;
    }
    else root = C;

    if (C->bf == 1) A->bf = -1; else A->bf = 0;
    if (C->bf == -1) B->bf = 1; else B->bf = 0;

    C->bf = 0;
}

void Insert(AVLNode*& root, AVLNode* key) 
    {
        AVLNode* w, * p, * r;
        bool t; 
        w = new AVLNode;        
        w->left = w->right = w->up = NULL;
        w->score = key->score;
        w->name = key->name;
        w->bf = 0;

        p = root;              

        if (!p) root = w;     
        else
        {                      
            while (true)
                if (key->score < p->score)   
                {
                    if (!p->left)   
                    {
                        p->left = w;   
                        break;        
                    }
                    p = p->left;     
                }
                else
                {
                    if (!p->right)  
                    {
                        p->right = w;  
                        break;         
                    }
                    p = p->right;    
                }

            w->up = p;           

            if (p->bf) p->bf = 0; 
            else
            {
                if (p->left == w)   
                    p->bf = 1;
                else
                    p->bf = -1;

                r = p->up;        
           
                t = false;
                while (r)
                {
                    if (r->bf)
                    {
                        t = true;     
                        break;        
                    };
                    
                    if (r->left == p) r->bf = 1;
                    else               r->bf = -1;

                    p = r;          
                    r = r->up;
                }

                if (t)           
                {                 
                    if (r->bf == 1)
                    {
                        if (r->right == p) r->bf = 0; 
                        else if (p->bf == -1) LR(root, r);
                        else                   LL(root, r);
                    }
                    else
                    {              
                        if (r->left == p) r->bf = 0;  
                        else if (p->bf == 1) RL(root, r);
                        else                  RR(root, r);
                    }
                }
            }
        }
    }
AVLNode* Previous(AVLNode* p) {
    AVLNode* r;

    if (p)
    {
        if (p->left)
        {
            p = p->left;
            while (p->right) p = p->right;
        }
        else
            do
            {
                r = p;
                p = p->up;
            } while (p && p->right != r);
    }
    return p;
}
AVLNode* Remove(AVLNode*& root, AVLNode* x) {
    AVLNode* t, * y, * z;
    bool nest;

    if (x->left && x->right)
    {
        y = Remove(root, Previous(x));
        nest = false;
    }
    else
    {
        if (x->left)
        {
            y = x->left; x->left = NULL;
        }
        else
        {
            y = x->right; x->right = NULL;
        }
        x->bf = 0;
        nest = true;
    }
    if (y)
    {
        y->up = x->up;
        y->left = x->left;  if (y->left)   y->left->up = y;
        y->right = x->right; if (y->right)  y->right->up = y;
        y->bf = x->bf;
    }

    if (x->up)
    {
        if (x->up->left == x) x->up->left = y; else x->up->right = y;
    }
    else root = y;

    if (nest)
    {
        z = y;
        y = x->up;
        while (y)
        {
            if (!y->bf)
            {            
                if (y->left == z)  y->bf = -1; else y->bf = 1;
                break;
            }
            else
            {
                if (((y->bf == 1) && (y->left == z)) || ((y->bf == -1) && (y->right == z)))
                {           
                    y->bf = 0;
                    z = y; y = y->up;
                }
                else
                {
                    if (y->left == z)  t = y->right; else t = y->left;
                    if (!t->bf)
                    {         
                        if (y->bf == 1) LL(root, y); else RR(root, y);
                        break;
                    }
                    else if (y->bf == t->bf)
                    {         
                        if (y->bf == 1) LL(root, y); else RR(root, y);
                        z = t; y = t->up;
                    }
                    else
                    {         
                        if (y->bf == 1) LR(root, y); else RL(root, y);
                        z = y->up; y = z->up;
                    }
                }
            }
        }
    }
    return x;
}

void Inorder(AVLNode* x)  
{
    AVLNode* tmp = x;
    if (tmp!=NULL) {

        Inorder(tmp->left);

        cout << tmp->name << " --- ";
        cout << tmp->score << " \n ";

        Inorder(tmp->right);
    }
}


bool Find(AVLNode* x, string name)
{
    if (x == NULL) {
        cout << "Nie ma takiego zawodnika" << endl;
        return false;
    }
    if (x->name == name) {
        cout << "Wynik zawodnika wynosi: " << x->score << endl;
        return true;
    }
    bool r1 = Find(x->left, name);
    if (r1) return true;
    bool r2 = Find(x->right, name);

    return r2;
}

void Search(AVLNode* T)
{
    string imie;
    cout << "-----------------------------\n";
    cout << "WYSZUKIWANIE WYNIKU ZAWODNIKA\n";
    cout << "-----------------------------\n\n";
    cout << "Podaj nazwisko zawodnika: ";
    cin >> imie;
    Find(T,imie);
}


bool Changing(AVLNode* x, string name)
{
    string tmp;
    if (x == NULL) {
        cout << "Nie ma takiego zawodnika" << endl;
        return false;
    }
    if (x->name == name) {
        cout << "Wynik zawodnika wynosi: " << x->score << endl;
        tmp = x->name;
        Remove(x, x);
        int new_score;
        cout << "Podaj nowy wynik\n";
        cin >> new_score;
        AVLNode* z;
        z = new AVLNode;
        z->name = tmp;
        z->score = new_score;
        Insert(x, z);
        return true;
    }
    bool r1 = Changing(x->left, name);
    if (r1) return true;
    bool r2 = Changing(x->right, name);
    return r2;
}

void Change(AVLNode* root)
{
    string imie;
    cout << "-----------------------\n";
    cout << "ZMIANA WYNIKU ZAWODNIKA\n";
    cout << "-----------------------\n\n";
    cout << "Podaj nazwisko zawodnika do zmiany wyniku: ";
    cin >> imie;
    Changing(root, imie);
}

int main()
{
    AVLNode* root = NULL;
    int wybor;

    AVLNode* x;
    x = new AVLNode;

    do {
        system("cls");

        cout << " -------------------------\n"
                "           MENU\n"
                " -------------------------\n"
                "  1  =  Dodaj wynik       \n"
                "  2  =  Zmien wynik       \n"
                "  3  =  Wyszukaj wynik    \n"
                "  4  =  Wyswietl wyniki   \n"
                "  0  =  Zakoncz            \n"
                " -------------------------\n"
                "Wpisz numer ktory Cie interesuje: ";
        cin >> wybor;
        system("cls");

        switch (wybor) {
        case 1: {
            cout << "-------------------\n";
            cout << "DODAWANIE ZAWODNIKA\n"
                    "-------------------\n";
            cout << "\n\nPodaj nazwisko zawodnika: ";
            cin >> x->name;
            cout << "\n\nPodaj wynik zawodnika: ";
            cin >> x->score;
            Insert(root, x);
        }
            break;
        case 2: Change(x); break; 
        case 3: Search(x); break;
        case 4: {
            cout << "--------------\n";
            cout << "    WYNIKI\n";
            cout << "--------------\n\n";
            Inorder(root);
        } break;
        }
        if ((wybor >= 1) && (wybor <= 4)) {
            cout << endl;
            system("pause");
        }
    } while (wybor);


    return 0;
}