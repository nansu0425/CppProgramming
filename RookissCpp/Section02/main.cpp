#include <iostream>
#include <locale>

int main() {
#pragma region 04
	/*
	wchar_t utf16le = L'¾È';
	char16_t utf16 = u'¾È';

	std::wcout.imbue(std::locale("kor"));
	std::wcout << utf16le << std::endl;
	*/

	/*
	char str[] = { 'H', 'e', 'l','l','o', '\0'};

	std::cout << str << std::endl;
	*/
#pragma endregion 04

#pragma region 8
	char a = 499;

	std::cout << std::dec << a << std::endl;
#pragma endregion 8 

	return 0;
}