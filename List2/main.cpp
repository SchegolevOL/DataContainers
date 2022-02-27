#include"List.h"
#include"List.cpp"


//#define BASE_CHEK
//#define LIST2
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#ifdef BASE_CHEK

	List<double> list;
	list.push_front(10.5);
	list.push_front(15.5);
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
#ifdef LIST2
	List<int> list3 = { 3, 5, 8, 13, 21 };
	list3.print();

	for (int i : list3)cout << i << tab;
	cout << endl;

	for (List<int> ::ConstReverseIterator it = list3.crbegin(); it; ++it)
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
#endif // LIST2

	Queue<int> q;
	for (size_t i = 0; i < 10; i++)
	{		
		q.push(i);
		q.peek();
	}
	for (size_t i = 0; i < 10; i++)
	{
		q.peek();
		q.pop();
	}




	
	return 0;
}
