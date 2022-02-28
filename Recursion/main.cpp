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


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int a = 5;
	cout << faktorial(a) << endl;
	int n = 2;
	cout << power(a, n) << endl;

	return 0;
}
