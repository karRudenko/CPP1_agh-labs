// Laboratorium 3 - Implementacja funkcjonalności grep
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

#include "Match.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <text> <pattern>\n";
        return 1;
    }

    const char* text = argv[1];
    const char* pattern = argv[2];

    if (match(text, pattern)) {
        std::cout << "Pattern \"" << pattern
                  << "\" found in text \"" << text << "\".\n";
    } else {
        std::cout << "Pattern \"" << pattern
                  << "\" not found in text \"" << text << "\".\n";
    }

    return 0;
}

/*
UWAGA: W tym zadaniu chcemy przetestować warunkową kompilację oraz zachowanie linkera.
CMakeLists dołączony do zadania, spowoduje wygenerowanie Makefile z dwiema regułami.
Jedna z nich, wywoływana zwykłym make, kompiluje i linkuje kod z flagą IMPLEMENT_MATCH.
Druga, wywoływana przez make grep_fail, wykonuje to samo, ale bez ww. flagi.

Waszym zadaniem jest napisanie kodu tak, by w pierwszym przypadku działał bez problemu,
a w drugim kompilował się, ale generował błąd w czasie linkowania - czyli undefined reference (używając do tego, w odpowiedni sposób, warunkowej kompilacji).


Przykładowa interakcja:

$ ./grep_ok "hello world" "wor"
Pattern "wor" found in text "hello world".

*/
