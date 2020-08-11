#pragma once

#include<String>
struct Person
{
	char name[16];
	int age;
	Person(const char cName[16], int a) :age(a)
	{
		strncpy_s(name, cName, 16);
	}
	Person()
	{
		name[0] = '\0';
		age = 0;
	}

};