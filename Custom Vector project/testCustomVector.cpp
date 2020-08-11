
#include <random>
#include <iostream>
#include "customVector.h"

using namespace MyCustromVector;

struct student
{
public:
	int id;
	const char* name;
	student(int i = rand(), const char* s = "notset")
		: id(i), name(s)
	{
		std::cout << "construct: " << name << std::endl;
	}
	

	bool operator<(const student &rh) const
	{
		return this->id < rh.id;
	
	}

	bool operator>(const student& rh) const
	{
		return this->id >rh.id;

	}

	bool operator>=(const student& rh) const
	{
		return this->id >= rh.id;

	}

	bool operator<=(const student& rh) const
	{
		return this->id <= rh.id;

	}
	bool operator==(const student& rh) const
	{
		return (this->id == rh.id && strcmp(this->name,rh.name)==0);

	}


};

std::ostream& operator<<(std::ostream& os, student const& s)
{
	os << "Student id: " << s.id << ", Student name: " << s.name << std::endl;
	return os;
}



//template<typename T, unsigned Size>
//void InsertionSort(Vector<T, Size>& arr, int number)
//{
//	for (int k = 1; k < number; ++k)
//	{
//		T temp = arr[k];
//		int i = k;
//
//		while (i > 0 && arr[i - 1] >= temp)
//		{
//			arr[i] = arr[i - 1];
//			--i;
//		}
//		arr[i] = temp;
//	}
//}

void testingStudentArray()
{
	Vector<student, 10> sArray;

	for (int i = 0; i < 14; i++)
		sArray.push({ rand(), "NotSetYet......." });

	std::cout << sArray;
	sArray[0].name = "Reza";
	std::cout << sArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after expansion!\n";
	std::cout << sArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	sArray.ascendingsort();
	std::cout << "Print after ascending sort!\n";
	std::cout << sArray;
	sArray.push({800, "Doom" });
	sArray.push({ rand(), "John" });
	sArray.push({ rand(), "Mery" });
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after auto adding John and Mery!\n";
	std::cout << sArray;

	

	sArray.erase(2);
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after erasing at index 2!\n";
	std::cout << sArray;

	sArray.insert(3, { 900, "Mark" });
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after insert at index 3!\n";
	std::cout << sArray;

	sArray.pop();
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after auto pop!\n";
	std::cout << sArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	sArray.Find({ 100,"Mark" });
	std::cout << "----------------------------------------------------------------" << std::endl;
	sArray.ascendingsort();
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after ascending sort!\n";
	std::cout << sArray;



	sArray.descendingsort();
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Print after descending sort!\n";
	std::cout << sArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	sArray.Find({800,"Doom"});
	std::cout << "----------------------------------------------------------------" << std::endl;
}
int main()
{
	Vector<int, 20> intArray(-1);
	Vector<int, 20> intArray2(-1);
	for (int i = 0; i < 10; ++i)
	{
		intArray.push(rand());
		intArray2.push(i);
	}

	std::cout << intArray;
	std::cout << intArray2;
	//InsertionSort(intArray,10);
	//std::cout << intArray;


	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray[4] = 25;
	std::cout << "Make intArray[4] = 25" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.ascendingsort();
	std::cout << "Print after ascending sort" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.insert(6, 4);
	std::cout << "Print after insert 4 at position 5" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.push(3);
	std::cout << "Print after push 3" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.push_front(100);
	std::cout << "Print after push_front 100" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.erase(5);
	std::cout << "Print after erase position 5" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.descendingsort();
	std::cout << "Print after descending sort" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray = intArray2;
	std::cout << "Print after assign" << std::endl;
	std::cout << intArray2;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.insert(5, 8);
	std::cout << "Print after insert 8 at position 5" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.pop();
	std::cout << "Print after auto pop" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.pop_front();
	std::cout << "Print after auto pop_front" << std::endl;
	std::cout << intArray;
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.Find(5);
	std::cout << "----------------------------------------------------------------" << std::endl;
	intArray.Find(10);
	std::cout << "----------------------------------------------------------------" << std::endl;
	testingStudentArray();



	system("pause");
	return 0;
}