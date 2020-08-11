#pragma once
#include <iostream>
#include <string>

namespace VGP220 {

	template <typename T>
	class CustomArray
	{
	public:

		CustomArray(int sz) : mMaxSize(sz), mSize(0)
		{
			if (sz <= 0)
				return;
			// allocate memory and assign each element to T()
			mData = new T[mMaxSize]();
		}

		~CustomArray()
		{
			if (mData)
				delete[] mData;
		}
		void print()
		{
			for (int i = 0; i < mSize; ++i)
				std::cout << "arr[" << i << "]: " << mData[i] << std::endl;

			std::cout <<"Max Size: "<<mMaxSize<< std::endl << std::endl;
		}
		void remove(int pos)
		{
			if (mSize <= 0 || mMaxSize <= 0)
			{
				std::cout << "ERROR!The array is empty" << std::endl;
			}
			else
			{
				if (pos < 0 || pos >= mMaxSize)
				{
					std::cerr << "Error, there is no such position, fail to remove" << std::endl;
					return;
				}

				T *tmpBuff{ new T[mMaxSize - 1]() };
				for (int i = 0; i < pos; ++i)
					tmpBuff[i] = mData[i];
				for (int i = pos; i < mSize; ++i)
					tmpBuff[i] = mData[i + 1];
				delete[] mData;
				mData = tmpBuff;
				mSize -= 1;
				mMaxSize -= 1;
			}
		}
		void insert(int pos, T val)
		{
			if (pos < 0 || pos >= mMaxSize)
			{
				std::cerr << "Error, Fail to insert" << std::endl;
				return;
			}

			T *tmpBuff{ new T[mMaxSize + 1]() };
			tmpBuff[pos] = val;
			for (int i = 0; i < pos; ++i)
				tmpBuff[i] = mData[i];
			for (int i = pos; i < mSize; ++i)
				tmpBuff[i + 1] = mData[i];
			delete[] mData;
			mData = tmpBuff;
			mSize += 1;
			mMaxSize += 1;

		}

		int search(T val)
		{
			for (int i = 0; i < mSize; ++i)
			{
				if (mData[i] == val)
					return i;
			}
			return -1;
		}
		void push(T val)
		{
			if (mSize >= mMaxSize)
			{
				if (!grow())
				{
					std::cerr << "Failed to grow the array! Ignore push!\n";
					return;
				}
			}
			mData[mSize++] = val;
		}

		void pop()
		{
			if (mSize <= 0)
				return;

			--mSize;
			mData[mSize] = T();
			shrink();
		}

		T& operator[](int i)
		{
			if (i < 0 || i >= mSize)
			{
				std::cerr << "!!Error! Trying to access ouf of range element!\n";
			}
			return *(mData + i);
		}
		int Size() const { return mSize; }
	private:
		bool grow();
		void shrink();
		T* mData{ nullptr };  // buffer to contains the data items.
		int mMaxSize{ 0 };  // Max possible number of items in the array
		int mSize{ 0 };   // current number of items in the array
	};

	template<typename T>
	bool CustomArray<T>::grow()
	{
		std::cout << "growing array ....\n";
		T *tmpBuff{ new T[2 * mMaxSize]() };
		if (tmpBuff == nullptr)
		{
			std::cerr << "ERROR! failed to allocate " << (2 * mMaxSize * sizeof(T)) <<
				" bytes to grow the array.\n";
			return false;
		}
		mMaxSize *= 2;   // this policy for growth can be changed as needed.
		for (int i = 0; i < mSize; ++i)
			tmpBuff[i] = mData[i];
		// check if tmpBuff need to be initialized to default T: T() ?
		for (int i = mSize; i < mMaxSize; ++i)
			tmpBuff[i] = T();
		delete[] mData;
		mData = tmpBuff;
	}

	template<typename T>
	void CustomArray<T>::shrink()
	{
		if (mSize * 2 >= mMaxSize)
		{
			std::cout << "Shrinking fail\n";
			return;
		}
		std::cout << "Shrinking array...\n";
		T *tmpBuff{ new T[mMaxSize / 2]() };
		if (tmpBuff == nullptr)
		{
			std::cerr << "Warning! Memory allocation failed for shrinking array...\n";
			return;
		}
		for (int i = 0; i < mSize; ++i)
			tmpBuff[i] = mData[i];

		mMaxSize /= 2;
		delete[] mData;
		mData = tmpBuff;
	}
	template<>
	void CustomArray<Person>::print()
	{
		for (int i = 0; i < mSize; ++i)
		{
			std::cout << "Student[" << i << "]: (" << mData[i].name << "," << mData[i].age << ")" << std::endl;
		}
		std::cout << "Max Size: " << mMaxSize << std::endl << std::endl;
	}

	template<>
	void CustomArray<Person>::insert(int pos, Person val)
	{
		if (pos < 0 || pos >= mMaxSize)
		{
			std::cerr << "Error, Fail to insert" << std::endl;
			return;
		}

		Person *tmpBuff{ new Person[mMaxSize + 1]() };
		tmpBuff[pos] = val;
		for (int i = 0; i < pos; ++i)
			tmpBuff[i] = mData[i];
		for (int i = pos; i < mSize; ++i)
			tmpBuff[i + 1] = mData[i];
		delete[] mData;
		mData = tmpBuff;
		mSize += 1;
		mMaxSize += 1;

	}
	template<>
	void CustomArray<Person>::remove(int pos)
	{
		if (mSize <= 0 || mMaxSize <= 0)
		{
			std::cout << "ERROR!The array is empty" << std::endl;
		}
		else
		{
			if (pos < 0 || pos >= mMaxSize)
			{
				std::cerr << "Error, Fail to remove" << std::endl;
				return;
			}

			Person *tmpBuff{ new Person[mMaxSize - 1]() };
			for (int i = 0; i < pos; ++i)
				tmpBuff[i] = mData[i];
			for (int i = pos; i < mSize; ++i)
				tmpBuff[i] = mData[i + 1];
			delete[] mData;
			mData = tmpBuff;
			mSize -= 1;
			mMaxSize -= 1;
		}
	}

	template<>
	int CustomArray<Person>::search(Person val)
	{
		for (int i = 0; i < mSize; ++i)
		{
			if (mData[i].age == val.age &&strcmp(mData[i].name, val.name) == 0)
				return i;
		}
		return -1;
	}
}
