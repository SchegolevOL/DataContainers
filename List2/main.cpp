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
		friend class Iterator;
	}*Head, *Tail;//Element* Temp; Element* Tail; тоже самое


public: 
	class BIterator
	{
		Element* Temp;
	public:

		Element* get_Temp()
		{
			return Temp;
		}
		void set_Temp(Element* (Temp))
		{
			this->Temp = Temp;
		}
		BIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor" << this << endl;
		}
		virtual ~BIterator()
		{
			cout << "ItDestructor" << this << endl;
		}
		bool operator ==(const BIterator& other)const//for 
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const BIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int& operator*()//for 
		{
			return Temp->Data;
		}
		const int& operator*()const//for 
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}
	};




	class Iterator: public BIterator
	{

		Iterator(Element* Temp = nullptr) :BIterator(Temp)
		{
			cout << "ItConstructor" << this << endl;
		}
		virtual ~Iterator()
		{
			cout << "ItDestructor" << this << endl;
		}
		Iterator& operator ++()//Prefix  
		{
			set_Temp(get_Temp()->pNext);
			return *this;
		}
		Iterator operator ++(int)//Postfix 
		{
			Iterator old = *this;
			set_Temp(get_Temp()->pNext);
			return old; 
		}
		Iterator& operator --()//Prefix  
		{
			set_Temp(get_Temp()->pPrev);
			return *this;
		}
		Iterator operator --(int)//Postfix 
		{
			Iterator old = *this;
			set_Temp(get_Temp()->pPrev);
			return old;
		}
		
	};
	class ReverseIterator: public BIterator
	{
		//Element* Temp;
	public:

		ReverseIterator(Element* Temp) : BIterator(Temp) 
		{
			cout << "RItConstructor" << this << endl;
		}

		~ReverseIterator()
		{
			cout << "ItDestructor" << this << endl;
		}

		ReverseIterator& operator ++()//Prefix  
		{
			set_Temp(get_Temp()->pPrev);
			return *this;
		}
		ReverseIterator operator ++(int)//Postfix 
		{
			ReverseIterator old = *this;
			set_Temp(get_Temp()->pPrev);
			return old;
		}

		ReverseIterator& operator --()//Prefix  
		{
			set_Temp(get_Temp()->pNext);
			return *this;
		}
		ReverseIterator operator --(int)//Postfix 
		{
			ReverseIterator old = *this;
			set_Temp(get_Temp()->pNext);
			return old; 
		}
		
		/*bool operator ==(const ReverseIterator& other)const//for 
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int& operator*()//for 
		{
			return Temp->Data;
		}
		const int& operator*()const//for 
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}*/
	};
	class ConstIterator:public BIterator
	{
	public:
		const ConstIterator(Element* Temp): BIterator(Temp)
		{
			cout << "CItConstructor" << this << endl;
		}

		~ConstIterator()
		{
			cout << "ItDestructor" << this << endl;
		}

	};

	class ConstReverseIterator :public BIterator
	{
	public:
		const ConstReverseIterator(Element* Temp) : BIterator(Temp)
		{
			cout << "CRItConstructor" << this << endl;
		}

		~ConstReverseIterator()
		{
			cout << "ItDestructor" << this << endl;
		}

	};







private:
	size_t size;

public:
	//----------Gerters-----------
	size_t get_size()
	{
		return size;
	}
	//----------Constructor----------
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor : " << this << endl;
	}
	List(const List& other) : List()
	{
		for (size_t i = 0; i < other.size; i++)
		{
			push_front(other[other.size - i - 1]);
		}
		cout << "CopyConstructor:\t\t" << this << endl;
	}
	List(List&& other)noexcept
	{
		size = other.size;
		Head = other.Head;
		Tail = other.Tail;
		other.Head = nullptr;
		cout << "MoveConstructor" << this << endl;
	}
	List(const initializer_list<int>& il) : List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}

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
		/*if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		Head = Head->pPrev =  new Element(Data, Head);*/
		
		Head == nullptr && Tail == nullptr? Head = Tail = new Element(Data, Head): Head = Head->pPrev = new Element(Data, Head);
		size++;

		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/

		size++;
	}
	void push_back(int Data)
	{
		/*if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data,nullptr,Tail);
		size++;*/
		Head == nullptr && Tail == nullptr? Head = Tail = new Element(Data, Head): Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int index, int Data)
	{	

		if (index > size)return;
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data, Head);
			size++;
			return;
		}
		if (index == 0) return push_front(Data);
		if (index == size)return push_back(Data);
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
		if (index == size - 1) return pop_back();
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
			for (size_t i = size; i > index+1; i--)
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
	int& operator[](int n)
	{
		if (n<=size/2)
		{
			Element* Temp = Head;
			for (size_t i = 0; i < n; i++)
				Temp = Temp->pNext;;
			return Temp->Data;
		}
		else
		{
			Element* Temp = Tail;
			for (size_t i = size; i > n + 1; i--)
				Temp = Temp->pPrev;;
			return Temp->Data;
		}
		
	}
	const int& operator[](int n)const
	{
		if (n <= size / 2)
		{
			Element* Temp = Head;
			for (size_t i = 0; i < n; i++)
				Temp = Temp->pNext;;
			return Temp->Data;
		}
		else
		{
			Element* Temp = Tail;
			for (size_t i = size; i > n + 1; i--)
				Temp = Temp->pPrev;;
			return Temp->Data;
		}
	}
	Iterator begin()//for 
	{
		return this->Head;
	}
	Iterator end()//for
	{
		return nullptr;
	}


	ReverseIterator rbegin()//for 
	{
		return this->Tail;
	}
	ReverseIterator rend()//for
	{
		return nullptr;
	}
};


#define BASE_CHEK
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#ifdef BASE_CHEK

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
	list.insert(7, 1000);
	list.print();
	list.erase(1);
	list.print();
	list.erase(5);
	list.print();
	/*for (size_t i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}*/
	cout << endl;
	List list2 = { 3, 5, 8, 13, 21 };
	for (int i : list2)cout << i << tab; cout << endl;
#endif //  BASE_CHEK
	List list3 = { 3, 5, 8, 13, 21 };
	list3.print();
	for (int i : list3)cout << i << tab; 
	cout << endl;

	for (List :: ReverseIterator it = list3.rbegin(); it ; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	return 0;
}
