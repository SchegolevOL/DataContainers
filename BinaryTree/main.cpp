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
void print(Element* Root)
	{
		if (Root == nullptr)return;
		cout <<"<" << Root->Data<<">" << tab;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
		
	}
private:
	int minValue(Element* tmp)
	{	
		return tmp->pLeft == nullptr ? tmp->Data : minValue(tmp->pLeft);		
	}
	int maxValue(Element* tmp)
	{
		return tmp->pRight == nullptr ? tmp->Data : maxValue(tmp->pRight);
	}
	int size(Element* Root,int s)
	{
		
		if (Root == nullptr) return s;
		
		size(Root->pLeft,s);
		s = s + 1;
		size(Root->pRight,s);
		
		return s;

	}
public:
	int minValue()
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
		if (Root == nullptr) return -1;
		return minValue(this->Root);		
	}
	int maxValue()
	{
		/*if (Root == nullptr) return-1;
		int max = Root->Data;
		Element* tmp = Root->pRight;
		while (tmp)
		{
			max = tmp->Data;
			tmp = tmp->pRight;
		}*/
		if (Root == nullptr) return -1;
		return maxValue(this->Root);
	}
	int size()
	{
		return size(this->Root, 0);
	}





	int sum()
	{
		if (Root == nullptr) return 0;
		int sum = Root->Data;
		Element* tmp = Root->pLeft;
		while (tmp)
		{
			sum = sum + tmp->Data;
			tmp = tmp->pLeft;
		}
		tmp = Root->pRight;
		while (tmp)
		{
			sum = sum + tmp->Data;
			tmp = tmp->pRight;
		}
		return sum;	
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
		tree.insert((rand() % 100)+1, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << tree.minValue()<<endl;
	cout << tree.maxValue() << endl;
	cout << tree.size() << endl;



	return 0;
}
