#include <iostream>
#include <Windows.h>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define tab "\t"

using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Element;
class ForwardList;
ForwardList operator+(ForwardList left, ForwardList right);



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
	//--------Geters---------

	unsigned int get_size()
	{
		return size;
	}

	//----------Constructor----------
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor : "<< this << endl;
		
	}
	ForwardList(unsigned int n): ForwardList()
	{
		
		for (size_t i = 0; i < n; i++)
		{
			push_front(0);
		}
		cout << "NConstructor : " << this << endl;

	}

	ForwardList(const ForwardList& other) : ForwardList()
	{
		for (size_t i = 0; i < other.size; i++)
		{
			push_front(other[other.size-i-1]);
		}
		cout << "CopyConstructor:\t\t" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept
	{
		size = other.size;
		Head = other.Head;

		
		other.Head = nullptr;
		cout << "MoveConstructor" << this << endl;
	}
	ForwardList(const initializer_list<int>& il): ForwardList()
	{
		int size_il = sizeof(il) / sizeof(int);
		for (int const* it = il.end()-1; it!=il.begin()-1;it--)
		{
			push_front(*it);
		}
		
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
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*if (Head == nullptr)//проверяем является список пустым
			return push_front(Data);
		Element* New = new Element(Data);//создаем новый элемент
		Element* Temp = Head;//итератор
		while (Temp->pNext != nullptr)//доходим до конца списка
		{			
			Temp = Temp->pNext;
		}		
		Temp->pNext = New;//присоеденяем новый элемент к последнему
		size++;*/
		if (Head == nullptr)
			return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, nullptr);
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
		/*if (index == 0|| Head == nullptr) return push_front(Data);
		if (index > size)return;	
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (size_t i = 0; i < index-1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;*/

		if (index == 0|| Head == nullptr) return push_front(Data);
		if (index > size)return;		
		Element* Temp = Head;
		for (size_t i = 0; i < index-1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data,Temp->pNext);
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
	/*void ForwardListRND( int begin, int end)
	{
		for (size_t i = 0; i < size; i++)
		{
			this[i] = rand() % (end - begin + 1) + begin;
		}
	}*/
	void reverse(ForwardList& other)
	{
		for (size_t i = 0; i < other.get_size(); i++)
		{
			push_front(other[i]);
		}		
	}
	/*void reverse()
	{
		int tmp;
		for (size_t i = 0; i < size; i++)
		{
			tmp = this[i];

		}
	}*/
	void unique(ForwardList& other)
	{
		bool flag;
		for (size_t i = 0; i < other.get_size(); i++)
		{
			flag = 0;
			for (size_t j = 0; j < other.get_size(); j++)
			{
				if (other[i] == other[j]&&i!=j)
				{
					flag = 1;
				}
				
			}
			if (flag == 0)push_front(other[i]);			
		}
	}


	//----------Operators----------
	int& operator[](int n)
	{
		Element* temp = Head;
		
		for (size_t i = 0; i < n; i++)temp = temp->pNext;		
		return temp->Data;
	}
	const int& operator[](int n)const
	{
		Element* temp = Head;
		
		for (size_t i = 0; i < n; i++)temp = temp->pNext;
		return temp->Data;
	}


};

//#define BASE CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define COPY_CONSTRACTOR
//#define REVERSE
//#define UNIQUE
#define HOME_WORK_2
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

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
#ifdef COPY_CONSTRACTOR
	ForwardList list1(5);
	ForwardList list2(5);
	for (size_t i = 0; i < 5; i++)
	{
		list1[i] = rand() % 100;
	}
	for (size_t i = 0; i < 5; i++)
	{
		list2[i] = rand() % 100;
	}
	list1.print();
	cout << endl;
	list2.print();
	ForwardList list3 = list1+list2;
	list3.print();
#endif // COPY_CONSTRACTOR
#ifdef REVERSE
	ForwardList list4(3);
	ForwardList list5(0);
	for (size_t i = 0; i < 3; i++)
	{
		list4[i] = rand() % 100;
	}
	list4.print();
	list5.reverse(list4);
	list5.print();
#endif // REVERSE
#ifdef UNIQUE
	ForwardList list6(10);
	ForwardList list7(0);
	for (size_t i = 0; i < 10; i++)
	{
		list6[i] = rand() % 10;
	}
	list6.print();
	list7.unique(list6);
	list7.print();
#endif // UNIQUE
#ifdef HOME_WORK_2
	ForwardList list7 = { 3,5,8,13,21 };
	list7.print();
#endif // HOME_WORK_2



	return 0;
}





ForwardList operator+(ForwardList left, ForwardList right)
{
	ForwardList result(left.get_size() + right.get_size());
	for (size_t i = 0; i < left.get_size(); i++)
	{
		result[i] = left[i];
	}
	for (size_t i = 0; i < right.get_size(); i++)
	{
		result[left.get_size()+i] = right[i];
	}
	return result;
}
