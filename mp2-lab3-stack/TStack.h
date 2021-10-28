#pragma once

template <class T>

class TStack
{
	T* Stack;
	int Size, NumLast;

public:
	TStack(int _size = 10) : Size(_size) 
	{
		Stack = new T[Size];
		NumLast = -1;
	}

	~TStack() { delete[] Stack; }

	TStack(const TStack<T>& s) : Size(s.Size), NumLast(s.NumLast)
	{
		Stack = new T[Size];
		for (int i = 0; i < NumLast; i++)
			Stack[i] = s.Stack[i];
	}

	TStack& operator=(const TStack<T>& s)
	{
		if (Size != s.Size) {
			Size = s.Size;
			delete[] Stack;
			Stack = new T[Size];
		}

		NumLast = s.NumLast;

		for (int i = 0; i <= NumLast; i++)
			Stack[i] = s.Stack[i];
	}

	bool operator==(const TStack<T>& s)
	{
		if (Size != s.Size || NumLast != s.NumLast)
			return false;
		for (int i = 0; i < NumLast; i++)
			if (Stack[i] != s.Stack[i])
				return false;
		return true;
	}

	bool operator!=(const TStack<T>& s)
	{
		return !(this == s);
	}

	bool IsEmpty() const { return (NumLast == -1); }

	bool IsFull() const { return (NumLast == (Size - 1)); }

	void Clear() { NumLast = -1; }

	void Push(const T& element)
	{
		if (IsFull())
			throw "Stack is full";
		Stack[++NumLast] = element;
	}

	T Pop()
	{
		if (IsEmpty())
			throw "Stack is empty";
		return Stack[NumLast--];
	}

	T Top()
	{
		if (IsEmpty())
			throw "Stack is empty";
		return Stack[NumLast];
	}
};
