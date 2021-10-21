#pragma once

#include <iostream>
#include  <string>
#include "TStack.h"

using namespace std;

class TCalculator
{
	string expr;
	string postfix = "1 2 5 + 4 3 - * /";
	//TStack<char> st_char;
	TStack<double> st_double;

public:
	TCalculator(string _expr = "1/((2+5)*(4-3))") : expr(_expr){}
	TCalculator(const TCalculator& cal) : expr(cal.expr), postfix(cal.postfix) {}
	bool CheckExpression(); //проверка корректности
	double Calc();
};
