#pragma once

#include <iostream>
#include <assert.h>

template<typename T>
class DoublyQueue
{
public:
	DoublyQueue(int size = 10);
	~DoublyQueue() { delete[] values; }
	bool IsEmpty() const;
	bool IsFull() const;
	bool push_back(T x);
	bool push_front(T x);
	bool pop_back();
	bool pop_front();
	void DisplayQueue() const;
private:
	int front = -1;     // index to front of the queue
	int back = -1;      // index to rear of the queue
	int count = 0;      // number of elements in the queue
	int maxSize = 0;
	T* values = nullptr;
};

template <typename T>
DoublyQueue<T>::DoublyQueue(int size)
{
	values = new T[size];
	if (values)
	{
		maxSize = size;
		front = 0;
		back = -1;
		count = 0;
	}
}

template <typename T>
bool DoublyQueue<T>::IsEmpty() const
{
	if (count<=0)
	{
		return true;
	}

	return false;
}

template <typename T>
bool DoublyQueue<T>::IsFull() const
{
	if ((back + 1) % maxSize == front &&count>=maxSize)
	{
		return true;
	}

	return false;
}

template<typename T>
bool DoublyQueue<T>::push_back(T x)
{
	if (!IsFull())
	{
		back = (back + 1) % maxSize;
		values[back] = x;
		++count;
		return true;
	}
	std::cout << "Error: queue is full\n";
	return false;
}

template<typename T>
bool DoublyQueue<T>::push_front(T x)
{
	if (!IsFull())
	{
		
		front = (front + maxSize - 1) % maxSize;
		values[front] = x;
		++count;
		return true;
	}
	std::cout << "Error: queue is full\n";
	return false;
}

template<typename T>
bool DoublyQueue<T>::pop_front()
{
	if (!IsEmpty())
	{
		front = (front + 1) % maxSize;
		--count;
		return true;
	}
	std::cout << "Error: queue is empty\n";
	return false;
}

template<typename T>
bool DoublyQueue<T>::pop_back()
{
	if (!IsEmpty())
	{
		back = (back + maxSize - 1) % maxSize;
		--count;
		return true;
	}
	std::cout << "Error: queue is empty\n";
	return false;
}

template<typename T>
void DoublyQueue<T>::DisplayQueue() const
{
	std::cout << "Front -->";
	for (int i = 0; i < count; ++i)
	{
		if (i == 0)
			std::cout << "\t";
		else
			std::cout << "\t\t";
		std::cout << values[(front + i) % maxSize];
		if (i != count - 1)
			std::cout << std::endl;
		else
			std::cout << "\t<--back\n";
	}
}
