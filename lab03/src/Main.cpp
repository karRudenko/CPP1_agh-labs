// Laboratorium 3 - Implementacja listy dwukierunkowej w C
//
// Prosze dopisać kod i dodać nowe pliki, tak aby program wykonywał się
// a wynik jego działania był taki sam jak podany na końcu tego pliku.
//
// Pliku main.cpp nie wolno modyfikować. Oczywiście, w czasie pracy można
// sobie jego część wykomentować, ale wersja wysłana jako rozwiązanie powinna
// zawierać plik w oryginalnej wersji – będę to sprawdzał diffem :).
//
// Ostateczny program powinien być przyjazny dla programisty
// (mieć czytelny i dobrze napisany kod).
// - co to znaczy? 
//   * kod powinien być podzielony na nagłówki i źródła
//   * nazwy powinny być zrozumiałe i spójne
//   * kod powinien kompilować się bez ostrzeżeń z flagami:
//     -Wall -Wextra -Wpedantic
//   * nie powinien powodować wycieków pamięci,
//     tzn. powinien bezproblemowo przechodzić sprawdzenie valgrindem
//
// Przy wykonywaniu zadania, nie wolno korzystać z internetu, notatek,
// ani żadnych innych materiałów (w tym własnych, wcześniej
// przygotowanych, plików). Jedynym wyjątkiem jest dołączony do zadania plik CMakeLists.txt.
//
// Kody źródłowe muszą znajdować się w katalogu do którego nikt oprócz
// właściciela nie ma praw dostępu. Rozwiązanie należy wgrać na UPeLa
// jako archiwum tar.gz o strukturze takiej jak opisana poniżej.
//
// UWAGA:
// * archiwum powinno zawierać katalog z zadaniem labN/, gdzie N to numer zadania/laboratorium
// W tym katalogu powinniśmy mieć trzy podkatalogi - include (na pliki nagłówkowe), 
// src (na pliki implementacyjne) oraz build (na budowę projektu), a także plik CMakeLists.txt, 
// który poprawnie opisuje zawartość projektu.
// Katalog build powinien być pusty.
// * tworzenie archiwum: tar -czvf nazwa.tar.gz zad/
//   np. tar -czvf lab01.tar.gz lab01/
// * rozpakowanie archiwum: tar -xvf nazwa.tar.gz

#include "List.h"
#include <stdio.h>


int main() {

    List l;
    listInit(&l);

    listPushBack(&l, 10);
    listPushBack(&l, 20);
    listPushBack(&l, 30);
    listPrintForward(&l);
    listPrintBackward(&l);

    listPushFront(&l, 5);
    listPushFront(&l, 2);
    listPrintForward(&l);
    listPrintBackward(&l);

    printf("Pop front: %d\n", listPopFront(&l));
    printf("Pop back: %d\n", listPopBack(&l));
    listPrintForward(&l);
    listPrintBackward(&l);

    listDestroy(&l);
    return 0;
}
/** Przykładowy wynik działania programu:
FWD (size=3): [10 20 30]
BWD (size=3): [30 20 10]
FWD (size=5): [2 5 10 20 30]
BWD (size=5): [30 20 10 5 2]
Pop front: 2
Pop back: 30
FWD (size=3): [5 10 20]
BWD (size=3): [20 10 5]
*/