#include <gtest/gtest.h>
#include "calculator-math.h"

TEST(AdditionTest, AddReturnsCorrect) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::addition(2, 3, &result), CalculatorMath::ERR_NONE);
  EXPECT_EQ(result, 5);
}

TEST(AdditionTest, AddNullptrResult) {
  EXPECT_EQ(CalculatorMath::addition(2, 3, nullptr), CalculatorMath::ERR_INVALID_ARGUMENTS);
}

TEST(AdditionTest, AddOverflowResult) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::addition(INT_MAX, 1, &result), CalculatorMath::ERR_OVERFLOW);
}

TEST(SubtractionTest, SubReturnsCorrect) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::subtraction(10, 4, &result), CalculatorMath::ERR_NONE);
  EXPECT_EQ(result, 6);
}

TEST(SubtractionTest, SubNullptrResult) {
  EXPECT_EQ(CalculatorMath::subtraction(10, 4, nullptr), CalculatorMath::ERR_INVALID_ARGUMENTS);
}

TEST(SubtractionTest, SubOverflowResult) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::subtraction(INT_MIN, 1, &result), CalculatorMath::ERR_OVERFLOW);
}

TEST(MultiplicationTest, MultReturnsCorrect) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::multiplication(5, 7, &result), CalculatorMath::ERR_NONE);
  EXPECT_EQ(result, 35);
}

TEST(MultiplicationTest, MultNullptrResult) {
  EXPECT_EQ(CalculatorMath::multiplication(10, 4, nullptr), CalculatorMath::ERR_INVALID_ARGUMENTS);
}

TEST(MultiplicationTest, MultOverflowResult) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::multiplication(INT_MAX, 2, &result), CalculatorMath::ERR_OVERFLOW);
}

TEST(DivisionTest, DivideCorrect) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::division(10, 2, &result), CalculatorMath::ERR_NONE);
  EXPECT_EQ(result, 5);
}

TEST(DivisionTest, DivideByZero) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::division(10, 0, &result), CalculatorMath::ERR_DIV_ZERO);
}

TEST(DivisionTest, DivideOverflowResult) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::division(INT_MIN, -1, &result), CalculatorMath::ERR_OVERFLOW);
}


TEST(FactorialTest, FactorialNLessZero) {
  int result = 0;
  EXPECT_EQ(CalculatorMath::factorial(5, &result), CalculatorMath::ERR_NONE);
  EXPECT_EQ(result, 120);
}
