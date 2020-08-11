#pragma once
#include <iostream>

namespace MyCustromVector {

	template<typename T, unsigned Size>
	class Vector
	{
	public:
		typedef T* Iterator;
		Vector(T val = T{});
		Vector(const Vector<T, Size>& src);  // copy constructor
		Vector(Vector<T, Size>&& src) = delete;
		~Vector();
		Vector<T, Size>& operator=(Vector<T, Size>& rh);  // copy assignment operator
		Vector<T, Size>& operator=(Vector<T, Size>&& rh) = delete;

		T& operator[](unsigned idx) const
		{
			if(idx < cSize)
				return *(pData + idx);
			std::cout << "ERROR! accessing element outside the range!\n";
			static T dummyValue{}; // this is needed to return a reference
			return dummyValue;
		}

		void  push(T val);  // pushing val to the end of the vector
		void push_front(T val); 
		void insert(unsigned pos, T val);
	

		T back() const
		{
			if(cSize > 0)
				return pData[cSize - 1];
			std::cout << "Error! accessing back() when vector is empty!\n";
			return T{};
		}
		void erase(unsigned pos);  // erase element at index pos. Elements after pos should shift left to replace the gap.
		void pop();  // pops the back element
		void pop_front(); // same as above, but pop from front of the vector

		Iterator begin() { return pData; }
		Iterator end() { return pData + cSize; }

		unsigned size() const { return cSize; }
		unsigned capacity() const { return maxSize; }
		bool empty() const { return cSize == 0; }
		unsigned GetSortState() const { return mStateSort; };

		// utility functions:
		template<typename Comparator = std::less<T>>
		void ascendingsort()
		{
			
			for (int k = 1; k < cSize; ++k)
			{
				T temp = pData[k];
				int i = k;

				while (i > 0 && pData[i - 1] >= temp)
				{
					pData[i] = pData[i - 1];
					--i;
				}
				pData[i] = temp;
			}
			
			mStateSort = 1;
			//std::sort(begin(), end(),Comparator());
		
		
		}

		template<typename Comparator = std::greater<T>>
		void descendingsort()
		{

			for (int k = 1; k < cSize; ++k)
			{
				T temp = pData[k];
				int i = k;

				while (i > 0 && pData[i - 1] <= temp)
				{
					pData[i] = pData[i - 1];
					--i;
				}
				pData[i] = temp;
			}
			//std::sort(begin(), end(), Comparator());

			mStateSort = 2;
		}

		// returns index of the val, if it is found. If not found, return -1
		int search(T val);
		int binsearchup(Iterator Data, int start, int end, T val);
		int binsearchdown(Iterator Data, int start, int end, T val);
		void Find(T val);
	
	private:
		unsigned maxSize{ Size };  // Max number of elements we can have in the vector
		unsigned cSize{0};     // current number of elements in the vector
		Iterator pData;

		bool expand(); 
		void shrink(); 
		unsigned mStateSort{ 0 };
		
	};

	template<typename T, unsigned B>
	std::ostream& operator<<(std::ostream& os, const Vector<T, B>& a)
	{

		os << "Vector content: " << "[Sort State: " << a.GetSortState() <<
			"]" << std::endl;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			os << a[i] << ", ";
		}
		os << std::endl;
		return os;
	}
	template<typename T, unsigned Size>
	Vector<T, Size>::Vector(T val): maxSize(Size), cSize(0), pData(nullptr)
	{
		if (maxSize > 0)
		{
			pData = new T[maxSize]{ val };
		}
	}

	template<typename T, unsigned Size>
	Vector<T, Size>::Vector(const Vector<T, Size>& src)
	{
		for (unsigned  i = 0; i < maxSize; i++)
		{
			pData[i] = src.pData[i];
		}
	}
	template<typename T, unsigned Size>
	inline Vector<T, Size>::~Vector()
	{
		delete[] pData;
	}
	template<typename T, unsigned Size>
	Vector<T, Size>& Vector<T, Size>::operator=(Vector<T, Size>& rh)
	{

		if(this!= &rh)

		{

			delete[] pData;

			maxSize = rh.maxSize;

			cSize= rh.cSize;



			pData = new T[maxSize];

			for(int k = 0; k < maxSize; k++)

			{

				pData[k] = rh.pData[k];

			}

		}
		if (mStateSort == 1)
		{
			this->ascendingsort();
		}
		else if (mStateSort == 2)
		{
			this->descendingsort();
		}
		return *this;
		 //TODO: insert return statement here
	}
	// this is default push_back
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::push(T val)
	{
		if (!expand())
			return;
		pData[cSize] = val;
		++cSize;
		if (mStateSort == 1)
		{
			this->ascendingsort();
		}
		else if (mStateSort == 2)
		{
			this->descendingsort();
		}
	}
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::push_front(T val)
	{
		if (!expand())
			return;
		// shift all elements after front, to the right by one slot, to make room.
		for (unsigned i = cSize; i > 0; --i)
			pData[i] = pData[i - 1];
		pData[0] = val;
		++cSize;
		if (mStateSort == 1)
		{
			this->ascendingsort();
		}
		else if (mStateSort == 2)
		{
			this->descendingsort();
		}

	}
	// insert val at index pos. 
	// first, push all elements from pos forward by one slot, to the right.
	// Then insert val at pos
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::insert(unsigned pos, T val)
	{
		if (mStateSort == 0) {
			if (pos < 0 || pos >= maxSize)
			{
				std::cout << "Error, Fail to insert" << std::endl;
				return;
			}

			Iterator newData{ new T[maxSize + 1] };
			newData[pos] = val;
			for (unsigned i = 0; i < pos; ++i)
				newData[i] = pData[i];
			for (unsigned i = pos; i < cSize; ++i)
				newData[i + 1] = pData[i];
			delete[] pData;
			pData = newData;
			cSize += 1;
			maxSize += 1;
		}
		else if (mStateSort == 1)
		{
			Iterator newData{ new T[maxSize + 1] };
			newData[cSize] = val;
			for (unsigned i = 0; i < cSize; ++i)
				newData[i] = pData[i];
			delete[] pData;
			pData = newData;
			cSize += 1;
			maxSize += 1;
			this->ascendingsort();

		}
		else if (mStateSort == 2)
		{
			Iterator newData{ new T[maxSize + 1] };
			newData[cSize] = val;
			for (unsigned i = 0; i < cSize; ++i)
				newData[i] = pData[i];
			delete[] pData;
			pData = newData;
			cSize += 1;
			maxSize += 1;
			this->descendingsort();
		}

	}


	// erases element at index pos. It then shifts all elements after pos to the left by one slot.
	// remember check for access violation accessing elements after cSize
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::erase(unsigned pos)
	{
		if (cSize <= 0 || maxSize <= 0)
		{
			std::cout << "ERROR!The array is empty" << std::endl;
		}
		else
		{
			if (pos < 0 || pos >= maxSize)
			{
				std::cerr << "Error, Fail to erase" << std::endl;
				return;
			}
			Iterator newData{ new T[maxSize - 1] };
			for (unsigned  i = 0; i < pos; ++i)
				newData[i] = pData[i];
			for (unsigned  i = pos; i < cSize; ++i)
				newData[i] = pData[i + 1];
			delete[] pData;
			pData = newData;
			cSize -= 1;
			maxSize -= 1;

		}
	}
	// this is default pop_back
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::pop()
	{
		if (cSize <= 0)
		{
			std::cout << "The array is empty" << std::endl;
			return;
		}
		this->erase(cSize-1);


	}
	// similar to push_front, but pops the front elmenent. Remember to fill the gap after.
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::pop_front()
	{
		if (cSize <= 0)
		{
			std::cout << "The array is empty" << std::endl;
			return;
		}
		this->erase(0);
	}

	// expansion happens by adding half of current maxSize to the maxSize, i.e. maxSize += maxSize/2
	// first allocate new pData, then copy the data in current pData to the new pData, then delete old pData
	template<typename T, unsigned Size>
	inline bool Vector<T, Size>::expand()
	{
		if (cSize < maxSize)
			return true;
		unsigned newSize{ maxSize + maxSize / 2 };
		std::cout << "expanding from capacity " << capacity() << " to  new capacity " << newSize << std::endl;
		Iterator newData{ new T[newSize] };
		if (nullptr == newData)
		{
			std::cout << "allocation failed! Ignore expansion!\n";
			return false;
		}
		
		memcpy_s(newData, newSize * sizeof(T), pData, cSize * sizeof(T));
		delete[] pData;
		maxSize = newSize;
		pData = newData;
	}

	// shrinking happens opposite to expansion, i.e. maxSize -= maxSize/2.
	// THis is done only when cSize < maxSize / 2
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::shrink()
	{
		if (cSize >= (maxSize / 2))
			return;

		unsigned newSize{ maxSize - maxSize / 3 };
		std::cout << "shrinking from capacity " << capacity() << " to  new capacity " << newSize << std::endl;
		Iterator newData{ new T[newSize] };
		if (nullptr == newData)
			return;
		memcpy_s(newData, newSize * sizeof(T), pData, cSize * sizeof(T));
		delete[] pData;
		maxSize = newSize;
		pData = newData;
	}

	template<typename T, unsigned Size>
	inline int Vector<T, Size>::search(T val)
	{

		if (mStateSort == 0)
		{
			for (unsigned i = 0; i < cSize; i++)
			{
				if (val == pData[i])
				{
					return i;
				}

			}
			return -1;

		}
		else if (mStateSort == 1)
		{
			return binsearchup(pData, 0, cSize - 1,val);


		}

		else if (mStateSort == 2)
		{
			return binsearchdown(pData, 0, cSize - 1, val);
		}
	
	
	
	
	}

	template<typename T, unsigned Size>
	inline int Vector<T, Size>::binsearchup(Iterator Data, int start, int end, T val)
	{
		if (Data == nullptr || start > end)
			return -1;
		int mid = start + (end-start) / 2;
		if (Data[mid] == val)
			return mid;
		else if (Data[mid] > val)
			return binsearchup(Data, start, mid - 1, val);
		else if (Data[mid] < val)
			return binsearchup(Data, mid + 1, end, val);

		return -1;
	}

	template<typename T, unsigned Size>
	inline int Vector<T, Size>::binsearchdown(Iterator Data, int start, int end, T val)
	{
		if (Data == nullptr || start > end)
			return -1;
		int mid = start + (end-start) / 2;
		if (Data[mid] == val)
			return mid;
		else if (Data[mid] < val)
			return binsearchdown(Data, start, mid - 1, val);
		else if (Data[mid] > val)
			return binsearchdown(Data, mid + 1, end, val);
	}
	template<typename T, unsigned Size>
	inline void Vector<T, Size>::Find(T val)
    {
		int IsFind = -1;
		IsFind = search(val);
		if (IsFind <0||IsFind>=maxSize)
		{
			std::cout << "The value "<< val<<" is not found" << std::endl;

		}
		else
		{
			std::cout << "The position of valve " << val << " is: " << IsFind << std::endl;
		}

	
	
	}
}
