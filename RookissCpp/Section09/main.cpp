#include <iostream>

void Test2()
{

}

void Test1()
{
	int a = 0;
	Test2();
}

int main()
{
	int number = 10;

	Test1();

	return 0;
}