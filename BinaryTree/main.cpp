#include <iostream>
#include <Windows.h>
#include<time.h>


#define tab "\t"

using namespace std;

#define DEBUG

class Tree
{
protected:

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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}

		friend class Tree;
		friend class UniqueTree;
	}*Root;



public:

	Element* getRoot()const
	{
		return Root;
	}
	//----------------
	Tree()
	{
		this->Root = nullptr;
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG
	}
	//-----------------
	Tree(const std::initializer_list<int>& il) : Tree()
	{
#ifdef DEBUG
		cout << "TIConstructor:\t" << this << endl;
#endif // DEBUG
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}

	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG
	}

	~Tree()
	{
		clear();
#ifdef DEBUG		
		cout << "TDConstructor:\t" << this << endl;
#endif // DEBUG
	}
private:
	//-------------------------------------------------------------------------
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
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (size(Root->pLeft)>size(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight),Root->pRight);
				}

			}
		}
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
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
		return tmp->pLeft ? minValue(tmp->pLeft) : tmp->Data;
	}
	int maxValue(Element* tmp)const
	{
		return tmp->pRight ? maxValue(tmp->pRight) : tmp->Data;
	}
	int size(Element* tmp)
	{
		return tmp ? size(tmp->pLeft) + size(tmp->pRight) + 1 : 0;
	}
	int sum(Element* tmp)const
	{
		/*if (tmp == nullptr) return s;
		s = sum(tmp->pLeft, s) + tmp->Data;
		s = sum(tmp->pRight, s);
		return s;*/

		return tmp ? sum(tmp->pLeft) + sum(tmp->pRight) + tmp->Data : 0;
	}
	double avg(Element* tmp)
	{
		return (double)(sum(tmp)) / size(tmp);
	}

	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}

	
	//----------------------------------------------------------
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
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	int size()
	{
		return size(this->Root);
	}
	int sum()
	{
		return sum(this->Root);
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
class UniqueTree : public Tree
{
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
		else  if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};
//#define BASE_CHEK
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	setlocale(LC_ALL, "");

#ifdef BASE_CHEK
	int n;
	cout << "Enter size tree: "; cin >> n;
	UniqueTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert((rand() % 100) + 1);
	}
	tree.print();
	cout << endl;
	cout << "Min element : " << tree.minValue() << endl;
	cout << "Max element : " << tree.maxValue() << endl;
	cout << "Size Tree : " << tree.size() << endl;
	cout << "Sum element Tree : " << tree.sum() << endl;
	cout << "AVG element Tree : " << tree.avg() << endl;
#endif // BASE_CHEK

	Tree tree = { 50,25,16,32,64,80 };
	//tree.print();
	Tree tree2 = tree;
	tree2.print();
	tree2.erase(80);
	tree2.print();

	return 0;
}
