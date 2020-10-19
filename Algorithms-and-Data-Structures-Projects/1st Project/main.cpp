#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
typedef long long ll;
using namespace std;
using namespace std::chrono;

int arr[100000000], sorted[100000000], temp[100000000];

///FUNCTII AUXILIARE

ll getMax(int a[], int n){
    int mx = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > mx)
            mx = a[i];
    return mx;
}

///TIPURI DE SORTARI
///1.Bubble Sort
void bubblesort(int a[], int n, int left, int right){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

///2.Count Sort (doar pentru numere pozitive)
void countsort(int a[], int n, int left, int right){
    int mx = getMax(a, n);
    int aux[mx + 1];
    for (int i = 0; i <= mx; i++)
        aux[i] = 0;

    for (int i = 0; i < n; i++)
        aux[a[i]]++;

    int idx = 0;
    for (int i = 0; i <= mx; i++)
        while(aux[i] != 0){
            a[idx++] = i;
            aux[i]--;
        }
}

///3.Radix Sort (doar pentru numere pozitive, cu bucketuri + Count Sort)
void radixsort(int a[], int n, int left, int right){
    int bucket[256];//, temp[n];
    for (int k = 0; k < 16; k += 8){
        for (int i = 0; i < 256; i++) ///Completez bucketurile cu 0, apoi cu numarul de ultime cifre, apoi cu pozitia ultimelor numere cu cifra respectiva
            bucket[i] = 0;
        for (int i = 0; i < n; i++)
            bucket[(a[i] >> k) & 255]++;
        for (int i = 1; i < 256; i++)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--){ ///Bagam in temp array-ul sortat dupa cifra curenta
            temp[bucket[(a[i] >> k) & 255] - 1] = a[i];
            bucket[(a[i] >> k) & 255]--;
        }
        for (int i = 0; i < n; i++)
            a[i] = temp[i];
    }
}

///4.Merge Sort
void interclasare(int a[], int left, int mid, int right){
    int i = left;
    int j = mid + 1;
    int index = left;

    while (i <= mid && j <= right){
        if (a[i] < a[j]){
            temp[index] = a[i];
            index++; i++;
        }
        else{
            temp[index] = a[j];
            index++; j++;
        }
    }

    while(i <= mid){
        temp[index] = a[i];
        index++; i++;
    }

    while(j <= right){
        temp[index] = a[j];
        index++; j++;
    }

    for (int i = left; i <= right; i++)
        a[i] = temp[i];
}

void mergesort(int a[], int n, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        mergesort(a, n, left, mid);
        mergesort(a, n, mid + 1, right);
        interclasare(a, left, mid, right);
    }
}

///5.Quick Sort
void quicksort(int a[], int n, int st, int dr)
{
    if (st < dr){
        int i = st, j = dr;
        int piv = a[st + (rand() % (dr - st + 1))];
        while (i <= j){
           while (i <= dr && a[i] < piv)
               i++;
           while (j >= st && a[j] > piv)
               j--;
           if (i <= dr && j >= st && i <= j){
               swap(a[i], a[j]);
               i++;
               j--;
           }
        }
        quicksort(a, n, st, j);
        quicksort(a, n, i, dr);
    }
}

///FUNCTIA DE TESTARE A SORTARILOR
bool testsort(int a[], int s[], int n){
    for (int i = 0; i < n; i++)
        if (a[i] != s[i])
            return 0;
    return 1;
}

void testare(void (*func)(int a[], int n, int left, int right)){
    int maxn;
    if (func == bubblesort)
        maxn = 10000;
    else
        maxn = 100000000;

    for (int n = 1000; n <= maxn; n *= 10){
        int temp = (n > 100000) ? 10000000 : 5000000;
        for (int i = 0; i < n; i++){
            arr[i] = rand() % temp;
            sorted[i] = arr[i];
        }

        auto start = high_resolution_clock::now();
        func(arr, n, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Sortarea vectorului cu " << n << " de elemente: " << duration.count() << " ms\n";

        start = high_resolution_clock::now();
        sort(sorted, sorted + n);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        cout << "Sortarea STL a vectorului cu " << n << " de elemente: " << duration.count() << " ms\n";

        if (testsort(arr, sorted, n))
            cout << "SORTARE - OK!\n\n";
        else
            cout << "SORTARE - FAIL!\n\n";

        if (func == quicksort && n == 100000000)
            cout << "La sortarea vectorului sortat cu " << n << " elemente, Quicksortul crapa\n\n";
        else{
            start = high_resolution_clock::now();
            func(arr, n, 0, n - 1);
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Sortarea vectorului deja sortat cu " << n << " de elemente: " << duration.count() << " ms\n";

            start = high_resolution_clock::now();
            sort(sorted, sorted + n);
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Sortarea STL a vectorului deja sortat cu " << n << " de elemente: " << duration.count() << " ms\n";

            if (testsort(arr, sorted, n))
                cout << "SORTARE - OK!\n\n";
            else
                cout << "SORTARE - FAIL!\n\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();

    cout << "\t\tTestare Bubblesort:\n";
    testare(bubblesort);

    cout << "\t\tTestare Countsort:\n";
    testare(countsort);

    cout << "\t\tTestare Radixsort:\n";
    testare(radixsort);

    cout << "\t\tTestare Mergesort:\n";
    testare(mergesort);

    cout << "\t\tTestare Quicksort:\n";
    testare(quicksort);

    return 0;
}
