#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>


using namespace std;


// Struktura węzła dla drzewa BST
struct ElementDrzewa {
    int wartosc;
    ElementDrzewa* lewy;
    ElementDrzewa* prawy;
};

class DrzewoBST {
private:
    ElementDrzewa* korzen;

public:
    DrzewoBST() : korzen(nullptr) {}

    void wstawElement(int wartosc) {
        // Tworzenie nowego węzła
        ElementDrzewa* nowyElement = new ElementDrzewa;
        nowyElement->wartosc = wartosc;
        nowyElement->lewy = nullptr;
        nowyElement->prawy = nullptr;

        if (korzen == nullptr) {
            korzen = nowyElement; // Korzeń staje się nowym elementem
        }
        else {
            ElementDrzewa* aktualny = korzen;
            while (true) {
                if (wartosc < aktualny->wartosc) {
                    if (aktualny->lewy == nullptr) {
                        aktualny->lewy = nowyElement; // Wstawianie do lewego poddrzewa
                        break;
                    }
                    else {
                        aktualny = aktualny->lewy; // Przechodzenie do lewego poddrzewa
                    }
                }
                else if (wartosc > aktualny->wartosc) {
                    if (aktualny->prawy == nullptr) {
                        aktualny->prawy = nowyElement; // Wstawianie do prawego poddrzewa
                        break;
                    }
                    else {
                        aktualny = aktualny->prawy; // Przechodzenie do prawego poddrzewa
                    }
                }
                else {
                    // Ignorowanie duplikatów
                    delete nowyElement;
                    break;
                }
            }
        }
    }

    void usunElement(int wartosc) {
        korzen = usunRekurencyjnie(korzen, wartosc);
    }

    void wyswietlDrzewo() {
        wyswietlRekurencyjnie(korzen);
    }

    bool znajdzElement(int wartosc) {
        ElementDrzewa* aktualny = korzen;

        while (aktualny != nullptr) {
            if (wartosc == aktualny->wartosc) {
                return true; // Element został znaleziony
            }
            else if (wartosc < aktualny->wartosc) {
                aktualny = aktualny->lewy; // Przechodzenie do lewego poddrzewa
            }
            else {
                aktualny = aktualny->prawy; // Przechodzenie do prawego poddrzewa
            }
        }

        return false; // Element nie został znaleziony
    }

private:
    ElementDrzewa* usunRekurencyjnie(ElementDrzewa* aktualny, int wartosc) {
        if (aktualny == nullptr) {
            return nullptr;
        }

        if (wartosc < aktualny->wartosc) {
            aktualny->lewy = usunRekurencyjnie(aktualny->lewy, wartosc); // Rekurencyjne usuwanie z lewego poddrzewa
        }
        else if (wartosc > aktualny->wartosc) {
            aktualny->prawy = usunRekurencyjnie(aktualny->prawy, wartosc); // Rekurencyjne usuwanie z prawego poddrzewa
        }
        else {
            if (aktualny->lewy == nullptr && aktualny->prawy == nullptr) {
                delete aktualny;
                return nullptr;
            }
            else if (aktualny->lewy == nullptr) {
                ElementDrzewa* temp = aktualny->prawy;
                delete aktualny;
                return temp;
            }
            else if (aktualny->prawy == nullptr) {
                ElementDrzewa* temp = aktualny->lewy;
                delete aktualny;
                return temp;
            }
            else {
                ElementDrzewa* nastepnik = znajdzNastepnik(aktualny->prawy);
                aktualny->wartosc = nastepnik->wartosc;
                aktualny->prawy = usunRekurencyjnie(aktualny->prawy, nastepnik->wartosc);
            }
        }

        return aktualny;
    }

    ElementDrzewa* znajdzNastepnik(ElementDrzewa* aktualny) {
        while (aktualny->lewy != nullptr) {
            aktualny = aktualny->lewy;
        }
        return aktualny;
    }

    void wyswietlRekurencyjnie(ElementDrzewa* aktualny) {
        if (aktualny != nullptr) {
            wyswietlRekurencyjnie(aktualny->lewy);
            cout << aktualny->wartosc << " ";
            wyswietlRekurencyjnie(aktualny->prawy);
        }
    }
};

struct Element      
{
    int wartosc;
    Element* nastepny;
    Element* lewy;
    Element* prawy;
};



class Lista {
private:
    Element* pierwszy;

public:
    Lista() : pierwszy(nullptr) {}

    // Wstawianie elementu na początek listy
    void wstawElementNaPoczatek(int wartosc) {
        // Tworzenie nowego elementu
        Element* nowyElement = new Element;
        nowyElement->wartosc = wartosc;
        nowyElement->nastepny = pierwszy;
        pierwszy = nowyElement;
    }

    // Wstawianie elementu na koniec listy
    void wstawElementNaKoniec(int wartosc) {
        // Tworzenie nowego elementu
        Element* nowyElement = new Element;
        nowyElement->wartosc = wartosc;
        nowyElement->nastepny = nullptr;

        if (pierwszy == nullptr) {
            pierwszy = nowyElement; // Jeżeli lista jest pusta, nowy element staje się pierwszym
        }
        else {
            Element* aktualny = pierwszy;
            while (aktualny->nastepny != nullptr) {
                aktualny = aktualny->nastepny; // Przechodzenie do końca listy
            }
            aktualny->nastepny = nowyElement; // Wstawianie nowego elementu na koniec
        }
    }

    // Wstawianie elementu po określonej wartości i indeksie
    void wstawElementPo(int wartosc, int wartoscPo, int indeks) {
        // Tworzenie nowego elementu
        Element* nowyElement = new Element;
        nowyElement->wartosc = wartosc;

        if (pierwszy == nullptr) {
            pierwszy = nowyElement; // Jeżeli lista jest pusta, nowy element staje się pierwszym
        }
        else {
            Element* aktualny = pierwszy;
            int obecnyIndeks = 0;

            while (aktualny != nullptr) {
                if (aktualny->wartosc == wartoscPo) {
                    if (indeks == obecnyIndeks) {
                        nowyElement->nastepny = aktualny->nastepny; // Wstawianie nowego elementu
                        aktualny->nastepny = nowyElement;
                        break;
                    }
                    obecnyIndeks++;
                }

                aktualny = aktualny->nastepny; // Przechodzenie do następnego elementu
            }
        }
    }

    // Usuwanie elementu z listy
    void usunElement(int wartosc) {
        if (pierwszy == nullptr) {
            return; // Jeżeli lista jest pusta, nie ma elementów do usunięcia
        }

        if (pierwszy->wartosc == wartosc) {
            Element* temp = pierwszy;
            pierwszy = pierwszy->nastepny; // Usuwanie pierwszego elementu
            delete temp;
        }
        else {
            Element* aktualny = pierwszy;
            while (aktualny->nastepny != nullptr) {
                if (aktualny->nastepny->wartosc == wartosc) {
                    Element* temp = aktualny->nastepny;
                    aktualny->nastepny = temp->nastepny; // Usuwanie elementu ze środka listy
                    delete temp;
                    break;
                }
                aktualny = aktualny->nastepny; // Przechodzenie do następnego elementu
            }
        }
    }

    // Wyszukiwanie elementu w liście
    bool znajdzElement(int wartosc) {
        Element* aktualny = pierwszy;

        while (aktualny != nullptr) {
            if (aktualny->wartosc == wartosc) {
                return true; // Element został znaleziony
            }

            aktualny = aktualny->nastepny; // Przechodzenie do następnego elementu
        }

        return false; // Element nie został znaleziony
    }

    // Wyświetlanie zawartości listy
    void wyswietlListe() {
        Element* aktualny = pierwszy;
        while (aktualny != nullptr) {
            cout << aktualny->wartosc << " "; // Wyświetlanie wartości elementu
            aktualny = aktualny->nastepny; // Przechodzenie do następnego elementu
        }
        cout << endl;
    }
};

// Klasa reprezentująca tablicę
class Tablica {
private:
    int* tablica; // Wskaźnik na tablicę
    int rozmiar; // Aktualny rozmiar tablicy

public:
    // Konstruktor domyślny
    Tablica() : tablica(nullptr), rozmiar(0) {}

    // Wstawianie elementu na początek tablicy
    void wstawElementNaPoczatek(int wartosc) {
        // Tworzenie nowej tablicy o rozmiarze większym o 1 od aktualnej
        int* nowaTablica = new int[rozmiar + 1];
        nowaTablica[0] = wartosc;
        // Przenoszenie elementów z poprzedniej tablicy do nowej, przesuwając je o 1 indeks w prawo
        for (int i = 0; i < rozmiar; i++) {
            nowaTablica[i + 1] = tablica[i];
        }
        delete[] tablica; // Usuwanie poprzedniej tablicy
        tablica = nowaTablica; // Przypisanie nowej tablicy
        rozmiar++; // Zwiększenie rozmiaru tablicy
    }

    // Wstawianie elementu na koniec tablicy
    void wstawElementNaKoniec(int wartosc) {
        // Tworzenie nowej tablicy o rozmiarze większym o 1 od aktualnej
        int* nowaTablica = new int[rozmiar + 1];
        // Przenoszenie elementów z poprzedniej tablicy do nowej
        for (int i = 0; i < rozmiar; i++) {
            nowaTablica[i] = tablica[i];
        }
        nowaTablica[rozmiar] = wartosc;
        delete[] tablica; 
        tablica = nowaTablica; 
        rozmiar++; 
    }

    // Wstawianie elementu na losową pozycję w tablicy
    void wstawElementNaLosowaPozycje(int wartosc) {
        if (rozmiar == 0) {
            wstawElementNaKoniec(wartosc); // Jeżeli tablica jest pusta, wstaw element na koniec
        }
        else {
            int losowaPozycja = rand() % rozmiar; // Generowanie losowej pozycji
            int* nowaTablica = new int[rozmiar + 1];
            // Przenoszenie elementów z poprzedniej tablicy do nowej do momentu osiągnięcia losowej pozycji
            for (int i = 0; i < losowaPozycja; i++) {
                nowaTablica[i] = tablica[i];
            }
            nowaTablica[losowaPozycja] = wartosc; // Wstawianie elementu na losową pozycję
            // Przenoszenie pozostałych elementów z poprzedniej tablicy do nowej, przesuwając je o 1 indeks w prawo
            for (int i = losowaPozycja; i < rozmiar; i++) {
                nowaTablica[i + 1] = tablica[i];
            }
            delete[] tablica; // Usuwanie poprzedniej tablicy
            tablica = nowaTablica; // Przypisanie nowej tablicy
            rozmiar++; // Zwiększenie rozmiaru tablicy
        }
    }

    // Usuwanie elementu z tablicy
    void usunElement(int wartosc) {
        if (rozmiar == 0) {
            return; // Jeżeli tablica jest pusta, zakończ funkcję
        }

        int* nowaTablica = new int[rozmiar - 1];
        int indeks = 0;
        bool usunieto = false;

        for (int i = 0; i < rozmiar; i++) {
            if (tablica[i] != wartosc) {
                nowaTablica[indeks] = tablica[i]; // Przenoszenie elementów, które nie są równoważne wartości do usunięcia
                indeks++;
            }
            else {
                usunieto = true;
            }
        }

        delete[] tablica; // Usuwanie poprzedniej tablicy
        tablica = nowaTablica; // Przypisanie nowej tablicy
        if (usunieto) {
            rozmiar--; // Zmniejszenie rozmiaru tablicy, jeżeli usunięto element
        }
    }

    // Wyszukiwanie elementu w tablicy
    bool znajdzElement(int wartosc) {
        for (int i = 0; i < rozmiar; i++) {
            if (tablica[i] == wartosc) {
                return true; // Element został znaleziony
            }
        }

        return false; // Element nie został znaleziony
    }

    // Wyświetlanie zawartości tablicy
    void wyswietlTablice() {
        for (int i = 0; i < rozmiar; i++) {
            cout << tablica[i] << " ";
        }
        cout << endl;
    }
};

// Funkcja wczytująca dane z pliku do struktur danych
void wczytajDaneDoStruktur(string nazwaPliku, DrzewoBST& drzewo, Lista& lista, Tablica& tablica) {
    ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        int wartosc;
        while (plik >> wartosc) {
            drzewo.wstawElement(wartosc); // Wstawianie elementu do drzewa BST
            lista.wstawElementNaPoczatek(wartosc); // Wstawianie elementu na początek listy
            tablica.wstawElementNaKoniec(wartosc); // Wstawianie elementu na koniec tablicy
        }
        plik.close();
    }
    else {
        cout << "Nie można otworzyć pliku " << nazwaPliku << endl;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    DrzewoBST bst;
    Lista lista;
    Tablica tablica;

    int wyborOperacji;
    int wyborStruktury;

    do
    {
        cout << "Wybierz operacje:" << endl;
        cout << "1. Dodaj element" << endl;
        cout << "2. Usun element" << endl;
        cout << "3. Wyswietl strukture" << endl;
        cout << "4. Znajdz element" << endl;
        cout << "5. Wprowadz dane do struktur" << endl;
        cout << "0. Wyjdz" << endl;
        cout << "Wybor operacji: ";
        cin >> wyborOperacji;

        switch (wyborOperacji)
        {
        case 1:
        {
            cout << "Wybierz strukture:" << endl;
            cout << "1. Drzewo BST" << endl;
            cout << "2. Lista" << endl;
            cout << "3. Tablica" << endl;
            cout << "Wybor struktury: ";
            cin >> wyborStruktury;

            int wartosc;
            int wartoscPo = 0;
            cout << "Podaj wartosc: ";
            cin >> wartosc;

            switch (wyborStruktury)
            {
            case 1:
            {
                auto startBST = chrono::high_resolution_clock::now();
                bst.wstawElement(wartosc);
                auto endBST = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationBST = endBST - startBST;
                cout << "Czas dodawania elementu do Drzewa BST: " << durationBST.count() << " ms" << endl;
                break;
            }
            case 2:
            {
                int wyborMiejsca;
                cout << "Wybierz miejsce wstawienia:" << endl;
                cout << "1. Poczatek" << endl;
                cout << "2. Koniec" << endl;
                cout << "3. Po indeksie" << endl;
                cout << "Wybor miejsca: ";
                cin >> wyborMiejsca;

                switch (wyborMiejsca)
                {
                case 1:
                {
                    auto startLista = chrono::high_resolution_clock::now();
                    lista.wstawElementNaPoczatek(wartosc);
                    auto endLista = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationLista = endLista - startLista;
                    cout << "Czas wykonania operacji na Liscie (wstawienie na poczatek): " << durationLista.count() << " ms" << endl;
                    break;
                }
                case 2:
                {
                    auto startLista = chrono::high_resolution_clock::now();
                    lista.wstawElementNaKoniec(wartosc);
                    auto endLista = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationLista = endLista - startLista;
                    cout << "Czas wykonania operacji na Liscie (wstawienie na koniec): " << durationLista.count() << " ms" << endl;
                    break;
                }
                case 3:
                {
                    int indeks;
                    cout << "Podaj indeks: ";
                    cin >> indeks;
                    auto startLista = chrono::high_resolution_clock::now();
                    lista.wstawElementPo(wartosc, wartoscPo, indeks);
                    auto endLista = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationLista = endLista - startLista;
                    cout << "Czas wykonania operacji na Liscie (wstawienie po indeksie): " << durationLista.count() << " ms" << endl;
                    break;
                }
                default:
                    cout << "Niepoprawny wybor miejsca." << endl;
                    break;
                }
                break;
            }
            case 3:
            {
                int wyborMiejsca;
                cout << "Wybierz miejsce wstawienia:" << endl;
                cout << "1. Poczatek" << endl;
                cout << "2. Koniec" << endl;
                cout << "3. Losowe" << endl;
                cout << "Wybor miejsca: ";
                cin >> wyborMiejsca;

                switch (wyborMiejsca)
                {
                case 1:
                {
                    auto startTablica = chrono::high_resolution_clock::now();
                    tablica.wstawElementNaPoczatek(wartosc);
                    auto endTablica = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationTablica = endTablica - startTablica;
                    cout << "Czas wykonania operacji na Tablicy (wstawienie na poczatek): " << durationTablica.count() << " ms" << endl;
                    break;
                }
                case 2:
                {
                    auto startTablica = chrono::high_resolution_clock::now();
                    tablica.wstawElementNaKoniec(wartosc);
                    auto endTablica = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationTablica = endTablica - startTablica;
                    cout << "Czas wykonania operacji na Tablicy (wstawienie na koniec): " << durationTablica.count() << " ms" << endl;
                    break;
                }
                case 3:
                {
                    auto startTablica = chrono::high_resolution_clock::now();
                    tablica.wstawElementNaLosowaPozycje(wartosc);
                    auto endTablica = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> durationTablica = endTablica - startTablica;
                    cout << "Czas wykonania operacji na Tablicy (wstawienie losowe): " << durationTablica.count() << " ms" << endl;
                    break;
                }
                default:
                    cout << "Niepoprawny wybor miejsca." << endl;
                    break;
                }
                break;
            }
            default:
                cout << "Niepoprawny wybor struktury." << endl;
                break;
            }
            break;
        }
        case 2:
        {
            cout << "Wybierz strukture:" << endl;
            cout << "1. Drzewo BST" << endl;
            cout << "2. Lista" << endl;
            cout << "3. Tablica" << endl;
            cout << "Wybor struktury: ";
            cin >> wyborStruktury;

            int wartosc;
            cout << "Podaj wartosc: ";
            cin >> wartosc;

            switch (wyborStruktury)
            {
            case 1:
            {
                auto startBST = chrono::high_resolution_clock::now();
                bst.usunElement(wartosc);
                auto endBST = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationBST = endBST - startBST;
                cout << "Czas usuwania elementu w Drzewie BST: " << durationBST.count() << " ms" << endl;
                break;
            }
            case 2:
            {
                auto startLista = chrono::high_resolution_clock::now();
                lista.usunElement(wartosc);
                auto endLista = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationLista = endLista - startLista;
                cout << "Czas usuwania elementu w Liscie: " << durationLista.count() << " ms" << endl;
                break;
            }
            case 3:
            {
                auto startTablica = chrono::high_resolution_clock::now();
                tablica.usunElement(wartosc);
                auto endTablica = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationTablica = endTablica - startTablica;
                cout << "Czas usuwania elementu w Tablicy: " << durationTablica.count() << " ms" << endl;
                break;
            }
            default:
                cout << "Niepoprawny wybor struktury." << endl;
                break;
            }
            break;
        }
        case 3:
        {
            cout << "Wybierz strukture:" << endl;
            cout << "1. Drzewo BST" << endl;
            cout << "2. Lista" << endl;
            cout << "3. Tablica" << endl;
            cout << "Wybor struktury: ";
            cin >> wyborStruktury;

            switch (wyborStruktury)
            {
            case 1:
            {
                bst.wyswietlDrzewo();
                break;
            }
            case 2:
            {
                lista.wyswietlListe();
                break;
            }
            case 3:
            {
                tablica.wyswietlTablice();
                break;
            }
            default:
                cout << "Niepoprawny wybor struktury." << endl;
                break;
            }
            break;
        }
        case 4:
        {
            cout << "Wybierz strukture:" << endl;
            cout << "1. Drzewo BST" << endl;
            cout << "2. Lista" << endl;
            cout << "3. Tablica" << endl;
            cout << "Wybor struktury: ";
            cin >> wyborStruktury;

            int wartosc;
            cout << "Podaj wartosc: ";
            cin >> wartosc;

            switch (wyborStruktury)
            {
            case 1:
            {
                auto startBST = chrono::high_resolution_clock::now();
                bool znaleziono = bst.znajdzElement(wartosc);
                auto endBST = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationBST = endBST - startBST;
                cout << "Czas szukania w Drzewie BST: " << durationBST.count() << " ms" << endl;
                cout << "Czy znaleziono element: " << (znaleziono ? "Tak" : "Nie") << endl;
                break;
            }
            case 2:
            {
                auto startLista = chrono::high_resolution_clock::now();
                bool znaleziono = lista.znajdzElement(wartosc);
                auto endLista = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationLista = endLista - startLista;
                cout << "Czas szukania elementu w Liscie: " << durationLista.count() << " ms" << endl;
                cout << "Czy znaleziono element: " << (znaleziono ? "Tak" : "Nie") << endl;
                break;
            }
            case 3:
            {
                auto startTablica = chrono::high_resolution_clock::now();
                bool znaleziono = tablica.znajdzElement(wartosc);
                auto endTablica = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationTablica = endTablica - startTablica;
                cout << "Czas szukania elementu w Tablicy: " << durationTablica.count() << " ms" << endl;
                cout << "Czy znaleziono element: " << (znaleziono ? "Tak" : "Nie") << endl;
                break;
            }
            default:
                cout << "Niepoprawny wybor struktury." << endl;
                break;
            }
            break;
        }
        case 5:
        {
            string nazwaPliku;
            cout << "Podaj nazwe pliku: ";
            cin >> nazwaPliku;
            wczytajDaneDoStruktur(nazwaPliku, bst, lista, tablica);
            break;
        }
        case 0:
            cout << "Koniec programu." << endl;
            break;
        default:
            cout << "Niepoprawny wybor operacji." << endl;
            break;
        }

        cout << endl;

    } while (wyborOperacji != 0);

    return 0;
}


