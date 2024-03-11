#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Node
{
	T value;
	Node<T>* Next;
};
template <typename T>
class List
{
private:
	Node<T>* Head;
	Node<T>* Tail;
	int size;
public:
	List();
	Node<T>* Gethead();
	void insert(T);
	bool find(T);
	int getSize();
	T& get(int);
	int getIndex(T);
	void display();
};

template<typename T>
inline List<T>::List()
{
	Head = nullptr;
	Tail = nullptr;
	size = 0;
}

template<typename T>
inline Node<T>* List<T>::Gethead()
{
	return Head;
}

template<typename T>
inline void List<T>::insert(T data)
{
	if (Head == nullptr)
	{
		Head = new Node<T>;
		Tail = Head;
	}
	else
	{
		Tail->Next = new Node<T>;
		Tail = Tail->Next;
	}
	Tail->value = data;
	Tail->Next = nullptr;
	size++;
}

template<typename T>
inline bool List<T>::find(T data)
{
	Node<T>* temp = Head;
	while (temp != nullptr)
	{
		if (temp->value == data)
			return true;
		temp = temp->Next;
	}
	return false;
}

template<typename T>
inline int List<T>::getSize()
{
	return size;
}

template<typename T>
inline T& List<T>::get(int index)
{
	Node<T>* temp = Head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->Next;
	}
	return temp->value;
}

template<typename T>
inline int List<T>::getIndex(T data)
{
	Node<T>* temp = Head;
	int count = 0;
	while (temp != nullptr)
	{
		if (temp->value == data)
			return count;
		count++;
		temp = temp->Next;
	}
	return -1;
}

template<typename T>
inline void List<T>::display()
{
	Node<T>* temp = Head;
	while (temp != nullptr)
	{
		cout << temp->value << "  ";
		temp = temp->Next;
	}
	cout << endl;
}
