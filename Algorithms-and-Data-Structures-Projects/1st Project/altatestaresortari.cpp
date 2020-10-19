#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <typeinfo>
#include <chrono>
typedef long long ll;
using namespace std;
using namespace std::chrono;

ifstream in("testare.in");
ofstream out("rezultat.out");

int arr[100000000], sorted[100000000], temp[100000000];

///FUNCTII AUXILIARE

int getMax(int a[], int n){
    int mx = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > mx)
            mx = a[i];
    return mx;
}

int getMin(int a[], int n){
    int mi = 1e9;
    for (int i = 0; i < n; i++)
        if (a[i] < mi)
            mi = a[i];
    return mi;
}

///TIPURI DE SORTARI
///1.Bubble Sort
void bubblesort(int a[], int n, int left, int right){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
    (void) left; (void) right; /// ca sa nu dea warning
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
    (void) left; (void) right; /// ca sa nu dea warning
}

///3.Radix Sort (doar pentru numere pozitive, cu bucketuri + Count Sort)
void radixsort256(int a[], int n, int left, int right){
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
    (void) left; (void) right; /// ca sa nu dea warning
}

void radixsort256256(int a[], int n, int left, int right){
    int bucket[256 * 256];//, temp[n];
    for (int k = 0; k < 32; k += 16){
        for (int i = 0; i < 256 * 256; i++) ///Completez bucketurile cu 0, apoi cu numarul de ultime cifre, apoi cu pozitia ultimelor numere cu cifra respectiva
            bucket[i] = 0;
        for (int i = 0; i < n; i++)
            bucket[(a[i] >> k) & (256 * 256 - 1)]++;
        for (int i = 1; i < 256 * 256; i++)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--){ ///Bagam in temp array-ul sortat dupa cifra curenta
            temp[bucket[(a[i] >> k) & (256 * 256 - 1)] - 1] = a[i];
            bucket[(a[i] >> k) & (256 * 256 - 1)]--;
        }
        for (int i = 0; i < n; i++)
            a[i] = temp[i];
    }
    (void) left; (void) right; /// ca sa nu dea warning
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
    (void) n; ///ca sa nu dea warning
}

///5.Quick Sort
int medianaDeTrei(int st, int mid, int dr){
    if ((arr[st] >= arr[dr]) != (arr[st] >= arr[mid]))
        return arr[st];
    else if ((arr[mid] >= arr[st]) != (arr[mid] >= arr[dr]))
        return arr[mid];
    else
        return arr[dr];
}

void quicksortMed3(int a[], int n, int st, int dr)
{
    if (st < dr){
        int i = st, j = dr;
        int piv = medianaDeTrei(st, st + (dr - st) / 2, dr);
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
        quicksortMed3(a, n, st, j);
        quicksortMed3(a, n, i, dr);
    }
    (void) n; ///ca sa nu dea warning
}

void quicksortRand(int a[], int n, int st, int dr)
{
    if (st < dr){
        int i = st, j = dr;
        int piv = a[st + rand() % (dr - st + 1)];
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
        quicksortRand(a, n, st, j);
        quicksortRand(a, n, i, dr);
    }
    (void) n; ///ca sa nu dea warning
}

///FUNCTIA DE TESTARE A SORTARILOR
bool testsort(int a[], int s[], int n){
    for (int i = 0; i < n; i++)
        if (a[i] != s[i])
            return 0;
    return 1;
}

int testare(void (*func)(int [], int, int, int), int n, int maxnum){
    if (n > 50000 && func == bubblesort){
        out << "\tBubblesort este ineficient pentru vectori cu " << n << " elemente\n";
        return 1e9;
    }

    for (int i = 0; i < n; i++){
        arr[i] = rand() % (maxnum + 1);
        sorted[i] = arr[i];
    }
    sort(sorted, sorted + n);

    auto start = high_resolution_clock::now();
    func(arr, n, 0, n - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (testsort(arr,sorted,n))
        out << "\tSortare - OK, Timpul de sortare: " << duration.count() << " ms\n";
    else
        out << "\tSortare - Fail, Timpul de sortare: " << duration.count() << " ms\n";

    return duration.count();
}

int testareSTL(int n, int maxnum){
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (maxnum + 1);

    auto start = high_resolution_clock::now();
    sort(arr, arr + n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    out << "\tTimpul de sortare: " << duration.count() << " ms\n";

    return duration.count();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();

    ll t, n, maxnum;
    vector <void (*)(int [], int, int, int)> sortari = {bubblesort, countsort, radixsort256, radixsort256256, mergesort, quicksortMed3, quicksortRand};
    vector <string> sortnames = {"Bubblesort", "Countsort", "Radixsort(256)", "Radixsort(256 * 256)", "Mergesort", "Quicksort(Mediana din 3)", "Quicksort(Random)", "STL"};
    int sorttimes[8];

    in >> t;
    while(t--){
        in >> n >> maxnum;

        out << "\t\tTestarea sortarilor pentru un array cu " << n << " de numere din intervalul [0;" << maxnum << "]:\n\n";
        for(int i = 0; i < sortari.size(); i++){
            out << sortnames[i] << ":";
            sorttimes[i] = testare(sortari[i], n, maxnum);
        }

        out << "Sortare STL:  ";
        sorttimes[7] = testareSTL(n, maxnum);

        int minim = getMin(sorttimes, 8);
        out << "\nCea/Cele mai eficienta/eficiente sortare/sortari: ";
        for(int i = 0; i < 8; i++)
            if (sorttimes[i] == minim)
                out << sortnames[i] << " ";
        out << "\n";

        out << "Radixsort-ul mai eficient: ";
        if (sorttimes[2] == sorttimes[3])
            out << "Ambele\n";
        else if (sorttimes[2] > sorttimes[3])
            out << sortnames[3] << "\n";
        else
            out << sortnames[2] << "\n";

        out << "Quicksort-ul mai eficient: ";
        if (sorttimes[5] == sorttimes[6])
            out << "Ambele\n\n\n\n";
        else if (sorttimes[5] > sorttimes[6])
            out << sortnames[6] << "\n\n\n\n";
        else
            out << sortnames[5] << "\n\n\n\n";
    }

    return 0;
}



/* Am incercat cu mediana medianei, dar imi iese din timp, am incercat prin doua metode, in Python probabil e mai ok pentru utilizare :)
vector < vector <int> > subliste;
vector <int> sublista;

int BFPRT(int a[], int sz, int st, int dr){
    if (sz <= 5)
        return a[st + (dr - st) / 2];
    for (int i = st; i <= dr; i += 5){
        for (int j = i; j <= dr && j < i + 5; j++)
            sublista.push_back(a[j]);
        sort(sublista.begin(), sublista.end());
        subliste.push_back(sublista);
        sublista.clear();
    }
    int newsz = subliste.size();
    int mediane[newsz];
    for(int i = 0; i < newsz; i++)
        mediane[i] = subliste[i][subliste[i].size() / 2];
    subliste.clear();
    return BFPRT(mediane, newsz, 0, newsz - 1);
}

int medmed(int a[], int sz, int st, int dr){
    if (sz <= 5)
        return a[st + (dr - st) / 2];
    int *temporar = new int[sz];
    for (int i = st; i <= dr; i++)
        temporar[i - st] = a[i];

    int *mediane = new int[(sz + 4) / 5];
    for (int i = 0; i < sz; i += 5){
        sort(temporar + i, temporar + i + min(5, sz - i));
        mediane[i / 5] = temporar[i + (min(i + 5, sz) - i) / 2];
    }
    delete [] temporar;
    return medmed(mediane, (sz + 4) / 5, 0, (sz + 4) / 5 - 1);
    delete [] mediane;
}
*/
