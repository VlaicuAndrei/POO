// CalculatorWithHistory.h
#pragma once
#include "ScientificCalculator.h"

class CalculatorWithHistory : public ScientificCalculator {
public:
    CalculatorWithHistory();
    CalculatorWithHistory(const std::string& expr);
    ~CalculatorWithHistory();

    double evaluateExpression() override;

    bool operator==(const CalculatorWithHistory& other) const;
    bool operator!() const;

    const char* getExpressionHistory() const;
    void setExpressionHistory(const char* newHistory);

    friend std::ostream& operator<<(std::ostream& out, const CalculatorWithHistory& calcWithHistory);
    friend std::istream& operator>>(std::istream& in, CalculatorWithHistory& calcWithHistory);

private:
    char* expressionHistory;
    bool isValidHistory(const char* history) const;
    void appendToHistory(const char* expression);
    void copyFrom(const CalculatorWithHistory& other);
};

