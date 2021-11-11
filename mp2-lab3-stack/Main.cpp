#include <iostream>
#include <string>
#include "TCalculator.h"
#include "TStack.h"

using namespace std;

int main()
{
	TCalculator calc;

	calc.SetExpr("2 + 3");
	
	if (calc.CheckExpression())
	{
		calc.ToPostfix();
		cout << calc.GetPostfix() << '\n';
		cout << calc.CalcPostfix() << '\n';

		double res = calc.Calc();

		cout << res << '\n';
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