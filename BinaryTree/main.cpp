#include <iostream>
#include <Windows.h>
#include<time.h>


#define tab "\t"

using namespace std;

#define DEBUG

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
		: Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "DConstructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
	}*Root;



public:

	Element* getRoot()const
	{
		return Root;
	}

	Tree()
	{
		this->Root = nullptr;
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Tree()
	{
#ifdef DEBUG
		cout << "TDConstructor:\t" << this << endl;
#endif // DEBUG
	}
private:
	void insert(int Data, Element* Root)//Рекурсивное добавление элемента в бинарное дерево
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
		
	}

	int minValue(Element* tmp)const
	{	
		return tmp->pLeft ? minValue(tmp->pLeft) : tmp->Data ;		
	}
	int maxValue(Element* tmp)const
	{
		return tmp->pRight ? maxValue(tmp->pRight) : tmp->Data;
	}
	int size(Element* tmp,int s)
	{		
		if (tmp == nullptr) return s;
		s = size(tmp->pLeft, s) + 1;
		s = size(tmp->pRight, s);		
		return s;
	}
	int sum(Element* tmp, int s)
	{
		if (tmp == nullptr) return s;
		s = sum(tmp->pLeft, s) + tmp->Data;
		s = sum(tmp->pRight, s);
		return s;
	}
	double avg(Element* tmp)
	{
		return (double)(sum(tmp, 0)) / size(tmp, 0);
	}
	void erase(int Data, Element* tmp)
	{

	}
public:
	int minValue()const
	{
		/*if (Root == nullptr) return-1;
		int min = Root->Data;
		Element* tmp=Root->pLeft;
		while (tmp)
		{
			min = tmp->Data;
			tmp = tmp->pLeft;
		}
		return min;*/
		if (Root == nullptr) return 0;
		return minValue(this->Root);		
	}
	int maxValue()const
	{
		/*if (Root == nullptr) return-1;
		int max = Root->Data;
		Element* tmp = Root->pRight;
		while (tmp)
		{
			max = tmp->Data;
			tmp = tmp->pRight;
		}*/
		if (Root == nullptr) return 0;
		return maxValue(this->Root);
	}
	void print()const
	{
		print(this->Root);
	}
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	int size()
	{
		return size(this->Root, 0);
	}
	int sum()
	{
		return sum(this->Root, 0);
	}
	double avg()
	{
		return avg(this->Root);
	}
	void erase(int Data)
	{
		erase(Data, this->Root);
	}



	
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));



	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (size_t i = 0; i < n; i++)
	{
		tree.insert((rand() % 100)+1);
	}
	tree.print();
	cout << endl;
	cout << tree.minValue()<<endl;
	cout << tree.maxValue() << endl;
	cout << tree.size() << endl;
	cout << tree.sum() << endl;
	cout << tree.avg() << endl;

	return 0;
}
