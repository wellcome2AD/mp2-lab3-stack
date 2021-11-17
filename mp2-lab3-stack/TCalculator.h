#pragma once

#include <iostream>
#include  <string>
#include "TStack.h"

using namespace std;

class TCalculator
{
	string expr;
	string postfix;
	TStack<string> st_string;
	TStack<double> st_double;

public:
	TCalculator(string _expr = "") : expr(_expr) {}

	void SetExpr(string _expr) { expr = _expr; }
	
	string GetPostfix() { return postfix; }

	bool CheckBracketsNum(); //проверка корректности
	
	void ToPostfix();
	
	double CalcPostfix();

	double Calc();

private:
	
	bool isOperator(char symbol);

	bool isFunction(const string& function);

	int Priority(const string& op); //приоритет операций	

	using FunctionType = double(*)(double);

	FunctionType GetFunction(const string&);
};
