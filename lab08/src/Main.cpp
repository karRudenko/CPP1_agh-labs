// Laboratorium 8 - W końcu coś ciekawszego niż listy i stosy.
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


#include "Reward.h"
#include "Quest.h"

int main() {


    Reward empty_reward; // nie skompiluje się jeżeli nie mamy domyślnego konstruktora
    // Quest empty_quest; // nie powinno się skompilować po odkomentowaniu (nie chcemy możliwości tworzenia questa bez podania parametrów)

    Quest q_test("quest testowy", "opis testowy"); // Utworzenie questa bez nagrody


    Reward basic_reward(50, 0, "");
    Quest q1("Zanieść rzepy Hildzie", "Zbierz rzepę z pola Lobarta.", basic_reward);
    q1.print();


    const Reward epic_reward(7000, 10000, "Naładowany Uriziel");
    Quest q2("Magiczny miecz Uriziel", "Naładuj Uriziela energią z kopca magicznej rudy.", epic_reward);
    q2.print();


    Reward alternative_epic_reward(7000, 10000, "Fala Śmierci Uriziela");
    q2.changeReward(alternative_epic_reward);
    q2.print();


    Quest q3(
        "Wydzielina pełzaczy",
        "Zdobądź 3 jaja pełzaczy dla Cor Kaloma.",
        Reward(5500, 0, "Esencja ducha; Esencja życia")
    );
    q3.print();


    Reward bonus_reward(0, 100, "Łomotacz");
    q3.addReward(bonus_reward);
    q3.print();


    return 0;
}

/** 
Wyjaśnię publicznie, dla kilku osób, które chyba nie czytają mojego feedbacku. :D

Nawiasem mówiąc, proszę to robić. Używam wstępów i feedbacku, żeby nie zawracać Wam głowy mówieniem jak chcecie się od razu skoncentrować na zadaniu 
(tym bardziej, że niektórzy się spóźniają i musiałbym przerywać Wam pracę, żeby coś powiedzieć do wszystkich). Nawet jeśli czasem są przydługie, to daję Wam zawsze dodatkowy czas.
No i moje umiejętności formułowania mądrych zdań o 8 rano są raczej kiepskie. :D



Jeżeli mamy metodę klasy, to określamy już scope w deklaracji (i definicji). W szczególności, mamy:

void Klasa::metoda() { ... }

więc kompilator wie skąd brać zmienne klasy. Nie musimy się do nich odnosić przez this->. This jest nam właściwie potrzebne tylko jako wskaźnik na bieżącą instancję 
(patrz dzisiejsze zadanie z adresem lub używanie funkcji lambda z dostępem do pól klasy wewnątrz metod - wtedy musimy przechwycić [this]).
Jest jeden, baaa(aaa)aaardzo specyficzny przypadek, gdy jest konieczne - przy dziedziczeniu z szablonu klasy. Daleko przed nami, jeśli w ogóle. :D

W teorii można też użyć this, jeżeli argument metody przesłania nazwą zmienną klasy, ale właśnie dlatego prosiłem Was w feedbacku o to, żeby pola klasy oznaczać, np. przez m_ lub _ na początku/końcu (dowolnie, byle konsekwentnie).

Tym bardziej nie powinniśmy pisać wewnątrz metody Klasa::zmienna, bo robi to straszny chaos wizualny i koncepcyjny. W ten sposób odnosimy się do zmiennej/metody statycznej klasy, a nie do pola instancji.
Podsumowując:

void Klasa::metoda(double zmiennaKlasy) {

    m_zmiennaKlasy = zmiennaKlasy; // nie ma konfliktu nazw, scope jest znany, wiadomo która zmienna jest w klasie a która jest argumentem
    innaMetodaKlasy(); // ponownie, scope jest znany
}

Jeśli mamy wszędzie Klasa::a = Klasa::b + Klasa::c, lub this->a = this->b + this->c, to kod bardzo szybko staje się mało czytelny (a pierwsza wersja właściwie "działa przypadkiem").


Jeszcze mały komentarz (możecie przeczytać później :)), do static/inline/extern w kontekście tzw. linkage i czasu życia pewnie jeszcze wrócimy w przyszłości, jak nam się naturalnie pojawią miejsca do ich użycia.
Nie chcę tworzyć już zadań, gdzie są wrzucone na siłę (ani robić 10. z rzędu loggera :D) i jednocześnie stwarzać mylne wrażenie, 
że to jest "domyślny sposób rozwiązywania tego problemu we współczesnym C++". :)


Na przykład, w znakomitej większości przypadków, globalne zmienne i extern w dużym projekcie to proszenie się o kłopoty, bo tworzymy kod, który ciężko debugować i rozwijać (nie róbcie tego :)). 
Czasem, w embedded czy sterownikach, zdarza się, że trzeba mieć globalnie dostępny handle do urządzenia i nie bardzo da się to zrobić inaczej. Ale to jest bardzo specyficzny case.

Globalne stałe to troche inna historia (inline constexpr albo inline const). Tu inline się rzeczywiście przydaje, żeby pozwolić linkerowi na utworzenie z wielu definicji jednego symbolu,
zamiast tworzyć kopię dla każdej jednostki translacyjnej i nie zwiększać sztucznie rozmiaru binarki. 
Albo gdybyśmy bardzo chcieli robić tzw. "header only library" z funkcjami, żeby uniknąć wielokrotnej deklaracji.

Z kolei inline w wersji "optymalizującej" (AKA proszę wklej mój kod bezpośrednio) ma bardzo różną skuteczność, bo w C/C++ nie ma twardego inline, tylko sugestia (kompilator i tak zrobi co chce, bazując na heurystyce, np. wielkości kodu).
Generalnie, większy wpływ na to czy coś rzeczywiście będzie inline czy nie, mają flagi optymalizacji (-O2, -O3 itd.) niż pojawienie się słowa inline. Szczególnie w GCC.
Żeby rzeczywiście osiągnąć zamierzony efekt (z dużym prawdopodobieństwem), trzeba dodatkowo użyć bezpośrednio dyrektywy kompilatora (np. __attribute__((always_inline)) w gcc).
A żeby być pewnym, napisać kawałek kodu w assemblerze samemu. :)

Podobnie, większość "treningowych" przykładów użycia static w klasach, dużo lepiej byłoby załatwić po prostu przestrzeniami nazw (np. różne funkcje i stałe pomocnicze) 
albo "z zewnątrz" (np. cacheowanie wyników w zewnętrznej strukturze, żeby nie tworzyć tzw. "global hidden state").
Albo są równoważne temu, co już przećwiczyliśmy bez klas, tylko licznik czy inne verbose przeniosłoby się do konstruktora i destruktora. :)
Nawiasem mówiąc, jestem wielkim fanem dedykowanych loggerów BEZ statycznych zmiennych. :D

Wyjątków jest naprawdę tylko kilka - stałe, metadane i metody, które rzeczywiście koncepcyjnie najbardziej pasują do już istniejącej klasy (ale jeśli klasa powstaje tylko dla nich i wszystkie są statyczne -> namespace),
mutexy przy wielowątkowości/asynchroniczności, oraz przypadki, gdy statyczne elementy muszą współdziałać z szablonami/dziedziczeniem.
Pewnie wrócimy do static w klasach właśnie po pojawieniu się dziedziczenia. Mam nawet pomysł. :)



Przechodząc do zadania.

Tym razem ćwiczymy konstruktory, znaczenie this (to podpowiedź :)) i użycie const (ma być **wszędzie**, gdzie się da i ma to sens - włączając oznaczanie nim całych metod, które nie zmieniają pól klasy; będę się czepiać).

Zwracam uwagę, że proste typy, które mieszczą się w rejestrze procesora (int, char, float, double, wskaźniki) powinny być przekazywane przez wartość, bo wtedy procesor może bezpośrednio udostępnić rejestr, w którym się znajdują, z poziomu funkcji.
Utworzenie referencji nie zawsze jest darmowe (mimo, że semantycznie myślimy o niej jak o aliasie). W szczególności, przy przekazywaniu argumentów do funkcji, główne kompilatory (gcc, clang, MSVC) implementują ją pod maską jako wskaźnik.

Dla dużych typów (np. std::string, std::vector, struktury, klasy etc.) używamy zawsze referencji (jeśli to możliwe, stałej). 
Jedynym wyjątkiem jest zwracanie lokalnego obiektu, którego czas życia jest krótszy niż czas życia referencji (np. lokalną zmienną z funkcji zwracamy przez wartość).



Dodatkowo, ponieważ nagroda jest jedynie kontenerem na czyste dane i nie ma żadnej funkcjonalności, poza konstruktorami (jest tzw. POD - Plain Old Data), 
zaimplementujemy ją jako strukturę z publicznymi polami (i nazwami pól bez przyrostków) a nie klasę. Dokładnie tak, jak zrobilibyśmy to w czystym C. 

Oczywiście w C++ ta różnica jest czysto semantyczna (modulo domyślna widoczność pól), ale chodzi o jasne komunikowanie zamiarów - a za bezpieczeństwo odpowiada tu użycie const a nie interfejs.
To podejście jest czasem kontrowersyjne (niektórzy używają wyłącznie klas i ew. publicznych pól), ale spotkacie się z nim na tyle często, że chciałbym żebyście rozumieli ten styl i nie zastanawiali się czemu widzicie struct w C++. :)
Z drugiej strony, niektórzy puryści będą się kłócić, że to nie jest prawdziwy POD, bo std::string w środku ma konstruktor i nie jest prostym typem. :D

Cała reszta funkcjonalności będzie zaimplementowana w klasie Quest. Tutaj, z kolei, zmienne będą prywatne, a dostęp do nich będzie się odbywał przez odpowiedni interfejs.




Mała, ale potrzebna, dygresja - jeżeli dopiszemy do struktury/klasy jakikolwiek własny konstruktor, to kompilator nie wygeneruje nam automatycznie bezargumentowego, który tylko ustawia domyślne wartości pól
(co zrobiłby, gdybyśmy nie mieli żadnego konstruktora). 


Warto wiedzieć (poprawiam tekst i już widzę, że pisząc to wyprzedziłem wykład o 1 :P), że nie musimy tego robić ręcznie, wystarczy dopisać:

    Reward() = default;


Taki konstruktor jest nam często potrzebny, nie tylko by tworzyć domyślne obiekty bezpośrednio, ale też by używać rozwiązań, które go wymagają.
Na przykład, bez domyślnego konstruktora nie jesteśmy w stanie zrobić 

    Reward* rewards = new Reward[5];

bo new musi dla każdego elementu wywołać Reward(). 
Z drugiej strony, możemy bezproblemowo używać większości funkcjonalności std::vector, bo nie konstruuje on swoich elementów od razu (chyba, że chcemy).


Czasem chcemy też zasygnalizować (kompilatorowi i innym), że brak domyślnego konstruktora jest w pełni zamierzony. 
Wtedy możemy go explicite usunąć:

    Reward() = delete;

Obydwie sytuacje są efektywnie równoważne, ale w pierwszej konstruktor nie zostanie w ogóle utworzony, a w drugiej zostanie utworzony jako usunięty.
Generuje to dwie zupełnie różne wiadomości:

error: no matching function for call to ‘Reward::Reward()’ // ktoś inny może pomyśleć - ok, nie ma, czyli muszę ją dodać, żeby działało
error: use of deleted function ‘Reward::Reward()’ // wyraźnie widać, że zachowanie jest zamierzone


Dygresja 2 - chyba nie było to oficjalnie omówione, więc powiem, że std::string można łączyć przy użyciu operatora +.
Przy czym, przynajmniej jeden z dodawanych obiektów musi być typu string - jeśli zrobimy po prostu "Ala " + "ma kota", 
to obydwa zostaną zinterpretowane jako const char* i dostaniemy błąd o niezdefiniowanym operatorze +.

std::string a = "Ala "; 
std::string b = a + "ma kota"; 

jest już w pełni poprawne.


Wracając:

0) Pełny const correctness (będzie oceniany) + przekazywanie/zwracanie w odpowiedni sposób

1) Reward
- struct z trzema polami (doświadczenie, zapłata, otrzymane przedmioty)
- domyślny konstruktor ustawia pola na 0, 0, "", proszę go wygenerować automatycznie (patrz opis :))
- drugi konstruktor pozwala ustawić wszystkie pola jednocześnie i wymaga podania wszystkich trzech (brak wartości domyślnych)

2) Quest
- prywatne pola: nazwa (string), opis (string), nagroda (Reward)
- brak domyślnego konstruktora, wyraźnie sygnalizowany jako design choice (patrz opis :))
- główny konstruktor wymaga tylko nazwy i opisu, podanie nagrody jest opcjonalne i domyślnie jest pusta
- metody:
  * print - wypisuje informacje o queście
  * changeReward - zmienia nagrodę questa na podaną
  * addReward - dodaje do obecnej nagrody questa wartości z przekazanej nagrody
  * 
  * getName - zwraca nazwę questa w sposób uniemożliwiający jej zmianę, ale wydajny dla złożonych typów (czyli nie przez wartość :))
  * getDescription - zwraca opis questa w sposób uniemożliwiający jego zmianę, ale wydajny dla złożonych typów (czyli nie przez wartość :))
  * getReward - zwraca nagrodę questa w sposób uniemożliwiający jej zmianę, ale wydajny dla złożonych typów (czyli nie przez wartość :))

3) W trybie Debug (podpowiedź na początku opisu :))
- przy tworzeniu questa wypisuje komunikat o tworzeniu z adresem instancji (i ewentualnie woła print)
- przy destrukcji questa wypisuje komunikat o destrukcji z adresem instancji
- nie zostawia śladu w Release


Przykładowy output:

1) Release:

Quest: Zanieść rzepy Hildzie
Opis: Zbierz rzepę z pola Lobarta.
Nagroda: 50 punktów doświadczenia, 0 sztuk rudy, Otrzymane przedmioty: brak

Quest: Magiczny miecz Uriziel
Opis: Naładuj Uriziela energią z kopca magicznej rudy.
Nagroda: 7000 punktów doświadczenia, 10000 sztuk rudy, Otrzymane przedmioty: Naładowany Uriziel

Quest: Magiczny miecz Uriziel
Opis: Naładuj Uriziela energią z kopca magicznej rudy.
Nagroda: 7000 punktów doświadczenia, 10000 sztuk rudy, Otrzymane przedmioty: Fala Śmierci Uriziela

Quest: Wydzielina pełzaczy
Opis: Zdobądź 3 jaja pełzaczy dla Cor Kaloma.
Nagroda: 5500 punktów doświadczenia, 0 sztuk rudy, Otrzymane przedmioty: Esencja ducha; Esencja życia

Quest: Wydzielina pełzaczy
Opis: Zdobądź 3 jaja pełzaczy dla Cor Kaloma.
Nagroda: 5500 punktów doświadczenia, 100 sztuk rudy, Otrzymane przedmioty: Esencja ducha; Esencja życia; Łomotacz


2) Debug:

Jak wyżej, ale dodatkowo (oczywiście adresy będą inne i różne przy każdym uruchomieniu):

Quest instance created with address 0x7ffee3b6c710
Quest instance created with address 0x7ffee3b6c720
Quest instance created with address 0x7ffee3b6c730
Quest instance, with address 0x7ffee3b6c710, destroyed.
Quest instance, with address 0x7ffee3b6c720, destroyed.
Quest instance, with address 0x7ffee3b6c730, destroyed.

*/