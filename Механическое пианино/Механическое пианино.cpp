#include <iostream>
#include <string>

enum Note {
    DO = 1,    // 1 << 0
    RE = 2,    // 1 << 1
    MI = 4,    // 1 << 2
    FA = 8,    // 1 << 3
    SOL = 16,  // 1 << 4
    LA = 32,   // 1 << 5
    SI = 64    // 1 << 6
};

void playChord(int notes) {
    if (notes & DO) {
        std::cout << "DO ";
    }
    if (notes & RE) {
        std::cout << "RE ";
    }
    if (notes & MI) {
        std::cout << "MI ";
    }
    if (notes & FA) {
        std::cout << "FA ";
    }
    if (notes & SOL) {
        std::cout << "SOL ";
    }
    if (notes & LA) {
        std::cout << "LA ";
    }
    if (notes & SI) {
        std::cout << "SI ";
    }
    std::cout << std::endl;
}

int main() {
    std::string input;
    std::cout << "Enter chord (numbers 1 to 7): ";
    std::cin >> input;

    int chordMask = 0;

    for (char ch : input) {
        int noteIndex = ch - '1'; // Преобразуем символ в индекс (0-6)
        if (noteIndex >= 0 && noteIndex < 7) {
            chordMask |= (1 << noteIndex); // Устанавливаем соответствующий бит
        }
    }

    std::cout << "Formed chord: ";
    playChord(chordMask);

    return 0;
}