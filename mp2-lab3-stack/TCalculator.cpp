#include <iostream>
#include <string>
#include "TCalculator.h"
#include "TException.h"

using namespace std;

bool TCalculator::CheckBracketsNum()
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
		catch (const std::exception&)
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

bool TCalculator::isFunction(const string& function)
{
	string functions[] = { "sin", "cos", "tg" };
	int size = 3;

	for (int i = 0; i < size; i++)
		if (function == functions[i])
			return true;

	return false;
}

int TCalculator::Priority(const string& op)
{
	if (op == "(" || isFunction(op))
		return 0;
	if (op == "+" || op == "-")
		return 1;
	if (op == "*" || op == "/")
		return 2;
	if (op == "^")
		return 3;
}

TCalculator::FunctionType TCalculator::GetFunction(const string& f)
{
	if (f == "sin")
		return sin;
	if (f == "cos")
		return cos;
	if (f == "tg")
		return tan;
}

void TCalculator::ToPostfix()
{
	string infix = '(' + expr + ')';
	postfix = "";

	st_string.Clear();

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
			continue;

		if (infix[i] <= '9' && infix[i] >= '0')
		{
			size_t ind;
			double num = stod(&infix[i], &ind);
			postfix += std::to_string(num);
			postfix += ' ';
			i += ind - 1;
			continue;
		}

		if (infix[i] == '(')
		{
			st_string.Push("(");
			continue;
		}

		if (infix[i] == ')')
		{
			while (st_string.Top() != "(")
				postfix += st_string.Pop() + " ";

			st_string.Pop();

			if (!st_string.IsEmpty() && isFunction(st_string.Top()))
				postfix += st_string.Pop() + " ";

			continue;
		}

		if (isOperator(infix[i]))
		{
			while (Priority(st_string.Top()) > Priority(string(1, infix[i])))
			{
				postfix += st_string.Pop();
				postfix += " ";
			}

			st_string.Push(string(1, infix[i]));
			continue;
		}

		string function = "";
		while (infix[i] != '(')
		{
			function += infix[i];
			i++;
		}

		while (!function.empty() && isspace(function[function.size() - 1]))
		{
			function.erase(function.size() - 1);
		}

		if (isFunction(function))
		{
			st_string.Push(function);
			st_string.Push("(");
			continue;
		}
		else
			throw TException("Unknown function");
	}
}

double TCalculator::CalcPostfix()
{
	double a, b;
	
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] <= '9' && postfix[i] >= '0')
		{
			size_t ind;
			double num = stod(&postfix[i], &ind);
			st_double.Push(num);
			i += ind - 1;
			continue;
		}

		if (isOperator(postfix[i]))
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

		if (postfix[i] != ' ')
		{
			string function;
			a = st_double.Pop();
			
			while (postfix[i] != ' ')
				function += postfix[i++];
			
			if (isFunction(function))
			{
				double res = GetFunction(function)(a);
				st_double.Push(res);
			}
		}
	}
	
	postfix = "";
	return st_double.Pop();
}
//
//double TCalculator::Calc()
//{
//	string infix = "(" + expr + ")";
//
//	st_double.Clear();
//	st_char.Clear();
//
//	for (int i = 0; i < infix.length(); i++)
//	{
//		if (infix[i] >= '0' && infix[i] <= '9')
//		{
//			size_t ind;
//			double num = stod(&infix[i], &ind);
//			st_double.Push(num);
//			i += ind - 1;
//			continue;
//		}
//
//		if (infix[i] == '(')
//		{
//			st_char.Push('(');
//			continue;
//		}
//
//		if (infix[i] == ')')
//		{
//			while (st_char.Top() != '(')
//			{
//				double b = st_double.Pop();
//				double a = st_double.Pop();
//
//				switch (st_char.Pop())
//				{
//				case '+':
//					st_double.Push(a + b);
//					break;
//				case '-':
//					st_double.Push(a - b);
//					break;
//				case '*':
//					st_double.Push(a * b);
//					break;
//				case '/':
//					st_double.Push(a / b);
//					break;
//				}
//			}
//			st_char.Pop();
//			continue;
//		}
//
//		if (isOperator(infix[i]))
//		{
//			while (Priority(st_char.Top()) > Priority(infix[i]))
//			{
//				double b = st_double.Pop();
//				double a = st_double.Pop();
//
//				switch (st_char.Pop())
//				{
//				case '+':
//					st_double.Push(a + b);
//					break;
//				case '-':
//					st_double.Push(a - b);
//					break;
//				case '*':
//					st_double.Push(a * b);
//					break;
//				case '/':
//					st_double.Push(a / b);
//					break;
//				}
//			}
//			
//			st_char.Push(infix[i]);
//		}
//	}
//	
//	double top = st_double.Pop();
//
//	if (st_double.IsEmpty())
//		return top;
//	else 
//		throw TException("The expression is incorrect");
//}

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
