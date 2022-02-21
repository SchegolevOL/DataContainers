#include <iostream>
#include <Windows.h>

#define tab "\t"

using namespace std;



template<typename T>
class List
{
	class Element
	{
		T Data;//Значение элемента
		Element* pNext;//Адрес следующего элемента
		Element* pPrev;//Адрес предыдущего элемента
	public:
		//----------Constructor----------
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data),pNext(pNext),pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor : \t" << this << endl;
#endif // DEBUG

		}
		//----------Destructor----------
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor : \t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
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
#ifdef DEBUG
			cout << "BItConstructor" << this << endl;
#endif // DEBUG

		}
		virtual ~BaseIterator()
		{
#ifdef DEBUG
			cout << "BItDestructor" << this << endl;
#endif // DEBUG

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
		const T& operator*()const//for 
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
#ifdef DEBUG
			cout << "CItConstructor" << this << endl;
#endif // DEBUG
		}
		virtual ~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator ++()//Prefix  
		{
			BaseIterator :: Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator ++(int)//Postfix 
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old; 
		}
		ConstIterator& operator --()//Prefix  
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int)//Postfix 
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		
	};


	class ConstReverseIterator: public BaseIterator
	{
		public:

		ConstReverseIterator(Element* Temp) : BaseIterator(Temp) 
		{
#ifdef DEBUG
			cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG

		}

		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CRItDestructor:\t" << this << endl;

#endif // DEBUG
		}

		ConstReverseIterator& operator ++()//Prefix  
		{
			BaseIterator::set_Temp(BaseIterator::get_Temp()->pPrev);
			return *this;
		}
		ConstReverseIterator operator ++(int)//Postfix 
		{
			ConstReverseIterator old = *this;
			set_Temp(BaseIterator::get_Temp()->pPrev);
			return old;
		}

		ConstReverseIterator& operator --()//Prefix  
		{
			BaseIterator::set_Temp(BaseIterator::get_Temp()->pNext);
			return *this;
		}
		ConstReverseIterator operator --(int)//Postfix 
		{
			ConstReverseIterator old = *this;
			set_Temp(BaseIterator::get_Temp()->pNext);
			return old; 
		}
	
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;

#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;

#endif // DEBUG
		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
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
#ifdef DEBUG
		cout << "LConstructor : " << this << endl;
#endif // DEBUG

	}
	List(const List& other) : List()
	{
		for (size_t i = 0; i < other.size; i++)
		{
			push_front(other[other.size - i - 1]);
		}
#ifdef DEBUG
		cout << "CopyConstructor:\t\t" << this << endl;
#endif // DEBUG

	}
	List(List&& other)noexcept
	{
		size = other.size;
		Head = other.Head;
		Tail = other.Tail;
		other.Head = nullptr;
#ifdef DEBUG
		cout << "MoveConstructor" << this << endl;
#endif // DEBUG

	}
	List(const initializer_list<T>& il) : List()
	{
		for (T const* it = il.begin(); it != il.end(); ++it)
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
#ifdef DEBUG
		cout << "LDestructor : " << this << endl;
#endif // DEBUG

	}

	//---------------Addingng elements-------------------
	void push_front(T Data)
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
	void push_back(T Data)
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
	void insert(int index, T Data)
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
	T& operator[](int n)
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
	const T& operator[](int n)const
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

	List<int> list;
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
	List<int> list2 = { 3, 5, 8, 13, 21 };
	for (int i : list2)cout << i << tab; cout << endl;
#endif //  BASE_CHEK
	List<int> list3 = { 3, 5, 8, 13, 21 };
	list3.print();
	for (int i : list3)cout << i << tab; 
	cout << endl;

	for (List<int> :: ConstReverseIterator it = list3.crbegin(); it ; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	List <double> d_list = { 2.3,2.6,1.2,1.9 };
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
		cout << *it << tab;
	cout << endl;
	List<string>s_list = { "have"," a"," nise"," day" };
	for (string i : s_list)cout << i; cout << endl;
	for (List<string>::ReverseIterator it = s_list.rbegin(); it; ++it)
		cout << *it << endl;
	

	return 0;
}
