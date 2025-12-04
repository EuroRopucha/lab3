
#include "ExpressionCalculator.h"

#include <gtest.h>


// Базовые операции
TEST(ExpressionCalculator, can_add_numbers) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("2 + 3"), 5);
}

TEST(ExpressionCalculator, can_subtract_numbers) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("10 - 4"), 6);
}

TEST(ExpressionCalculator, can_multiply_numbers) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("7 * 6"), 42);
}

TEST(ExpressionCalculator, can_divide_numbers) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("20 / 5"), 4);
}

// Скобки и приоритет
TEST(ExpressionCalculator, respects_operator_precedence) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("2 + 3 * 4"), 14);
}

TEST(ExpressionCalculator, can_handle_parentheses) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("(2 + 3)*4"), 20);
}

// Унарный минус
TEST(ExpressionCalculator, can_handle_unary_minus_at_start) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("-3 + 2"), -1);
}

TEST(ExpressionCalculator, can_handle_unary_minus_in_parentheses) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("-(4 * 2)"), -8);
}

// Ошибки
TEST(ExpressionCalculator, throws_on_division_by_zero) {
	ExpressionCalculator calc;
	EXPECT_THROW(calc.calculate("5 / 0"), std::invalid_argument);
}

// Унарный минус перед скобками
TEST(ExpressionCalculator, can_handle_unary_minus_before_parentheses) {
	ExpressionCalculator calc;
	EXPECT_EQ(calc.calculate("-(2 + 3) * 4"), -20);
}

// Проверка на лишние операнды (ошибка)
TEST(ExpressionCalculator, throws_on_extra_operands) {
	ExpressionCalculator calc;
	EXPECT_THROW(calc.calculate("3 3 +"), std::invalid_argument);
}
