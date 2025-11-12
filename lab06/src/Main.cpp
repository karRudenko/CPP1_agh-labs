// Laboratorium 6 - CMake
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


#include "Logger.h"

int main() {

    Logger logger;

    // Domyślny poziom logowania to INFO
    logger.setMinimumLoggingLevel(Logger::WARNING);

    logger.log("Program started.", Logger::INFO);                // poniżej poziomu, nie pojawi się
    logger.log("Loading configuration...", Logger::DEBUG);        // pojawi się tylko w buildzie Debug
    logger.log("Possible configuration issue.", Logger::WARNING); // pojawi się, bo WARNING >= WARNING
    logger.log("Unhandled exception!", Logger::ERROR);            // pojawi się, bo ERROR >= WARNING

    logger.mute(); // Całkowicie wyłączamy logowanie
    logger.log("This log will not appear.", Logger::ERROR);       // wyciszony, niezależnie od poziomu

    logger.unmute(); // Ponownie włączamy logowanie
    logger.log("Recovered from error.", Logger::INFO);            // poniżej poziomu (INFO < WARNING), nie pojawi się
    logger.log("Program finished.", Logger::WARNING);             // pojawi się, bo WARNING >= WARNING

    return 0;
}

/** 
Jak już przećwiczyliśmy extern, to nauczymy się teraz unikać jego i zmiennych globalnych (bo nie są zbyt dobrą praktyką). :P

Uwaga: składnia Logger::INFO oznacza po prostu enuma zdefiniowanego wewnątrz klasy (w jej przestrzeni nazw).

Logger powinien obsługiwać cztery poziomy ważności - INFO, WARNING, ERROR oraz DEBUG. 
Przy czym, wiadomości z poziomem DEBUG wyświetlane są tylko i wyłącznie gdy zbudowaliśmy wersję debugową programu.
W wersji release powinny być zupełnie ignorowane po stronie loggera.

Minimalny poziom logowania oznacza, że wypisujemy tylko komunikaty na tym, lub ważniejszym poziomie. Np. jeśli poziom to ERROR,
to wypisujemy tylko logi poziomu ERROR lub DEBUG. Hierarchia jest dokładnie taka, jak powyżej (ofc od lewej do prawej :D).

Logger powinien startować z minimalnym poziomem logowania INFO oraz w stanie unmute. Konstruktor NIE jest tutaj potrzebny. :)

Proszę też starać się już operować na std::string i używać modyfikatora const tam, gdzie to możliwe. 
Zwracam uwagę, że w C++ zmienne złożone możemy przekazywać (bez robienia kopii) do funkcji, w której ich nie modyfikujemy, przez tzw. stałą referencję - np.  ... funkcja(Logger const& logger, ...).
W dużej mierze jest to podobne do tego, co znacie już z C, czyli const Logger* const (aka stały wskaźnik na stały obiekt), ale nie musimy robić dereferencji, bo obiekt zachowuje się dokładnie tak jak przy przekazywaniu przez wartość.
Podobnie, metody klasy, które nie modyfikują w żaden sposób jej zmiennych składowych, możemy oznaczyć tym samym modyfikatorem, np.

... metoda(Logger const& logger, ...) const;

To daje nam też dodatkowe crosschecki, bo kompilator wtedy nie dopuści by taka metoda zmieniała przekazany obiekt logger (ściślej, nie pozwoli wywołać żadnej z metod loggera, która nie jest oznaczona jako const - tym pojawiającym się na końcu). 
Podobnie, kompilator nie pozwoli nam wewnątrz tej metody zmienić klasy, do której należy (przez ten const na samym końcu).


Dodatkowo, dzisiaj CMakeLists jest do napisania samemu. Proszę pamiętać, żeby go załączyć do zadania!
Trzeba to zrobić tak, żeby dało się program zbudować w trybie Debug lub Release (w zależności od tego zmienia nam się tylko trochę printout).
(uwaga, pod przykładem są jeszcze dodatkowe wymagania)


Build debugowy:

[DEBUG] Loading configuration...
[WARNING] Possible configuration issue.
[ERROR] Unhandled exception!
[WARNING] Program finished.


Build release:

[WARNING] Possible configuration issue.
[ERROR] Unhandled exception!
[WARNING] Program finished.



Czyli musi tak zadziałać jeśli zrobię:

cmake -DCMAKE_BUILD_TYPE=Debug ..
make
./program

albo

cmake -DCMAKE_BUILD_TYPE=Release ..
make
./program


Wymagania:
- CMake powinien wymuszać standard C++17
- Kompilacja powinna odbywać się z flagami -Wall oraz -Wextra (w obu przypadkach)
- W przypadku buildu typu RELEASE, włączamy dodatkowo optymalizację -O2



Dla chętnych (bez bonusu punktowego, dla ćwiczenia :D) - proszę spróbować przygotować drugą wersję CMakeLists, 
która kompiluje Logger.cpp jako osobną bibliotekę statyczną, a do programu (sam main) tylko ją linkuje. 
*/