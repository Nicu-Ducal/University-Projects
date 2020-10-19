# ASD Tema 1 - Sortari 
(consider ca merită să fie citit)

BubbleSort, CountSort, RadixSort (în baza 256 și 256 * 256), MergeSort și QuickSort (doua metode de selectiea a pivotului: mediana din 3 și alegere random a pivotului) implementate în C++ (IDE - CodeBlocks).
Am făcut update la funcția de testare cu trimitere a functiei de sortare ca argument și testarea sortarii pentru vectori cu pana la 100.000.000 de elemente și comparatie cu sort-ul din STL + afisarea timpului de sortare.

După update 
    (1) Am adăugat încă două tipuri de sortare: Radixsort (în baza 256 * 256) și Quicksort (selecția pivotului cu mediana din 3);
    (2) Am îmbunătățit funcția de testare și am eliminat sortarea unui array deja sortat, pentru că lua prea mult timp (prima versiune a temei cu această funcție se află în fișierul "main.cpp");
    (3) Am adaugat citirea testelor din fișier (fișierul "testare.in");
    
Facts:
    (1) Tema updated se află în fișierul "altatestaresortari.cpp";
    (2) Am încercat să fac mediana medianei (BFPRT) pentru Quicksort (sunt cele doua functii comentate dupa main()), dar probabil din cauza  creării array-urilor consumă mai mult timp, probabil e mai bună pentru Python (sau eu nu am gândit cum trebuie, dar parcă așa ar trebui);
    (3) Programul rulează circa 3 - 5 minute (din cauza sortarii array-urilor mari - cu 10^7 și 10^8 elemente).
