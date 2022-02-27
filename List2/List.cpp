#include"List.h"




//--------class List----------------------------------------------------------------------
template<typename T> size_t List<T> ::get_size()
{
	return size;
}
template<typename T> List<T> ::List()
{
	Head = nullptr;
	Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor : " << this << endl;
#endif // DEBUG

}
template<typename T> List<T> ::List(const List& other) : List()
{
	for (size_t i = 0; i < other.size; i++)
	{
		push_front(other[other.size - i - 1]);
	}
#ifdef DEBUG
	cout << "CopyConstructor:\t\t" << this << endl;
#endif // DEBUG

}
template<typename T> List<T> ::List(List&& other)noexcept
{
	size = other.size;

	Head = other.Head;
	Tail = other.Tail;
	other.Head = nullptr;
#ifdef DEBUG
	cout << "MoveConstructor" << this << endl;
#endif // DEBUG

}
template<typename T> List<T> ::List(const initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}

}
template<typename T> List<T> ::~List()
{
	while (Head)
	{
		pop_front();
	}
#ifdef DEBUG
	cout << "LDestructor : " << this << endl;
#endif // DEBUG

}
template<typename T> void List<T> ::push_front(T Data)
{
	Head == nullptr && Tail == nullptr ? Head = Tail = new Element(Data, Head) : Head = Head->pPrev = new Element(Data, Head);
	size++;

}
template<typename T> void List<T> ::push_back(T Data)
{
	Head == nullptr && Tail == nullptr ? Head = Tail = new Element(Data, Head) : Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T> void List<T> ::insert(int index, T Data)
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
	if (index <= size / 2)
	{
		Element* Temp = Head;
		for (size_t i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext, Temp);
		size++;
	}
	else
	{
		Element* Temp = Tail;
		for (size_t i = size; i > index + 1; i--)
			Temp = Temp->pPrev;
		Temp->pNext = new Element(Data, Temp->pNext, Temp);
		size++;
	}

}
template<typename T> void List<T> ::pop_front()
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
template<typename T> void List<T> ::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;

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
template<typename T> void List<T> ::erase(int index)
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
		for (size_t i = size; i > index + 1; i--)
			Temp = Temp->pPrev;
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete	Temp;
	}

	size--;
}
template<typename T> void List<T> ::print()const
{
	cout << "Head = " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << "| Adress pPrev = " << Temp->pPrev << tab << "| Adres Element = " << Temp << tab << "| Data = " << Temp->Data << tab << "| Adress pNext = " << Temp->pNext << endl;
	}
	cout << "Tail = " << Tail << endl;
	cout << "Количество элементов списка : " << size << endl;

}
template<typename T> void List<T> ::reverse_print()const
{
	cout << "Head = " << Head << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << "| Adress pPrev = " << Temp->pPrev << tab << "| Adres Element = " << Temp << tab << "| Data = " << Temp->Data << tab << "| Adress pNext = " << Temp->pNext << endl;

	}
	cout << "Tail = " << Tail << endl;
	cout << "Количество элементов списка : " << size << endl;

}
template<typename T> T& List<T> :: operator [](int n)
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
template<typename T> const T& List<T> :: operator[](int n)const
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
template<typename T> typename List<T>::ConstIterator List<T>::cbegin()const//for 
{
	return this->Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::cend()const//for
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crbegin()const//for 
{
	return this->Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crend()const//for
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::begin()//for 
{
	return this->Head;
}
template<typename T> typename List<T>::Iterator List<T>::end()//for
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()//for 
{
	return this->Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()//for
{
	return nullptr;
}
template<typename T> void  List<T>::get_Head()
{
	return Head;
}
template<typename T> void  List<T>:: get_Tail()
{
	return Tail;
}
//-------------------------------------------------------------------------------------------------

//----------ReverseIterator-------------------------------------------------------------------------
template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T> T& List<T>::ReverseIterator::operator*()
{
	return List::BaseIterator::Temp->Data;
}
//--------------------------------------------------------------------------------------------------

//----------class Iterator--------------------------------------------------------------------------
template<typename T> List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;

#endif // DEBUG
}
template<typename T> List<T>::Iterator ::~Iterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;

#endif // DEBUG
}
template<typename T> T& List<T>::Iterator::operator*()
{
	return List<T>::Iterator::Temp->Data;
}
//--------------------------------------------------------------------------------------------------

//----------class BaseIterator---------------------------------------------------------------------
template<typename T> typename List<T>::Element* List<T>::BaseIterator::get_Temp()
{
	return List<T>::BaseIterator::Temp;
}
template<typename T> void List<T>::BaseIterator::set_Temp(Element* (Temp))
{
	this->Temp = Temp;
}
template<typename T> List<T>::BaseIterator::BaseIterator(List<T>::Element* Temp) :Temp(Temp) {
#ifdef DEBUG
	cout << "BItConstructor" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BItConstructor" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::BaseIterator:: operator bool()const
{
	return Temp;
}
template<typename T> bool List<T>::BaseIterator::operator ==(const List<T>::BaseIterator& other)const//for 
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::BaseIterator::operator !=(const List<T>::BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& List<T>::BaseIterator::operator*()const//for 
{
	return Temp->Data;
}
//--------------------------------------------------------------------------------------------------

//----------class ConstIterator---------------------------------------------------------------------
template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CItConstructor" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CItDestructor:\t" << this << endl;

#endif // DEBUG
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator ++()//Prefix  
{
	List<T>::ConstIterator::Temp = List<T>::ConstIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator ++(int)//Postfix 
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator --()//Prefix  
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator --(int)//Postfix 
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
//--------------------------------------------------------------------------------------------------

//----------class ConstReverseIterator--------------------------------------------------------------
template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "CRItDestructor:\t" << this << endl;

#endif // DEBUG
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator ++()//Prefix  
{
	List<T>::BaseIterator::set_Temp(List<T>::BaseIterator::get_Temp()->pPrev);
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator ++(int)//Postfix 
{
	ConstReverseIterator old = *this;
	List<T>::BaseIterator::set_Temp(List<T>::BaseIterator::get_Temp()->pPrev);
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator --()//Prefix  
{
	BaseIterator::set_Temp(BaseIterator::get_Temp()->pNext);
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator  --(int)//Postfix 
{
	ConstReverseIterator old = *this;
	set_Temp(BaseIterator::get_Temp()->pNext);
	return old;
}
//--------------------------------------------------------------------------------------------------

//----------class Element---------------------------------------------------------------------------
template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor : \t" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor : \t" << this << endl;
#endif // DEBUG

}
//--------------------------------------------------------------------------------------------------

//------------class Queue---------------------------------------------------------------------------
template<typename T> void Queue<T>:: pop()
{
	List<T>::pop_front();
}
template<typename T> void Queue<T>:: push(T data)
{
	List<T>::push_and(data);
}
template<typename T>  typename T Queue<T>::peek()
{
	return List<T>::get_Tail()->get_Data();
}
//--------------------------------------------------------------------------------------------------