#include<iostream>
#include <string>
#include <fstream>
#include<sstream>
using namespace std;

#define MAX 11003
#define MAX2 1301
//#define MULT 3

typedef	struct WordCount {
		char word[64];
		unsigned short count; // # of times this word occurred in the book
		unsigned short page; // last page this word occurred 
		unsigned short key;
		struct WordCount *next;
	}WordCount;

	 WordCount *hashtable[MAX] = { nullptr };

	 WordCount *hashtable2[MAX2] = { nullptr };

	int HashIndex(const char *word)
	{
		int sum = 0;
		for (int i = 0; word[i] != '\0'; ++i)
		{
			sum = sum + word[i];
		}
		return sum % MAX;


	}

	int HashIndex2(const char *word)
	{
		int sum = 0;
		for (int i = 0; word[i] != '\0'; ++i)
		{
			sum = sum + word[i];
		}
		return sum % MAX2;


	}
	//chaining
	void cinsertword(const char *word,int pagenumber)
	{
		WordCount *p;
		
		int index = HashIndex(word);
		for (p = hashtable2[index]; p != nullptr; p = p->next)
		{
			if (strcmp(p->word, word) == 0)
			{
				(p->count)++;
				p->page = pagenumber;
				p->key = index;
				return;
			}
		}
		p = new WordCount [sizeof(WordCount)];
		p->count = 1;
		p->page = pagenumber;
		p->next = nullptr;
		strcpy_s(p->word, word);
		p->next = hashtable2[index];
		hashtable2[index] = p;
	}

	//Linear Probing
	void linsertword(const char *word, int pagenumber)
	{

		int index = HashIndex(word);
		while (hashtable[index] != nullptr )
		{
			if (strcmp(hashtable[index]->word, word) == 0)
			{
				(hashtable[index]->count)++;
				hashtable[index]->page = pagenumber;
				return;
			}
				index = (index + 1) % MAX;


		}
		hashtable[index] = new WordCount;
		hashtable[index]->count = 1;
		hashtable[index]->page = pagenumber;
		hashtable[index]->next = nullptr;
		hashtable[index]->key = index;
		strcpy_s(hashtable[index]->word, word);



	}




	void readtext(string filename,int number)
	{
		int page=0,i=0;
		ifstream textfile;
		string name{ "" };
		
		string line{ " " };
		textfile.open(filename.c_str());
		if (!textfile.is_open())
		{
			string path;
			cout << "Can not open the file" << endl;
			cout << "Enter the absolute path of the txt file" << endl;
			cout << "Example: C:\\Users\\a1521\\Desktop\\HashTable\\HashTable\\iliad.txt" << endl;
			cin >> path;
			textfile.open(path, ios::in);

		}
		

			

	
		while (getline(textfile, line))
		{
			i++;
			
			for (size_t i = 0; i < line.length(); i++)
			{
				if (ispunct(line[i]))
				{
					line[i] = ' ';
				}



			}
			stringstream ss(line);
			while (ss >> name)
			{
				const char* word = name.c_str();

				page = i / 44 + 1;

				if (number == 1)
				{
					linsertword(word, page);
				}
				else if (number == 2)
				{
					cinsertword(word, page);
				}
			}
		}

		textfile.close();
	
	}


	void lclean()
	{
		for (int i = 0; i < MAX; ++i)
		{
			delete hashtable[i];
		}
	
	}

	void cclean()
	{
		WordCount *n, *temp;
		for (int i = 0; i < MAX2; ++i)
		{
			n = hashtable2[i];
			while (n != nullptr)
			{
				temp = n->next;
				delete(n);
				n = temp;


			}
		}
	}

	void lsearch(const char *name)
	{
		WordCount *p;
		int count = 0;
		int index = HashIndex(name);
		if (hashtable[index]!=nullptr)
		{
			int n = 0;
			while (1)
			{
				n++;
				if (n> MAX)
				{
					cout << "The word does not find" << endl;
					return;
				}
				if (strcmp(hashtable[index]->word , name)!=0)
				{
					index = (index + 1) % MAX;
				}
				else
				{
					break;
				}

			}
			p = hashtable[index];
			cout << "Number of word(" << p->word << "): " << p->count << endl;
			cout << "Last page number: " << p->page << endl;
			//cout << "Hash table index: " << p->key << endl;
		}
		else
		{
			cout << "The word does not find" << endl;
		}
		return;
	
	
	
	}
	void csearch(const char *name)
	{
	
		WordCount *p;
		int count = 0;
		int index = HashIndex(name);
		for (p = hashtable2[index]; p != nullptr; p = p->next)
		{
			if (strcmp(p->word, name) == 0)
			{
				cout << "Number of word(" << p->word << "): " << p->count << endl;
				cout << "Last page number: " << p->page << endl;
				//cout << "Hash table index: " << p->key << endl;
				count++;
			}
		}
		if (count == 0)
		{
			cout << "Word does not find" << endl;
		}
		return;
	
	}

	int main()
	{
		

		string name{""};
		int number = 0;
		cout << "-------------HASH TABLE---------------" << endl;
		cout << "Types of collision resolution to choose:" << endl;
		cout << "[1]:Linear Probing\n[2]:chaining" << endl;
		cin >> number;
		if (number == 1)
		{
			for (int i = 0; i < MAX; i++)
			{
				hashtable[i] = nullptr;
			}
			cout << "using Linear Probing for hash table" << endl;
			cout << "Hash table size: " << MAX << endl;
			cout << "load the file: iliad.txt" << endl;
			readtext("iliad.txt",1);
			int count = 0;
			float percent = 0.0;
			for (int i = 0; i < MAX; i++)
			{

				if (hashtable[i] == nullptr)
				{
					count++;
				}

			}
			percent = (MAX - count) * 100 / MAX;
			cout << "How full is the hash table? :" << percent << "%" << endl;
			bool choice = true;
			while (choice)
			{
				char answer{ ' ' };
				cout << "Enter the word name" << endl;
				cin >> name;
				const char* mname = name.c_str();
				lsearch(mname);
				cout << "Do you want to quit(y/n)" << endl;
				cin >> answer;
				if (answer == 'y')
				{
					break;
				}
				cout << endl;
			}
			lclean();
		}
		else if (number == 2)
		{
			cout << "using chaining for hash table" << endl;
			cout << "Hash table size: " << MAX2 << endl;
			cout << "load the file: iliad.txt" << endl;
			string filename{ "iliad.txt" };
			//cin >> filename;
			readtext(filename,2);
			int count = 0;
			float percent = 0.0;
			for (int i = 0; i < MAX2; i++)
			{

				if (hashtable2[i] == nullptr)
				{
					count++;
				}

			}
			percent = (MAX2 - count) * 100 / MAX2;
			cout << "How full is the hash table? :" << percent << "%" << endl;
			bool choice = true;
			while (choice)
			{
				char answer{ ' ' };
				cout << "Enter the word name" << endl;
				cin >> name;
				const char* mname = name.c_str();
				csearch(mname);
				cout << "Do you want to quit(y/n)" << endl;
				cin >> answer;
				if (answer == 'y')
				{
					break;
				}
				cout << endl;
			}
			cclean();
		}
		system("pause");
		return 0;
	}