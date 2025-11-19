#include <iostream>
#include "ExpressionCalculator.h"

int main() {
    std::string input;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, input);

    try {
        ExpressionCalculator calc;
        int result = calc.calculate(input);
        std::cout << "Результат: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}

