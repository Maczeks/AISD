#include <iostream>

using namespace std;

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];     
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int index = partition(arr, low, high);
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}
int main()
{
    int a[3][4];
    int b[12];
    int i, j, k = 0;
    cout << "Podaj elementy tabicy wymiaru 3x4 \n";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cin >> a[i][j];
        }
    }
    cout << endl;
    cout << endl;

    cout << "Tablica 2D podana przez Ciebie \n";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            b[k++] = a[i][j];
    }
    quickSort(b, 0, 12-1);

    int l = 0;
    for (i = 0; i < 3 ; i++) {
        for (j = 0; j < 4; j++) {
             a[i][j] = b[l];
             l++;
        }
    }

    cout << "Posortowana tablica: \n";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;

    }
    return 0;
}