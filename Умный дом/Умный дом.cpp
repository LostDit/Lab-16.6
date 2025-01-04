#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>

// Перечисление для управления переключателями
enum Switches {
    POWER = 1,
    LIGHTS_INSIDE = 2,
    LIGHTS_OUTSIDE = 4,
    HEATERS = 8,
    WATER_PIPE_HEATING = 16,
    CONDITIONER = 32
};

// Функция для обновления цветовой температуры
void updateColorTemperature(int hour, int& colorTemp) {
    if (hour >= 16 && hour <= 20) {
        float factor = (hour - 16) / 4.0f;
        colorTemp = static_cast<int>(5000 - factor * (5000 - 2700));
    }
    else if (hour == 0) {
        colorTemp = 5000;
    }
}

// Проверка на корректность ввода
bool isValidInput(const std::string& input, int& tempInside, int& tempOutside, std::string& movementInput, std::string& lightsInput) {
    std::stringstream ss(input);
    if (!(ss >> tempInside >> tempOutside >> movementInput >> lightsInput)) {
        return false;
    }
    if (movementInput != "yes" && movementInput != "no") {
        return false;
    }
    if (lightsInput != "on" && lightsInput != "off") {
        return false;
    }
    return true;
}

// Основная логика обработки состояния дома
void processState(int hour, int& switchesState, int tempInside, int tempOutside, bool movement, bool lightsInside, int& colorTemp) {
    // Логика управления устройствами
    if (tempOutside < 0) {
        if (!(switchesState & WATER_PIPE_HEATING)) {
            switchesState |= WATER_PIPE_HEATING;
            std::cout << "Water pipe heating ON!" << std::endl;
        }
    }
    else if (tempOutside > 5) {
        if (switchesState & WATER_PIPE_HEATING) {
            switchesState &= ~WATER_PIPE_HEATING;
            std::cout << "Water pipe heating OFF!" << std::endl;
        }
    }

    if (hour >= 16 || hour < 5) {
        if (movement) {
            if (!(switchesState & LIGHTS_OUTSIDE)) {
                switchesState |= LIGHTS_OUTSIDE;
                std::cout << "Outside lights ON!" << std::endl;
            }
        }
        else if (switchesState & LIGHTS_OUTSIDE) {
            switchesState &= ~LIGHTS_OUTSIDE;
            std::cout << "Outside lights OFF!" << std::endl;
        }
    }
    else if (switchesState & LIGHTS_OUTSIDE) {
        switchesState &= ~LIGHTS_OUTSIDE;
        std::cout << "Outside lights OFF!" << std::endl;
    }

    if (tempInside < 22) {
        if (!(switchesState & HEATERS)) {
            switchesState |= HEATERS;
            std::cout << "Heaters ON!" << std::endl;
        }
    }
    else if (tempInside >= 25) {
        if (switchesState & HEATERS) {
            switchesState &= ~HEATERS;
            std::cout << "Heaters OFF!" << std::endl;
        }
    }

    if (tempInside >= 30) {
        if (!(switchesState & CONDITIONER)) {
            switchesState |= CONDITIONER;
            std::cout << "Conditioner ON!" << std::endl;
        }
    }
    else if (tempInside <= 25) {
        if (switchesState & CONDITIONER) {
            switchesState &= ~CONDITIONER;
            std::cout << "Conditioner OFF!" << std::endl;
        }
    }

    if (lightsInside) {
        updateColorTemperature(hour, colorTemp);
        std::cout << "Color temperature: " << colorTemp << "K" << std::endl;
    }
}

int main() {
    int switchesState = 0;
    int colorTemp = 5000;

    for (int day = 1; day <= 2; ++day) {
        std::cout << "Day " << day << std::endl;
        for (int hour = 0; hour < 24; ++hour) {
            int tempInside, tempOutside;
            std::string movementInput, lightsInput;

            std::cout << "Time: " << std::setw(2) << std::setfill('0') << hour << ":00" << std::endl;
            std::cout << "Temperature inside, temperature outside, movement (yes/no), lights (on/off): ";

            std::string input;
            std::getline(std::cin, input);

            // Проверка на корректность ввода
            if (!isValidInput(input, tempInside, tempOutside, movementInput, lightsInput)) {
                std::cout << "Invalid input. Please enter data in the correct format: <temp_inside> <temp_outside> <movement yes/no> <lights on/off>" << std::endl;
                --hour; // Повторить текущий час
                continue;
            }

            bool movement = (movementInput == "yes");
            bool lightsInside = (lightsInput == "on");

            processState(hour, switchesState, tempInside, tempOutside, movement, lightsInside, colorTemp);
        }
    }

    return 0;
}
