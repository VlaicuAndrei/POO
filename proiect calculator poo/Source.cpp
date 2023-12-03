// Main.cpp
#include "CalculatorWithHistory.h"
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
#include <cmath>
#include <string> 

using namespace std;


void removeZeroes(double number, char* result, int bufLen) {
    int written = snprintf(result, bufLen, "%.15g", number);
    bool dotFound = false;
    int lastZero = -1;

    for (int i = 0; i < written; ++i) {
        if (result[i] == '.') {
            dotFound = true;
        }
        else if (dotFound && result[i] == '0') {
            lastZero = i;
        }
        else {
            lastZero = -1;
        }
    }

    if (lastZero != -1) {
        result[lastZero] = '\0';
        if (result[lastZero - 1] == '.') {
            result[lastZero - 1] = '\0';
        }
    }
}

int main() {
    CalculatorWithHistory Calculator("initializare cu o expresie");
    string expression;
    while (true) {
        cout << "Introduceti expresia matematica ('exit' pentru a iesi): ";
        getline(cin, expression);
        if (expression == "exit") {
            break;
        }
        Calculator.setExpression(expression);
        double result = Calculator.evaluateExpression();
        char formattedResult[256];
        removeZeroes(result, formattedResult, sizeof(formattedResult));

        cout << "Rezultatul expresiei este: " << formattedResult << std::endl;
        cout << "Expresie: " << Calculator.getExpression() << std::endl;
        cout << "Istoric: " << Calculator.getExpressionHistory() << std::endl;
    }
    cout << "Programul s-a incheiat.\n";
    return 0;
}
