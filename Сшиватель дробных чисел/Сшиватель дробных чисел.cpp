#include <iostream>
#include <string>
#include <iomanip>

// Функция для объединения целой и дробной частей в одно число
double combineParts(const std::string& wholePart, const std::string& fractionalPart) {
    std::string combined = wholePart + "." + fractionalPart;
    try {
        return std::stod(combined);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 0.0;
    }
}

// Функция для ввода числовой строки
std::string getNumberPart(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        getline(std::cin, input);

        if (!input.empty() && input.find_first_not_of("0123456789") == std::string::npos) {
            return input;
        }
        std::cout << "Invalid input. Please try again.\n";
    }
}

int main() {
    std::locale::global(std::locale("C"));

    std::string wholePart = getNumberPart("Enter the integer part of the number: ");
    std::string fractionalPart = getNumberPart("Enter the fractional part of the number: ");

    double result = combineParts(wholePart, fractionalPart);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "The resulting number: " << result << "\n";

    return 0;
}