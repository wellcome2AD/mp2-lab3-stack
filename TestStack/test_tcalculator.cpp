#include "../mp2-lab3-stack/TCalculator.h"
#include "gtest.h"

//can evaluate simple expression

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator(""));
}

TEST(TCalculator, can_set_expression)
{
	TCalculator calc;
	ASSERT_NO_THROW(calc.SetExpr("2 + 2"));
}

TEST(TCalculator, can_check_brackets_in_correct_expression)
{
	TCalculator calc;
	calc.SetExpr("((2) + (2))");
	ASSERT_EQ(calc.CheckBracketsNum(), true);
}

TEST(TCalculator, can_check_brackets_in_incorrect_expression)
{
	TCalculator calc;
	calc.SetExpr("(2) + (2))");
	ASSERT_EQ(calc.CheckBracketsNum(), false);
}

TEST(TCalculator, can_get_postfix_of_correct_expr)
{
	TCalculator calc("2 + 2 / 3 * 4");
	if (calc.CheckBracketsNum())
		calc.ToPostfix();
	string postfix = "2.000000 2.000000 3.000000 / 4.000000 * + ";
	ASSERT_EQ(calc.GetPostfix(), postfix);
}

TEST(TCalculator, can_calculate_sum)
{
	TCalculator calc("2+2");
	double answ = calc.Calc();
	double answ1 = 2.0 + 2.0;
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_sub)
{
	TCalculator calc("5-2");
	double answ = calc.Calc();
	double answ1 = 5.0 - 2.0;
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_mul)
{
	TCalculator calc("2*2");
	double answ = calc.Calc();
	double answ1 = 2.0 * 2.0;
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_div)
{
	TCalculator calc("10/2");
	double answ = calc.Calc();
	double answ1 = 10.0 / 2.0;
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_degree)
{
	TCalculator calc("2.9^0.5");
	double answ = calc.Calc();
	double answ1 = pow(2.9, 0.5);
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_sin)
{
	TCalculator calc("sin(2.9)");
	double answ = calc.Calc();
	double answ1 = sin(2.9);
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_cos)
{
	TCalculator calc("cos(2.9)");
	double answ = calc.Calc();
	double answ1 = cos(2.9);
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_tan)
{
	TCalculator calc("tg(2.9)");
	double answ = calc.Calc();
	double answ1 = tan(2.9);
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, can_calculate_correct_complex_expr)
{
	TCalculator calc("1 / 3 * (2 + 5 - 7) + sin(69) * cos(5)");
	double answ = calc.Calc();
	double answ1 = 1.0 / 3.0 * (2.0 + 5.0 - 7.0) + sin(69) * cos(5);
	ASSERT_EQ(answ, answ1);
}

TEST(TCalculator, cant_calculate_expr_with_too_many_brackets)
{
	TCalculator calc("1 / 3 * (2 + 5 - 7))");
	ASSERT_ANY_THROW(calc.Calc(););
}

TEST(TCalculator, cant_calculate_incorrect_expr)
{
	TCalculator calc("sin(a)");
	ASSERT_ANY_THROW(calc.Calc(););
}