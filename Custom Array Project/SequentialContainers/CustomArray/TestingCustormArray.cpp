
#include <random>
#include "Person.h"
#include "CustomArray.h"


using namespace VGP220;



int main()
{
	CustomArray<int> arr(20);
	std::cout << "Push 10 items" << std::endl;
	for (int i = 0; i < 10; ++i)
		arr.push(rand());

	arr.print(); // add this method to CustomArray
	//arr[0] = 9;
	//while (arr.Size() > 0)
	arr.pop();
	arr.print();
	std::cout << "Inset 4 at arr[4]" << std::endl;
	arr.insert(4, 4);
	arr.print();

	std::cout << "Remove  arr[3]" << std::endl;
	arr.remove(3);
	arr.print();


	int result{ 0 };
	int input{ 24464 };
	std::cout << "Search  value " << input << std::endl;
	result = arr.search(input);
	if (result == -1)
	{
		std::cout << input << "is not in the array" << std::endl;
	}
	else
	{
		std::cout << "The index of value " << input << " is: " << result << std::endl;
	}


	CustomArray<Person> student(20);
	Person AllStudent[12] = { {"Tom",3},{"Bob",4},{"Jason",5},{"Helen",7},{"Mike",8},{"Sara",9},{"Chris",10},{"Cary",11},{"Evan",12},{"Alex",13},{"Adam",14},{"Cody",15} };
	std::cout << "Push 12 students" << std::endl;
	for (int i = 0; i < 12; ++i)
		student.push(AllStudent[i]);
	student.print();
	std::cout << std::endl << "Inset Ford,4 at student[0]" << std::endl;
	Person Ford{ "Ford",4 };
	student.insert(0, Ford);
	student.print();

	std::cout << std::endl << "Remove  student[3]" << std::endl;
	student.remove(3);
	student.print();

	student.pop();

	int result2{ 0 };
	Person mStudent{ "Cary",11 };
	std::cout << std::endl << "Search  student: " << mStudent.name << " ,age: " << mStudent.age << std::endl;
	result2 = student.search(mStudent);
	if (result2 == -1)
	{
		std::cout << mStudent.name << " is not in the student array" << std::endl;
	}
	else
	{
		std::cout << "The index of the student " << mStudent.name << "(age " << mStudent.age << ")" << " is: " << result2 << std::endl;
	}

	system("pause");
	return 0;
}
