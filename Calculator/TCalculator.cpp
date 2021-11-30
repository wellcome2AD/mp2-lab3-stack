#include <iostream>
#include <string>
#include "..\mp2-lab3-stack\TCalculator.h"
#include "..\mp2-lab3-stack\TException.h"

using namespace std;

bool TCalculator::CheckBracketsNum()
{

	int size = expr.size();
	TStack<char> st1(size);

	for (int i = 0; i < size; i++)
	{
		if (expr.at(i) == '(')
			st1.Push('(');
		try
		{
			if (expr.at(i) == ')')
				st1.Pop();
		}
		catch (const TException&)
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
	cout << "Bracket sequence is correct" << '\n';
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

void TCalculator::PushUnOperationResult(const string& op)
{
	double a = st_double.Pop();

	if (op == "sin")
	{
		st_double.Push(sin(a));
	}
	else if (op == "cos")
	{
		st_double.Push(cos(a));
	}
	else if (op == "tg")
	{
		st_double.Push(tan(a));
	}
}

void TCalculator::PushBinOperationResult(const string& op)
{
	double b = st_double.Pop();
	double a = st_double.Pop();

	if (op == "+")
	{
		st_double.Push(a + b);
	}
	else if (op == "-")
	{
		st_double.Push(a - b);
	}
	else if (op == "*")
	{
		st_double.Push(a * b);
	}
	else if (op == "/")
	{
		st_double.Push(a / b);
	}
	else if (op == "^")
	{
		st_double.Push(pow(a, b));
	}
}

void TCalculator::ToPostfix()
{
	string infix = '(' + expr + ')';
	postfix = "";

	st_string.Clear();

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix.at(i) == ' ')
			continue;

		if (infix.at(i) <= '9' && infix.at(i) >= '0')
		{
			size_t ind;
			double num = stod(&infix.at(i), &ind);
			postfix += std::to_string(num);
			postfix += ' ';
			i += ind - 1;
			continue;
		}

		if (infix.at(i) == '(')
		{
			st_string.Push("(");
			continue;
		}

		if (infix.at(i) == ')')
		{
			while (st_string.Top() != "(")
				postfix += st_string.Pop() + " ";

			st_string.Pop();

			if (!st_string.IsEmpty() && isFunction(st_string.Top()))
				postfix += st_string.Pop() + " ";

			continue;
		}

		if (isOperator(infix.at(i)))
		{
			while (Priority(st_string.Top()) >= Priority(string(1, infix.at(i))))
			{
				postfix += st_string.Pop();
				postfix += " ";
			}

			st_string.Push(string(1, infix.at(i)));
			continue;
		}

		string function = "";
		while (infix.at(i) != '(')
		{
			function += infix.at(i);
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
	
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix.at(i) <= '9' && postfix.at(i) >= '0')
		{
			size_t ind;
			double num = stod(&postfix.at(i), &ind);
			st_double.Push(num);
			i += ind - 1;
			continue;
		}

		if (isOperator(postfix.at(i)))
		{
			PushBinOperationResult(string(1, postfix.at(i)));
			continue;
		}

		if (postfix.at(i) != ' ')
		{
			string function;
			
			while (postfix.at(i) != ' ')
				function += postfix[i++];
			
			if (isFunction(function))
			{
				PushUnOperationResult(function);
			}
		}
	}
	
	postfix = "";

	double top = st_double.Pop();

	if (st_double.IsEmpty())
		return top;
	else
		throw TException("The expression is incorrect");
}

double TCalculator::Calc()
{
	string infix = "(" + expr + ")";

	st_double.Clear();
	st_string.Clear();

	for (int i = 0; i < infix.length(); i++)
	{
		if (infix.at(i) >= '0' && infix.at(i) <= '9')
		{
			size_t ind;
			double num = stod(&infix.at(i), &ind);
			st_double.Push(num);
			i += ind - 1;
			continue;
		}

		if (infix.at(i) == '(')
		{
			st_string.Push("(");
			continue;
		}

		if (infix.at(i) == ')')
		{
			while (st_string.Top() != "(")
			{
				string op = st_string.Pop();
				PushBinOperationResult(op);
			}

			st_string.Pop();

			if (!st_string.IsEmpty() && isFunction(st_string.Top()))
				PushUnOperationResult(st_string.Pop());

			continue;
		}

		if (isOperator(infix.at(i)))
		{
			while (Priority(st_string.Top()) >= Priority(string(1, infix.at(i))))
			{
				string op = st_string.Pop();
				PushBinOperationResult(op);
			}
			
			st_string.Push(string(1, infix.at(i)));
			continue;
		}

		if (infix.at(i) != ' ')
		{
			string function;

			while (infix.at(i) != '(')
			{
				function += infix.at(i);
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
	
	double top = st_double.Pop();

	if (st_double.IsEmpty())
		return top;
	else 
		throw TException("The expression is incorrect");
}
