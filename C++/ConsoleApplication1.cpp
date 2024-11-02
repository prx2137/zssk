#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void generateRandomNumbersToFile(const std::string& filename, int count) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Błąd otwarcia pliku." << std::endl;
        return;
    }

    // Ustawienie ziarna dla generatora liczb losowych
    std::srand(std::time(nullptr));

    // Zapisanie liczby elementów do pliku
    file << count << std::endl;

    // Generowanie i zapisywanie losowych liczb do pliku
    for (int i = 0; i < count; i++) {
        int number = std::rand();
        file << number << std::endl;
    }

    file.close();

    std::cout << "Wygenerowano i zapisano " << count << " liczb do pliku: " << filename << std::endl;
}

int main() {
    std::string filename = "liczby5000.txt";
    int count;

    std::cout << "Podaj liczbę liczb do wygenerowania i zapisa do pliku: ";
    std::cin >> count;

    generateRandomNumbersToFile(filename, count);

    return 0;
}
