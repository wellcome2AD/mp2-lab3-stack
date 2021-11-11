
#include <iostream>
#include <string>
#include "TCalculator.h"

using namespace std;

bool TCalculator::CheckExpression()
{

	int size = expr.size();
	TStack<char> st1(size);

	for (int i = 0; i < size; i++)
	{
		if (expr[i] == '(')
			st1.Push('(');
		try
		{
			if (expr[i] == ')')
				st1.Pop();
		}
		catch (...)
		{
			cout << "')' more than '(' " << '\n';
			return 0;
		}
	}

	if (!st1.IsEmpty())
	{
		cout << "'(' more than ')' " << '\n';
		return 0;
	}
	cout << "The expression is correct" << '\n';
	return 1;
}

bool TCalculator::isOperator(char symbol)
{
	char operators[] = { '+', '-', '*', '/', '^' };
	int size = 5;

	for (int i = 0; i < size; i++)
		if (symbol == operators[i])
			return true;

	return false;	
}

int TCalculator::Priority(char op)
{
	switch (op)
	{
	case '(':
		return 0;
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '^':
		return 3;
	}
}

void TCalculator::ToPostfix()
{
	string infix = '(' + expr + ')';
	postfix = "";

	st_char.Clear();

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
			continue;

		if (infix[i] <= '9' && infix[i] >= '0')
		{
			postfix += infix[i];
			postfix += ' ';
			continue;
		}

		if (infix[i] == '(')
		{
			st_char.Push('(');
			continue;
		}			

		if (infix[i] == ')')
		{
			while (st_char.Top() != '(')
			{
				try
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				catch (string ex)
				{
					cout << ex;
				}
			}

			try
			{
				st_char.Pop();
			}
			catch (string ex)
			{
				cout << ex;
			}
			continue;
		}

		if (isOperator(infix[i]))
		{
			while (Priority(st_char.Top()) > Priority(infix[i]))
			{
				try
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				catch (string ex)
				{
					cout << ex;
				}
			}

			try
			{
				st_char.Push(infix[i]);
			}
			catch (string ex)
			{
				cout << ex;
			}
		}
	}
}

double TCalculator::CalcPostfix()
{
	double a, b;
	
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] <= '9' && postfix[i] >= '0')
		{
			st_double.Push(stod(&postfix[i]));
			continue;
		}

		if (postfix[i] != ' ')
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

double TCalculator::Calc()
{
	string infix = "(" + expr + ")";

	st_double.Clear();
	st_char.Clear();

	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] += '0' && infix[i] <= '9')
		{
			size_t ind;
			double num = stod(&infix[i], &ind);
			st_double.Push(num);
			i += ind - 1;
		}

		if (infix[i] == '(')
		{
			st_char.Push('(');
			continue;
		}

		if (infix[i] == ')')
		{
			while (st_char.Top() != '(')
			{
				double b = st_double.Pop();
				double a = st_double.Pop();

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

			st_char.Pop();
		}

		if (isOperator(infix[i]))
		{
			while (Priority(st_char.Top()) > Priority(infix[i]))
			{
				double b = st_double.Pop();
				double a = st_double.Pop();

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
			
			st_char.Push(infix[i]);
		}
	}

	double top = st_double.Top();
	if (st_double.IsEmpty())
		return top;
	//else throw ...
}

//приоритет: ( = 0, + = - = 1, *, ^
	//1. брать очередную операцию (а), сравнивать её по приоритету
	//с той, которая сейчас на вершине стека (b):
	//	1.1 если (a <= b) - вытолкнуть b в строку
	//	1.2 если a>b - записать a в стек
	//	1.3 '(' просто записывается в стек, без проверки
	//	1.4 ) выталкивает все операции из стека до (
	//  (в связи с этим все выражения будут заключаться в () )
	//2. число просто переписывается в строку
	//+ ( + * ( - ) ) * ^ -
	//2 + (1+2*(4 - 2))*4^2 - 5
	//2 1 2 4 2 - * + 4 2 ^ +
	//
