// Laboratorium 5 - Zasięg widoczności/linkowania
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

#include <iostream>
#include "Config.h"

int main() {
    std::cout << "=== Initial configuration ===" << std::endl;
    std::cout << "debugLevel=" << debugLevel << ", verbose=" << verbose << std::endl;

    logMessage("Program started.");
    logMessage("Still running...");
    logMessage("Preparing to change configuration.");

    // Change configuration
    debugLevel = 2;
    verbose = true;

    std::cout << "\n=== Configuration changed ===" << std::endl;
    std::cout << "debugLevel=" << debugLevel << ", verbose=" << verbose << std::endl;

    logMessage("Debugging mode active.");
    logMessage("Doing something important...");
    logMessage("Program finished.");

    return 0;
}

/** Przykładowy wynik działania programu:

Przy LOG podany jest aktualny poziom debugLevel, #n oznacza licznik wywołań logowania.
Zadanie należy wykonać stosując odpowiednie specyfikatory widoczności/linkowania.

=== Initial configuration ===
debugLevel=0, verbose=0
[LOG:0] #1 Program started.
[LOG:0] #2 Still running...
[LOG:0] #3 Preparing to change configuration.

=== Configuration changed ===
debugLevel=2, verbose=1
[LOG:2] [VERBOSE] #4 Debugging mode active.
[LOG:2] [VERBOSE] #5 Doing something important...
[LOG:2] [VERBOSE] #6 Program finished.

*/