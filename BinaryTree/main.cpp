#include <iostream>
#include <Windows.h>

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
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}



};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (size_t i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;






	return 0;
}
