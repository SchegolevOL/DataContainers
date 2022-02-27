#pragma once
#include <iostream>
#include <Windows.h>

#define tab "\t"

using namespace std;

template<typename T> class List
{
	class Element
	{
		T Data;//Значение элемента
		Element* pNext;//Адрес следующего элемента
		Element* pPrev;//Адрес предыдущего элемента
	public:
		
		//----------Constructor----------
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		//----------Destructor----------
		~Element();
		friend class List<T>;
		friend class ConstIterator;
		//friend Queue;

	}*Head, * Tail;//Element* Temp; Element* Tail; тоже самое

	void get_Head();
	 
	void get_Tail();
	
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:

		Element* get_Temp();
		void set_Temp(Element* (Temp));

		BaseIterator(Element* Temp = nullptr);
		virtual ~BaseIterator();
		virtual BaseIterator& operator ++() = 0;

		virtual BaseIterator& operator --() = 0;


		operator bool()const;
		bool operator ==(const BaseIterator& other)const;
		bool operator !=(const BaseIterator& other)const;
		const T& operator*()const;


	};


public:
	class ConstIterator :public BaseIterator
	{

	public:
		ConstIterator(Element* Temp);
		virtual ~ConstIterator();
		ConstIterator& operator ++();
		ConstIterator operator ++(int);
		ConstIterator& operator --();
		ConstIterator operator --(int);

	};


	class ConstReverseIterator : public BaseIterator
	{
	public:

		ConstReverseIterator(Element* Temp = nullptr);

		~ConstReverseIterator();

		ConstReverseIterator& operator ++();
		ConstReverseIterator operator ++(int);

		ConstReverseIterator& operator --();
		ConstReverseIterator operator --(int);

	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		T& operator*();
	};


private:
	size_t size;

public:
	//----------Gerters-----------
	size_t get_size();
	//----------Constructor----------
	List();
	List(const List& other);
	List(List&& other)noexcept;
	List(const initializer_list<T>& il);

	//----------Destructor----------
	virtual ~List();

	//---------------Addingng elements-------------------
	void push_front(T Data);
	void push_back(T Data);
	void insert(int index, T Data);
	//--------------Remaving elements--------------------
	void pop_front();
	void pop_back();
	void erase(int index);
	void print()const;
	void reverse_print()const;
	//----------Operators----------
	T& operator[](int n);
	const T& operator[](int n)const;
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	
	

};

template<typename T>
	class Queue: public List
	{
	public:
		Queue() :List() {}		
		Queue(const Queue& other) : List(other) {}		
		Queue(const initializer_list<T>& il) :List(il) {}
		Queue(Queue&& other)noexcept :List(other) {}
		
		void pop();
		void push(T data);
		T peek();
	};
