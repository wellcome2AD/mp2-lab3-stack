#include <iostream>
#include <string>
#include "TCalculator.h"

using namespace std;

int main()
{
	TCalculator calc;
	calc.SetExpr("2 + 2");
	calc.ToPostfix();
	cout << calc.GetPostfix() << '\n';
	//cout << calc.Calc() << '\n';
}