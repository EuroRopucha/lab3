#include <iostream>
#include "ExpressionCalculator.h"
using namespace std;

int main() {
    //string input;
    //getline(std::cin, input);

    string expression = "3 + 4 * 2";

    try {
        ExpressionCalculator calc;
        int result = calc.calculate("3+14 * 2");
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

