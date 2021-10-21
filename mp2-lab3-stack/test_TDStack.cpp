#include <iostream>
#include "TDStack.h"
#include <string>

#define cout std::cout
#define string std::string

void main()
{
	TDStack<int> mas(10);
	
	setlocale(LC_ALL, "");

	try
	{
		for (int i = 0; i < 5; i++)
			mas.St1_Push(i);
	}
	catch (...)
	{
		cout << '\n' << "Стек полон" << '\n';
		return;
	}

	try
	{
		for (int i = 0; i < 5; i++)
			mas.St2_Push(2*i);
	}
	catch (...)
	{
		cout << '\n' << "Стек полон" << '\n';
		return;
	}
	

	if (mas.IsFull())
		cout << '\n' << "Массив полный" << '\n';
	else
		cout << '\n' << "Массив не полный" << '\n';


	try
	{
		cout << '\n' << "Стек №1" << '\n';
		for (int i = 0; i < 5; i++)
			cout << mas.St1_Pop() << ' ';
		cout << '\n';
	}
	catch (...)
	{
		cout << '\n' << "Стек №1 пуст" << '\n';
		return;
	}

	try
	{
		cout << '\n' << "Стек №2" << '\n';
		for (int i = 0; i < 5; i++)
			cout << mas.St2_Pop() << ' ';
		cout << '\n';
	}
	catch (...)
	{
		cout << '\n' << "Стек №2 пуст" << '\n';
		return;
	}

	if (mas.St1_IsEmpty())
		cout << '\n' << "Стек №1 пуст" << '\n';

	if (mas.St2_IsEmpty())
		cout << '\n' << "Стек №2 пуст" << '\n';
}