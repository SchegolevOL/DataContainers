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
		friend class ConstIterator;
	}*Head, *Tail;//Element* Temp; Element* Tail; тоже самое
	
	
	class BaseIterator
	{
	protected:
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

		BaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "BItConstructor" << this << endl;
		}
		virtual ~BaseIterator()
		{
			cout << "BItDestructor" << this << endl;
		}

		virtual BaseIterator& operator ++() = 0;
		
		virtual BaseIterator& operator --() = 0;
		

		operator bool()const
		{
			return Temp;
		}
		bool operator ==(const BaseIterator& other)const//for 
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}		
		const int& operator*()const//for 
		{
			return Temp->Data;
		}


	};
	

public: 
	class ConstIterator:public BaseIterator
	{
		
	public:
		ConstIterator(Element* Temp) : BaseIterator(Temp)
		{
			cout << "CItConstructor" << this << endl;
		}
		virtual ~ConstIterator()
		{
			cout << "CItDestructor" << this << endl;
		}
		ConstIterator& operator ++()//Prefix  
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator ++(int)//Postfix 
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old; 
		}
		ConstIterator& operator --()//Prefix  
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int)//Postfix 
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		
	};


	class ConstReverseIterator: public BaseIterator
	{
		public:

		ConstReverseIterator(Element* Temp) : BaseIterator(Temp) 
		{
			cout << "CRItConstructor:\t" << this << endl;
		}

		~ConstReverseIterator()
		{
			cout << "CRItDestructor:\t" << this << endl;
		}

		ConstReverseIterator& operator ++()//Prefix  
		{
			set_Temp(get_Temp()->pPrev);
			return *this;
		}
		ConstReverseIterator operator ++(int)//Postfix 
		{
			ConstReverseIterator old = *this;
			set_Temp(get_Temp()->pPrev);
			return old;
		}

		ConstReverseIterator& operator --()//Prefix  
		{
			set_Temp(get_Temp()->pNext);
			return *this;
		}
		ConstReverseIterator operator --(int)//Postfix 
		{
			ConstReverseIterator old = *this;
			set_Temp(get_Temp()->pNext);
			return old; 
		}
	
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		int& operator*()
		{
			return Temp->Data;
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
	ConstIterator cbegin()const//for 
	{
		return this->Head;
	}
	ConstIterator cend()const//for
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const//for 
	{
		return this->Tail;
	}
	ConstReverseIterator crend()const//for
	{
		return nullptr;
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

	for (List :: ConstReverseIterator it = list3.crbegin(); it ; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;





	return 0;
}
