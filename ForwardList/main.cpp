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
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) 
	{
		cout << "EConstructor : " << this << endl; 
		count++;
	}
	~Element() 
	{ 
		
		cout << "EDestructor : " << this << endl; 
		count--;
		
	}
	friend class ForwardList;// дружественный класс
};

int Element::count = 0;

class ForwardList //односвязный список
{
	Element* Head;
	unsigned int size;//размер списка
public:

	//----------Constructor----------
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor : "<< this << endl;
		
	}
	ForwardList(int n)
	{
		Head = nullptr;
		size = 0;
		for (size_t i = 0; i < n; i++)
		{
			push_front(0);
		}
		cout << "NConstructor : " << this << endl;

	}

	~ForwardList() 
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor : " << this << endl;

	};

	//---------------Addingng elements-------------------
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head==nullptr)//проверяем является список пустым
			return push_front(Data);
		Element* New = new Element(Data);//создаем новый элемент
		Element* Temp = Head;//итератор
		while (Temp->pNext != nullptr)//доходим до конца списка
		{			
			Temp = Temp->pNext;
		}		
		Temp->pNext = New;//присоеденяем новый элемент к последнему
		size++;

	}

	//--------------Remaving elements--------------------
	void pop_front()
	{
		if (Head==nullptr)return;
		Element* Erased = Head;//итератор
		Head = Erased->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;	
		size--;
	}
	void insert(int index, int Data)
	{		
		if (index == 0|| Head == nullptr) return push_front(Data);
		if (index > size)return;	
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (size_t i = 0; i < index-1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void erase(int index)
	{
		if (index == 0) return pop_front();
		if (index > size)return;
		Element* Temp = Head;
		Element* Ell;
		for (size_t i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Ell = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete	Ell;
		size--;
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
		cout << "Общее количество элементов списка : " << Head->count << endl;
		cout << "Количество элементов списка : " << size<< endl;
	}
	//----------Operators----------
	int& operator[](int n)
	{
		Element* temp = Head;
		int data;
		if (n==0)return Head->Data;
		for (size_t i = 0; i < n; i++)temp = temp->pNext;		
		return temp->Data;
	}

};

//#define BASE CHECK
//#define DESTRUCTOR_CHECK
#define HOME_WORK_1

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


#ifdef BASE CHECK
	int n;
	cout << "Введите размер списка : "; cin >> n;
	ForwardList list;
	for (size_t i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << "------------------" << endl;
	list.push_back(111);	
	list.print();
	cout << "------------------" << endl;
	list.pop_back();
	list.print();
	cout << "------------------" << endl;
	list.push_front(111);	
	list.print();
	cout << "------------------" << endl;
	list.pop_front();	
	list.print();
	cout << "------------------" << endl;
	list.insert(6, 111);
	list.print();
	cout << "------------------" << endl;	
	list.erase(2);
	list.print();
	cout << "------------------" << endl;
#endif // BASE CHECK
	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	//cout << "Список заполнен" << endl;
	list.print();
#endif // DESTRUCTOR_CHECK




#ifdef HOME_WORK_1
	int n;
	cout << "Введите размер списка - "; cin >> n;
	ForwardList list (n);
	for (size_t i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (size_t i = 0; i < n; i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
		
#endif // HOME_WORK_1






	return 0;
}