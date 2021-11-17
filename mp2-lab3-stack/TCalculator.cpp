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
	double a;
	
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
			PushBinOperationResult(string(1, postfix[i]));
			continue;
		}

		if (postfix[i] != ' ')
		{
			string function;
			
			while (postfix[i] != ' ')
				function += postfix[i++];
			
			if (isFunction(function))
			{
				PushUnOperationResult(function);
			}
		}
	}
	
	postfix = "";
	return st_double.Pop();
}

double TCalculator::Calc()
{
	double a;
	string infix = "(" + expr + ")";

	st_double.Clear();
	st_string.Clear();

	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] >= '0' && infix[i] <= '9')
		{
			size_t ind;
			double num = stod(&infix[i], &ind);
			st_double.Push(num);
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
			{
				string op = st_string.Pop();
				PushBinOperationResult(op);
			}

			st_string.Pop();

			if (!st_string.IsEmpty() && isFunction(st_string.Top()))
				PushUnOperationResult(st_string.Pop());

			continue;
		}

		if (isOperator(infix[i]))
		{
			while (Priority(st_string.Top()) > Priority(string(1, infix[i])))
			{
				string op = st_string.Pop();
				PushBinOperationResult(op);
			}
			
			st_string.Push(string(1, infix[i]));
			continue;
		}

		if (infix[i] != ' ')
		{
			string function;

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
	
	double top = st_double.Pop();

	if (st_double.IsEmpty())
		return top;
	else 
		throw TException("The expression is incorrect");
}
