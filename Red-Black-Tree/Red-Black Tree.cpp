#include <iostream>
#include <iomanip>

using namespace std;

struct BR_node
{
    int score;
    string name;
    BR_node* l_son;
    BR_node* r_son;
    BR_node* parent;
    char color;
};

BR_node* minBRTree(BR_node* sentry, BR_node* root)
{
	if (root != sentry)
		while (root->l_son != sentry) root = root->l_son;
	return root;
}

BR_node* nextNode(BR_node* currentNode, BR_node* sentry, BR_node* root)
{
	BR_node* pom;

	if (currentNode != sentry)
	{
		if (currentNode->r_son != sentry) return minBRTree(sentry, currentNode->r_son);
		else
		{
			pom = currentNode->parent;
			while ((pom != sentry) && (currentNode == pom->r_son))
			{
				currentNode = pom;
				pom = pom->parent;
			}
			return pom;
		}
	}
	return sentry;
}

void RotLeft(BR_node* A, BR_node* sentry, BR_node*& root)
{
	BR_node* B;
	BR_node* pom;

	B = A->r_son;

	if (B != sentry)
	{
		pom = A->parent;
		A->r_son = B->l_son;

		if (A->r_son != sentry) A->r_son->parent = A;

		B->l_son = A;
		B->parent = pom;
		A->parent = B;

		if (pom != sentry)
		{
			if (pom->l_son == A) pom->l_son = B;
			else pom->r_son = B;
		}
		else root = B;
	}
}

void RotRight(BR_node* A, BR_node* sentry, BR_node*& root)
{
	BR_node* B;
	BR_node* pom;

	B = A->l_son;

	if (B != sentry)
	{
		pom = A->parent;
		A->l_son = B->r_son;

		if (A->l_son != sentry) A->l_son->parent = A;

		B->r_son = A;
		B->parent = pom;
		A->parent = B;

		if (pom != sentry)
		{
			if (pom->l_son == A) pom->l_son = B;
			else pom->r_son = B;
		}
		else root = B;
	}
}

void insertBR(BR_node*& BR_Tree, BR_node* sentry, BR_node* value)
{
	BR_node* nodeToAdd = new BR_node;
	nodeToAdd->score = value->score;
	nodeToAdd->name = value->name;
	nodeToAdd->color = 'R';
	nodeToAdd->l_son = sentry;
	nodeToAdd->r_son = sentry;
	nodeToAdd->parent = BR_Tree;

	BR_node* pom = BR_Tree;

	if (BR_Tree == sentry)
	{
		BR_Tree = nodeToAdd;
		BR_Tree->color = 'B';
	}
	else
	{
		while (1)
		{
			if (value->score < nodeToAdd->parent->score)
			{
				if (nodeToAdd->parent->l_son == sentry)
				{
					nodeToAdd->parent->l_son = nodeToAdd;
					break;
				}
				nodeToAdd->parent = nodeToAdd->parent->l_son;
			}
			else
			{
				if (nodeToAdd->parent->r_son == sentry)
				{
					nodeToAdd->parent->r_son = nodeToAdd;
					break;
				}
				nodeToAdd->parent = nodeToAdd->parent->r_son;
			}
		}
	}

	while ((nodeToAdd != BR_Tree) && (nodeToAdd->parent->color == 'R'))
	{
		if (nodeToAdd->parent == nodeToAdd->parent->parent->l_son)
		{
			pom = nodeToAdd->parent->parent->r_son; //uncle for nodeToAdd

			if (pom->color == 'R') //case 1
			{
				nodeToAdd->parent->color = 'B';
				pom->color = 'B';
				nodeToAdd->parent->parent->color = 'R';
				nodeToAdd = nodeToAdd->parent->parent;
				continue;
			}

			if (nodeToAdd == nodeToAdd->parent->r_son) //case 2
			{
				nodeToAdd = nodeToAdd->parent;
				RotLeft(nodeToAdd, sentry, BR_Tree);
			}

			nodeToAdd->parent->color = 'B'; //case 3
			nodeToAdd->parent->parent->color = 'R';
			RotRight(nodeToAdd->parent->parent, sentry, BR_Tree);
			break;
		}
		else
		{
			pom = nodeToAdd->parent->parent->l_son; //uncle

			if (pom->color == 'R') //case 1
			{
				nodeToAdd->parent->color = 'B';
				pom->color = 'B';
				nodeToAdd->parent->parent->color = 'R';
				nodeToAdd = nodeToAdd->parent->parent;
				continue;
			}

			if (nodeToAdd == nodeToAdd->parent->l_son) //case 2
			{
				nodeToAdd = nodeToAdd->parent;
				RotRight(nodeToAdd, sentry, BR_Tree);
			}

			nodeToAdd->parent->color = 'B';
			nodeToAdd->parent->parent->color = 'R';
			RotLeft(nodeToAdd->parent->parent, sentry, BR_Tree);
			break;
		}
	}
	BR_Tree->color = 'B';
}

void removeRB(BR_node* BR_Tree, BR_node* sentry, BR_node* nodeToRemove)
{
    BR_node* W, * Y, * Z;

    if ((nodeToRemove->l_son == sentry) || (nodeToRemove->r_son == sentry)) Y = nodeToRemove;
    else Y = nextNode(nodeToRemove,sentry,BR_Tree);

    if (Y->l_son != sentry) Z = Y->l_son;
    else Z = Y->r_son;

    Z->parent = Y->parent;

    if (Y->parent == sentry) BR_Tree = Z;
    else if (Y == Y->parent->l_son) Y->parent->l_son = Z;
    else Y->parent->r_son = Z;

    if (Y != nodeToRemove) nodeToRemove->score = Y->score;

    if (Y->color == 'B')   // Naprawa struktury drzewa czerwono-czarnego
        while ((Z != BR_Tree) && (Z->color == 'B'))
            if (Z == Z->parent->l_son)
            {
                W = Z->parent->r_son;

                if (W->color == 'R')
                {              // Przypadek 1
                    W->color = 'B';
                    Z->parent->color = 'R';
                    RotLeft(Z->parent,sentry,BR_Tree);
                    W = Z->parent->r_son;
                }

                if ((W->l_son->color == 'B') && (W->r_son->color == 'B'))
                {              // Przypadek 2
                    W->color = 'R';
                    Z = Z->parent;
                    continue;
                }

                if (W->r_son->color == 'B')
                {              // Przypadek 3
                    W->l_son->color = 'B';
                    W->color = 'R';
                    RotRight(W,sentry,BR_Tree);
                    W = Z->parent->r_son;
                }

                W->color = Z->parent->color; // Przypadek 4
                Z->parent->color = 'B';
                W->r_son->color = 'B';
                RotLeft(Z->parent,sentry,BR_Tree);
                Z = BR_Tree;      // To spowoduje zakoñczenie pêtli
            }
            else
            {                // Przypadki lustrzane
                W = Z->parent->l_son;

                if (W->color == 'R')
                {              // Przypadek 1
                    W->color = 'B';
                    Z->parent->color = 'R';
                    RotRight(Z->parent,sentry,BR_Tree);
                    W = Z->parent->l_son;
                }

                if ((W->l_son->color == 'B') && (W->r_son->color == 'B'))
                {              // Przypadek 2
                    W->color = 'R';
                    Z = Z->parent;
                    continue;
                }

                if (W->l_son->color == 'B')
                {              // Przypadek 3
                    W->r_son->color = 'B';
                    W->color = 'R';
                    RotLeft(W,sentry,BR_Tree);
                    W = Z->parent->l_son;
                }

                W->color = Z->parent->color;  // Przypadek 4
                Z->parent->color = 'B';
                W->l_son->color = 'B';
                RotRight(Z->parent,sentry,BR_Tree);
                Z = BR_Tree;      // To spowoduje zakoñczenie pêtli
            }

    Z->color = 'B';
    delete Y;
}

void Inorder(BR_node* root, BR_node* sentry)
{
    BR_node* tmp = root;
    if (tmp != sentry) {
        Inorder(tmp->l_son,sentry);
        cout << tmp->name << " --- ";
        cout << tmp->score << " \n ";
        Inorder(tmp->r_son,sentry);
    }
}


bool Find(BR_node* x,BR_node* sentry, string name)
{
    if (x == sentry) {
        cout << "Nie ma takiego zawodnika" << endl;
        return false;
    }
    if (x->name == name) {
        cout << "Wynik zawodnika wynosi: " << x->score << endl;
        return true;
    }
    bool r1 = Find(x->l_son,sentry, name);
    if (r1) return true;
    bool r2 = Find(x->r_son,sentry, name);

    return r2;
}

void Search(BR_node* T,BR_node* sentry)
{
    string imie;
    cout << "-----------------------------\n";
    cout << "WYSZUKIWANIE WYNIKU ZAWODNIKA\n";
    cout << "-----------------------------\n\n";
    cout << "Podaj nazwisko zawodnika: ";
    cin >> imie;
    Find(T,sentry,imie);
}


bool Changing(BR_node* root, BR_node* sentry ,string name)
{
    string tmp;
    BR_node* new_root = root;
    if (new_root == sentry) {
        cout << "Nie ma takiego zawodnika" << endl;
        return false;
    }
    if (new_root->name == name) {
        cout << "Wynik zawodnika wynosi: " << new_root->score << endl;
        tmp = new_root->name;
        removeRB(root,sentry,new_root);
        int new_score;
        cout << "Podaj nowy wynik\n";
        cin >> new_score;
        BR_node* z;
        z = new BR_node;
        z->name = tmp;
        z->score = new_score;
        insertBR(root,sentry,z);
        return true;
    }
    bool r1 = Find(new_root->l_son,sentry, name);
    if (r1) return true;
    bool r2 = Find(new_root->r_son,sentry, name);
    return r2;
}

void Change(BR_node* root,BR_node* sentry)
{
    string imie;
    cout << "-----------------------\n";
    cout << "ZMIANA WYNIKU ZAWODNIKA\n";
    cout << "-----------------------\n\n";
    cout << "Podaj nazwisko zawodnika do zmiany wyniku: ";
    cin >> imie;
    Changing(root,sentry,imie);
}
int main()
{
    int wybor;

    BR_node* sentry;
    sentry = new BR_node;
	sentry->color = 'B';
	BR_node* root = sentry;

    BR_node* x;
    x = new BR_node;
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
            insertBR(root,sentry,x);
        }
            break;
        case 2: Change(root,sentry); break; 
        case 3: Search(root,sentry); break;
        case 4: {
            cout << "--------------\n";
            cout << "    WYNIKI\n";
            cout << "--------------\n\n";
            Inorder(root,sentry);
        } break;
        }
        if ((wybor >= 1) && (wybor <= 4)) {
            cout << endl;
            system("pause");
        }
    } while (wybor);

    delete x;
    return 0;
}