#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

// Функции для выполнения операций
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    return a / b;
}

// Функция для удаления пробелов из строки
std::string removeSpaces(const std::string& input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

int main() {
    std::string buffer;
    std::cout << "Enter an expression in the format <number1> <operator> <number2>: ";
    std::getline(std::cin, buffer);

    buffer = removeSpaces(buffer);

    std::stringstream buffer_stream(buffer);

    double a, b;
    char operation;

    buffer_stream >> a >> operation >> b;

    if (buffer_stream.fail() || !buffer_stream.eof()) {
        std::cerr << "Input error. Please check the format of the expression." << std::endl;
        return 1;
    }

    // Выполнение операции и вывод результата
    std::cout << std::fixed << std::setprecision(3); // Точность вывода
    try {
        switch (operation) {
        case '+':
            std::cout << "Result: " << add(a, b) << std::endl;
            break;
        case '-':
            std::cout << "Result: " << subtract(a, b) << std::endl;
            break;
        case '*':
            std::cout << "Result: " << multiply(a, b) << std::endl;
            break;
        case '/':
            std::cout << "Result: " << divide(a, b) << std::endl;
            break;
        default:
            std::cerr << "Error: Invalid operation." << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
