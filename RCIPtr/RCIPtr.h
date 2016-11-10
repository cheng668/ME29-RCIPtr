#pragma once
#include "RCObject.h"
/*This template can use to improve the efficiency of objects 
coping frequently ,and constructing and deleting costly. */
template<typename T>
class RCIPtr
{
public:
	RCIPtr(const T* readPtr = 0);
	RCIPtr(const RCIPtr& rhs);
	RCIPtr& operator=(const RCIPtr& rhs);
	~RCIPtr();

	T* operator->();
	const T* operator->() const;
	T& operator*();
	const T& operator*() const;
private:
	struct CountHolder:public RCObject
	{
		~CountHolder() { delete pointee; }
		T* pointee;
	};
	CountHolder* countHolder;
	void init();
	void makeCopy();
};

template<typename T>
void
RCIPtr<T>::init()
{
	if (!countHolder->isShareable())
	{
		T* oldValue = countHolder->pointee;
		countHolder = new CountHolder();//
		countHolder->pointee = new T(*oldValue);
	}
	countHolder->addRefCount();
}
/*
make deep copy
*/
template<typename T>
void
RCIPtr<T>::makeCopy()
{
	if (countHolder->isShare())
	{
		countHolder->removeRefCount();
		T* oldValue = countHolder->pointee;
		countHolder = new countHolder();
		countHolder->pointee = new T(*oldValue);
		countHolder->addRefCount();
	}
}

template<typename T>
RCIPtr<T>::RCIPtr(const T* realPtr):countHolder(new countHolder)//default constructor
{
	countHolder->pointee = realPtr;
	init();
}

template<typename T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs) :countHolder(rhs.countHolder)//default copy constructor
{
	init();
}

template<typename T>
RCIPtr<T>&
RCIPtr<T>::operator =(const RCIPtr& rhs)
{
	if (countHolder != rhs.countHolder)
	{
		countHolder->removeRefCount();
		countHolder = rhs.countHolder;
		init();
	}
	return *this
}

template<typename T>
RCIPtr<T>::~RCIPtr()
{
	countHolder->removeRefCount();
}

template<typename T>
T*
RCIPtr<T>::operator ->() 
{
	makeCopy(); return countHolder->pointee;
}

template<typename T>
const T* 
RCIPtr<T>::operator ->() const
{
	return countHolder->pointee;
}

template<typename T>
T& 
RCIPtr<T>::operator *()
{
	makeCopy(); return *(countHolder->pointee);
}

template<typename T>
const T&
RCIPtr<T>::operator *() const
{
	return *(countHolder->pointee);
}