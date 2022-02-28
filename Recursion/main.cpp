#include <iostream>
#include <Windows.h>

using namespace std;
//1. �������� ����������� ������� int factorial(int n), ������� ��������� �����, � ���������� ��������� ����� �����;
long long faktorial(int value)
{
	return value < 1 ? 1 : faktorial(value - 1) * value;
}
//2. �������� ���������� ������� double power(double a, int n), ������� �������� ��������� ����� � ��������� �������;
double power(double a, int n)
{
	return n < 1 ? 1 : power(a, n - 1) * a;
}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "������" << endl;
		return;
	}
	
	elevator(floor-1);
	cout << "�� �� " << floor << " �����" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*int a = 5;
	cout << faktorial(a) << endl;
	int n = 2;
	cout << power(a, n) << endl;*/

	int floor; cin >> floor;
	elevator(floor);


	return 0;
}
