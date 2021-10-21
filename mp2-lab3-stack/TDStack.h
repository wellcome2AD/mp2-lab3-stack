#pragma once

template <class T>

class TDStack
{
	T* Mas;
	int Size, NumLast1, NumLast2;
public:

	TDStack(int size) : Size(size) 
	{
		Mas = new T[Size];
		NumLast1 = -1;
		NumLast2 = Size;
	}

	bool St1_IsEmpty() const { return (NumLast1 == -1); }
	
	bool St2_IsEmpty() const { return (NumLast2 == Size); }

	bool IsFull() const { return ((NumLast2 - NumLast1) == 1); }

	void Clear() 
	{ 
		NumLast1 = -1; 
		NumLast2 = Size; 
	}

	void St1_Push(const T& element)
	{
		if (IsFull())
			throw 0;
		Mas[++NumLast1] = element;
	}

	void St2_Push(const T& element)
	{
		if (IsFull())
			throw 0;
		Mas[--NumLast2] = element;
	}

	T St1_Pop()
	{
		if (St1_IsEmpty())
			throw 0;
		return Mas[NumLast1--];
	}

	T St2_Pop()
	{
		if (St2_IsEmpty())
			throw 0;
		return Mas[NumLast2++];
	}
};
