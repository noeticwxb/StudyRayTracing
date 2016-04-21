#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_ 1
#include "config.h"


template<typename T> class DynArray
{
public:
	DynArray();
	DynArray(int capacity);
	~DynArray();

	bool append(T item);
	bool truncate();
	void clear() { mSize = 0; }
	int length() { return mSize; }
	bool empty(){ return mSize == 0; }

	const T& operator[](int i) const { return mData[i]; }
	T& operator[](int i){ return mData[i]; }

private:
	T* mData;
	int mSize;
	int mCapacity;
};

template<typename T> 
DynArray<T>::DynArray()
{
	mSize = 0;
	mCapacity = 4;
	mData = NEW_ARRAY(T, mCapacity);
}

template<typename T> 
DynArray<T>::DynArray(int capacity)
{
	mSize = 0;
	mCapacity = capacity;
	mData = NEW_ARRAY(T, mCapacity);
}

template<typename T> 
DynArray<T>::~DynArray()
{
	mSize = 0;
	mCapacity = 0;
	SAFE_DELETE_ARRAY(mData);
}

template<typename T> 
bool DynArray<T>::truncate()
{
	if (mSize!=mCapacity)
	{
		T* temp = mData;

		if (!(mData = NEW_ARRAY(T, mSize)))
		{
			mData = temp;
			return false;
		}

		mCapacity = mSize;
		for (int i = 0; i < mSize;++i)
		{
			mData[i] = temp[i];
		}

		DELETE_ARRAY(temp);
		return true; 
	}
}

template<typename T>
bool DynArray<T>::append(T item)
{
	if (mSize==mCapacity)
	{
		T* temp = mData;

		if (!(mData = NEW_ARRAY(T, mCapacity*2)))
		{
			mData = temp;
			return false;
		}

		mCapacity *= 2;
		for (int i = 0; i < mSize; ++i)
		{
			mData[i] = temp[i];
		}
		DELETE_ARRAY(temp);
	}
	mData(mSize++) = item;
	return true;
}


#endif