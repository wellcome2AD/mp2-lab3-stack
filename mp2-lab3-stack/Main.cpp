#include <iostream>
#include <string>
#include "TCalculator.h"
#include "TStack.h"

using namespace std;

int main()
{
	TCalculator calc;

	calc.SetExpr(")9 + 9");

	if (calc.CheckExpression())
	{
		calc.ToPostfix();
		cout << calc.GetPostfix() << '\n';

		cout << calc.Calc() << '\n';
	}

}