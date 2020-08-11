#include<iostream>
#include<array>
#include <iostream>
#include <chrono>
#include<random>
#include"time.h"

template<typename T, int num>
void BubbleSort(std::array<T, num>& arr)
{
	for (int k = num - 1; k > 0; --k)
	{
		for (int i = 0; i < k; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				T temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

template<typename T, int num>
void SelectionSort(std::array<T, num>& arr)
{
	for (int k = 0; k < num - 1; ++k)
	{
		int minIndex = k;
		for (int i = k + 1; i < num; ++i)
		{
			if (arr[i] < arr[minIndex])
				minIndex = i;
		}

		// swap min with k if necessary
		if (k != minIndex)
		{
			T temp = arr[minIndex];
			arr[minIndex] = arr[k];
			arr[k] = temp;
		}
	}
}

template<typename T, int num>
void InsertionSort(std::array<T, num>& arr)
{
	for (int k = 1; k < num; ++k)
	{
		T temp = arr[k];
		int i = k;

		while (i > 0 && arr[i - 1] >= temp)
		{
			arr[i] = arr[i - 1];
			--i;
		}
		arr[i] = temp;
	}
}
using namespace std;
int main()
{
	std::cout << "---------The test number is 1000--------" << std::endl;
	std::array<int, 1000> intArray1;
	for(int i = 0; i < 1000; ++i)
			intArray1[i] = rand();
	std::cout << "The first 10 integers before sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray1[i] << ", ";
	std::array<int, 1000> intArray2 = intArray1;
	std::array<int, 1000> intArray3 = intArray1;
	std::cout << std::endl;
	auto start{ chrono::steady_clock::now() };
	InsertionSort<int, 1000>(intArray1);
	auto end = chrono::steady_clock::now();
	std::cout << "Insertsort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	SelectionSort<int, 1000>(intArray2);
	end = chrono::steady_clock::now();
	std::cout << "SelectionSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	BubbleSort<int, 1000>(intArray3);
	end = chrono::steady_clock::now();
	std::cout << "BubbleSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	std::cout << "The first 10 integers after sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray1[i] << ", ";

	std::cout << std::endl;
	std::cout << "----------------Test End----------------" << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "---------The test number is 10000--------" << std::endl;
	std::array<int, 10000> intArray4;
	for (int i = 0; i < 10000; ++i)
		intArray4[i] = rand();
	std::cout << "The first 10 integers before sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray4[i] << ", ";
	std::array<int, 10000> intArray5 = intArray4;
	std::array<int, 10000> intArray6 = intArray4;
	std::cout << std::endl;
	start= chrono::steady_clock::now();
	InsertionSort<int, 10000>(intArray4);
	end = chrono::steady_clock::now();
	std::cout << "Insertsort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	SelectionSort<int, 10000>(intArray5);
	end = chrono::steady_clock::now();
	std::cout << "SelectionSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	BubbleSort<int, 10000>(intArray6);
	end = chrono::steady_clock::now();
	std::cout << "BubbleSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	std::cout << "The first 10 integers after sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray4[i] << ", ";

	std::cout << std::endl;
	std::cout << "----------------Test End----------------" << std::endl;

	std::cout << std::endl << std::endl;


	std::cout << "---------The test number is 100000--------" << std::endl;
	static std::array<int, 100000> intArray7;
	for (int i = 0; i < 100000; ++i)
		intArray7[i] = rand();

	std::cout << "The first 10 integers before sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray7[i] << ", ";
	static std::array<int, 100000> intArray8 = intArray7;
	static std::array<int, 100000> intArray9 = intArray7;
	std::cout<<std::endl;
	start = chrono::steady_clock::now();
	InsertionSort<int, 100000>(intArray7);
	end = chrono::steady_clock::now();
	std::cout << "Insertsort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	SelectionSort<int, 100000>(intArray8);
	end = chrono::steady_clock::now();
	std::cout << "SelectionSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = chrono::steady_clock::now();
	BubbleSort<int, 100000>(intArray9);
	end = chrono::steady_clock::now();
	std::cout << "BubbleSort::Elapsed time in ms:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	std::cout << "The first 10 integers after sorting are: ";
	for (int i = 0; i < 10; ++i)
		std::cout << intArray7[i] << ", ";

	std::cout << std::endl;
	std::cout << "----------------Test End----------------" << std::endl;

	system("pause");
	return 0;
}