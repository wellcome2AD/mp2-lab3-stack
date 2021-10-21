
#include <iostream>
#include <string>
#include "TCalculator.h"

using namespace std;

bool TCalculator::CheckExpression()
{
	return true;
}

double TCalculator::Calc()
{
	double a, b;

	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] <= '9' && postfix[i] >= '0')
			st_double.Push(stod(&postfix[i]));
		else
			if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
			{
				b = st_double.Pop();
				a = st_double.Pop();

				switch (postfix[i])
				{
				case '+':
					st_double.Push(a + b);
					break;
				case '-':
					st_double.Push(a - b);
					break;
				case '*':
					st_double.Push(a * b);
					break;
				case '/':
					st_double.Push(a / b);
					break;
				}
			}
	}
	
	return st_double.Pop();
}
