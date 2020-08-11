#include <iostream>
#include "Header.h"
#include <fstream>
#include <map>
#include <graphics.h>

using namespace VGP244;

void picture(std::map<int, int> Map )
{
	initgraph(1000, 400);

	//x
	setlinecolor(LIGHTRED);
	line(30, 330, 800, 330);
	//x arrow
	line(800, 330, 780, 320);
	line(800, 330, 780, 340);
	outtextxy(800, 640, "x");
	//y
	setlinecolor(LIGHTBLUE);
	line(30, 40, 30, 330);
	//yarrow
	line(30, 40, 20, 60);
	line(30, 40, 40, 60);
	outtextxy(20, 20, "y");
	//折线图
	setlinecolor(LIGHTGREEN);
	for (int i=0;i<99001;i++)
{
	//std::cout << it->first << " : " << it->second<< "\n";


		line( 30+i, 300 - 10*Map[i],  30+i + 1, 300 - 10*(Map[i+1]));//画布坐标的正方向恰好与广义坐标系的正方向相反
}
	setlinecolor(LIGHTCYAN);
	system("pause");
	closegraph();
}


int main()
{
	std::map<int, int> heightMap;
	std::ifstream readFile("data_search.txt");
	std::ifstream readFile2("search_list.txt");

	
	int num = 0;
	int num2 = 0;
	std::cout << "AVL tree construction app:\n\n";
	//std::cout << "Enter int value as data. To stop, enter -1\n\n";
	AVL<int> avl;
	int val = 0;
	for (int i = 1; i < 15; i++)
	{
		avl.insert(i);
	}
	std::cout << std::endl;
	std::cout << "The Tree height is: " << avl.TreeHeight() << std::endl;
	std::cout << std::endl;
	//avl.Postorderprint();
	//std::cout << std::endl;
	avl.printTree();

	//system("pause");

	//while (val != -1)
	//{
	//	std::cin >> val;
	//	avl.insert(val);
	//	std::cout << std::endl;
	//	avl.printTree();
	//}
	std::cout << "Remove node 8" << std::endl;
	avl.remove(8);
	avl.printTree();
	//avl.Printfixleveltree(2);

	std::cout << "Try to find node 8" << std::endl;
	avl.find(8);
	std::cout << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "      Text File Test" << std::endl;
	AVL<int> av2;
	while (!readFile.eof())
	{
		readFile >> num;
		//std::cout << num << ",";
		av2.insert(num);
	}
	readFile.close();
	//av2.printTree();
	std::cout << "The Tree height is: "<<av2.TreeHeight() << std::endl;
	std::cout << std::endl;

	AVL<int> av3;
 ;
	av3.Setroot(av2.levelcopy(av2.Getroot()));
	std::cout << "Print the first 4 levels of the tree nodes" << std::endl;
	av3.printTree();

	std::cout <<  std::endl;
	std::cout << "Search and Remove nodes" << std::endl;
	//search and delete node;
	while (!readFile2.eof())
	{
		readFile2 >> num2;
		//std::cout << num << ",";
		
		if (av2.find(num2)!=nullptr)
		{
			av2.remove(num2);
		}

	}
	readFile2.close();

	std::cout << "The Tree height is: " << av2.TreeHeight() << std::endl;
	std::cout << std::endl;

	
	av2.Inorderprint();
	int count = 0;
	int num3 = 0;
	std::ifstream readFile3("data.txt");
	AVL<int> av4;
	while (!readFile3.eof())
	{
		readFile3 >> num3;
		//std::cout << num << ",";
		av4.insert(num3);
		count++;
		heightMap.insert(std::make_pair(count, av4.TreeHeight()));
	}
	readFile3.close();
	picture(heightMap);
	//for (auto it = heightMap.cbegin(); it != heightMap.cend(); ++it)
	//{
	//	std::cout << it->first << " : " << it->second<< "\n";
	//}

	system("pause");
}