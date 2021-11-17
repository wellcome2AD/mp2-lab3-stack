#include <iostream>
#include <string>
#include "TCalculator.h"
#include "TStack.h"
#include "TException.h"

using namespace std;

int main()
{
	double res;
	string expr;
	TCalculator calc;
	
	while (true)
	{
		std::getline(std::cin, expr);
		calc.SetExpr(expr);

		if (expr != "0" && calc.CheckBracketsNum())
		{
			try
			{
				calc.ToPostfix();
				cout << "Postfix: " << calc.GetPostfix() << '\n';
			}
			catch (const TException&)
			{
				cout << "Cannot convert to postfix" << '\n';
				return 0;
			}

			try
			{			
				res = calc.CalcPostfix();
				cout << "Result of calculation with postfix: " << res << '\n';
			}
			catch (const TException&)
			{
				cout << "Cannot calculate postfix expression" << '\n';
				return 0;
			}
			
			/*try
			{
				res = calc.Calc();
				cout << "Result of calculation without postfix: " << res << '\n';
			}
			catch (const TException&)
			{
				cout << "Cannot calculate" << '\n';
				return 0;
			}*/
		}
		else
			break;

		cout << '\n';
	}
	
	//(1 + sin(2))
	//sin(
	// + sin(2)
	// ( 1
	//


	/*string tmp = "2 + 3.4 * (2-1)";
	int i = 4;
	size_t ind;
	double d = stod(&tmp[i], &ind);

	cout << "str = " << tmp << endl;
	cout << "d = " << d << endl;
	cout << "ind = " << ind << endl;*/
}