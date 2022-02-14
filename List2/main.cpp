#include <iostream>
#include <Windows.h>

#define tab "\t"

using namespace std;

class List
{
	class Element
	{
		int Data;//Значение элемента
		Element* pNext;//Адрес следующего элемента
		Element* pPrev;//Адрес предыдущего элемента
	public:
		//----------Constructor----------
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data),pNext(pNext),pPrev(pPrev)
		{
			cout << "EConstructor : \t" << this << endl;
		}
		//----------Destructor----------
		~Element()
		{
			cout << "EDestructor : \t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;//Element* Temp; Element* Tail; тоже самое
	
	size_t size;

public:
	//----------Constructor----------
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor : " << this << endl;
	}
	//----------Destructor----------
	~List()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor : " << this << endl;
	}

	//---------------Addingng elements-------------------
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		Head = Head->pPrev =  new Element(Data, Head);
		

		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data,nullptr,Tail);
		size++;
	}
	void insert(int index, int Data)
	{		
		if (index > size+1)return;
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		if (index == 0) return push_front(Data);
		
		if (index<=size/2)
		{
			Element* Temp = Head;
			for (size_t i = 0; i < index - 1; i++)Temp=Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext, Temp);
			size++;
		}
		else
		{
			Element* Temp = Tail;
			for (size_t i = size; i >index+1 ; i--)
				Temp = Temp->pPrev;
			Temp->pNext = new Element(Data, Temp->pNext, Temp);
			size++;
		}
		
	}
	//--------------Remaving elements--------------------
	void pop_front()
	{
		if (Head == nullptr)return;
		if (Head->pNext->pNext == nullptr)
		{
			Head = Tail = nullptr;
			return;
		}
		Element* Erased = Head;//итератор
		Head = Erased->pNext;
		Erased->pNext->pPrev = nullptr;
		delete Erased;
		
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr&&Tail == nullptr)return;
		
		if (Head->pNext->pNext == nullptr)
		{
			Head = Tail = nullptr;
			return;
		}
		
		Element* Erased = Tail;//итератор
		Tail = Erased->pPrev;
		Tail->pNext = nullptr;
		delete Erased;
		size--;
	}
	void erase(int index)
	{
		if (Head == nullptr && Tail == nullptr)return;

		if (Head->pNext->pNext == nullptr)
		{
			Head = Tail = nullptr;
			return;
		}
		if (index == 0) return pop_front();
		if (index > size)return;
			
		if (index <= size / 2)
		{
			Element* Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = Temp->pNext;
			delete	Temp;
		}
		else
		{
			Element* Temp = Tail;
			for (size_t i = size-1; i > index; i--)
				Temp = Temp->pPrev;
			Temp->pNext->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = Temp->pNext;
			delete	Temp;
		}
		
		size--;
	}
	void print()const
	{
		cout << "Head = " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << "| Adress pPrev = " << Temp->pPrev << tab << "| Adres Element = " << Temp << tab << "| Data = " << Temp->Data << tab << "| Adress pNext = " << Temp->pNext << endl;
		}
		cout << "Tail = " << Tail << endl;
		cout << "Количество элементов списка : " << size << endl;

	}
	void reverse_print()const
	{
		cout << "Head = " << Head << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{		
			cout << "| Adress pPrev = " << Temp->pPrev << tab << "| Adres Element = " << Temp << tab << "| Data = " << Temp->Data << tab << "| Adress pNext = " << Temp->pNext << endl;
		
		}
		cout << "Tail = " << Tail << endl;
		cout << "Количество элементов списка : " << size << endl;

	}
	//----------Operators----------

};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List list;
	list.push_front(10);
	list.push_front(15);
	list.push_front(25);
	list.push_back(100);	
	list.print();
	list.reverse_print();

	list.pop_front();
	list.print();

	list.pop_back();
	list.print();
	list.insert(1, 0);
	list.print();
	list.push_front(10);
	list.push_front(15);
	list.push_front(25);
	list.push_back(100);
	list.print();
	list.insert(8,1000);
	list.print();
	list.erase(1);
	list.print();
	list.erase(4);
	list.print();
	return 0;
}
