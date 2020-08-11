
#include <random>
#include <time.h>
#include "DoublyQueue.h"

int main()
{
	srand(time(0));
	std::cout << "The size of the deque is 20\n";
	std::cout << "Attempt to push front 18 items to deque:\n";
	DoublyQueue<int> queue(20);
	for (int i = 0; i < 18; ++i)
		queue.push_front(rand()%30);
	queue.DisplayQueue();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Attempt to push front 5 to deque:\n";
	queue.push_front(5);
	queue.DisplayQueue();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Attempt to push back 5 to deque:\n";
	queue.push_back(5);
	queue.DisplayQueue();
	std::cout << std::endl;
	std::cout << "---------------------Pop start----------------\n";
	for (int i = 0; i < 10; ++i)
	{
		queue.pop_front();
		std::cout << "---------------------Pop front----------------\n";
		queue.DisplayQueue();
		std::cout << std::endl;
		queue.pop_back();
		std::cout << "---------------------Pop back-----------------\n";
		queue.DisplayQueue();
		std::cout << std::endl;
	}
	std::cout << "---------------------Pop front----------------\n";
	queue.pop_front();
	system("pause");
	return 0;
}