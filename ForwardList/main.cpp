#include <iostream>
#include <Windows.h>
#include <string>
#include <math.h>
#define tab "\t"
using namespace std;
class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) 
	{ cout << "EConstructor : " << this << endl; }
	~Element() 
	{ cout << "EDestructor : " << this << endl; }
	friend class ForwardList;// дружественный класс
};

class ForwardList //односвязный список
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor : "<< this << endl;
	}
	~ForwardList() 
	{ cout << "LDestructor : " << this << endl; };

	//Addingng elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{			
			Temp = Temp->pNext;
		}		
		New->pNext = nullptr;
		Temp->pNext = New;
	}
	void pop_front()
	{
		Element* Temp = Head;
		Temp = Temp->pNext;
		Head = Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		Element* Back = Temp;;
		while (Temp->pNext != nullptr)
		{
			Back = Temp;
			Temp = Temp->pNext;
		}
		Back->pNext = nullptr;
	}
	void insert(int index, int value)
	{
			
		if (index == 0)
		{
			this->push_front(value);
		}else
		{
			Element* New = new Element(value);
			Element* Back = Head;
			Element* Next = Back->pNext;

			for (size_t i = 0; i < index-1 && Back->pNext != nullptr; i++)
			{
				Back = Next;
				Next = Back->pNext;
			}
			New->pNext = Next;
			Back->pNext = New;
		 }
	}
	void erase(int index)
	{
		if (index == 0)
		{
			this->pop_front();
		}
		else
		{
			Element* Temp = Head;
			Element* Next = Temp->pNext;
			for (size_t i = 0; i < index - 1 && Temp->pNext != nullptr; i++)
			{
				Temp = Next;
				Next = Temp->pNext;
			}
			if (Temp->pNext != nullptr)
			{
				Temp->pNext = Next->pNext;
			}
		}
	}




	//Metods
	void print()const
	{
		Element* Temp = Head;//- итератор- это указатель при
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//переход на следующий элемент
		}
	}
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введите размер списка : "; cin >> n;
	ForwardList list;
	for (size_t i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(101);
	cout << "------------------" << endl;
	list.print();
	list.pop_front();
	cout << "------------------" << endl;
	list.print();
	list.pop_back();
	cout << "------------------" << endl;
	list.print();
	list.insert(0, 111);
	cout << "------------------" << endl;
	list.print();
	list.erase(0);
	cout << "------------------" << endl;
	list.print();


	return 0;
}