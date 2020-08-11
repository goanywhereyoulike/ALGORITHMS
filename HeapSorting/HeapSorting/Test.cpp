#include <iostream>
#include<random>
void MakeMaxHeap(int ary[], int n, int i)
{
	//i is the last father root
	int max = i;
	int Maxnumber = i * 2 + 1;
	//left child

	if (ary[Maxnumber + 1] > ary[Maxnumber] && Maxnumber + 1 < n)
		{
			Maxnumber++;
		}
	// compare child which is larger(left or right)
	if (Maxnumber<n &&ary[Maxnumber]>ary[max])
	{
		max = Maxnumber;

	}
	if (max != i)
	{
		
		std::swap(ary[i], ary[max]);//put the max number to last father root
		MakeMaxHeap(ary, n, max);//Make sure the child still are max head after swap

	}

}

void HeapSort(int ary[], int n)
{
	for (int i = n / 2 - 1; i >=0; i--)
	{
		MakeMaxHeap(ary, n, i);

	}
	//Make the Max Heap structure
	for (int i = n - 1; i >=0; i--)
	{
		std::swap(ary[0], ary[i]);
		MakeMaxHeap(ary, i, 0);
	}

	//switch ary[0] with the last item and then remake the max heap, leaving the last alone(the max number)

}

void display(int ary[], int n)
{
	std::cout << "Array[" << n << "]: ";
	for (int i = 0; i < n; ++i)
	{
		std::cout << ary[i] << " ";

	}

	std::cout << std::endl;
	std::cout << std::endl;
}

int main()
{
	int ary1[10];
	for (int i = 0; i < 10; i++)
	{
		ary1[i] = rand() % 10;
	}
	int ary2[100];
	for (int i = 0; i < 100; i++)
	{
		ary2[i] = rand() % 100;
	}
	int ary3[200];
	for (int i = 0; i < 200; i++)
	{
		ary3[i] = rand() % 200;
	}
	std::cout << "INPUT ARRAY" << std:: endl;
	display(ary1, 10);
	display(ary2, 100);
	display(ary3, 200);
	HeapSort(ary1, 10);
	HeapSort(ary2, 100);
	HeapSort(ary3, 200);
	std::cout << "----------------------------------" << std::endl;
	std::cout << "OUTPUT ARRAY AFTER HEAD SORTING" << std::endl;
	display(ary1, 10);
	display(ary2, 100);
	display(ary3, 200);
	system("pause");
	return 0;
}