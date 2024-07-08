#include <iostream>

#define SNAIL

#ifdef POINTER_REFERENCE
#define OUT

struct StartInfo {
	int hp;
	int attack;
	int defence;
};

StartInfo CreatePlayer();
void CreateMonster(OUT StartInfo& info);

int main() {
	StartInfo playerInfo = { 0 };
	StartInfo monsterInfo = { 0 };

	playerInfo = CreatePlayer();
	CreateMonster(OUT monsterInfo);

	return 0;
}

StartInfo CreatePlayer() {
	StartInfo info;

	info.attack = 30;
	info.defence = 10;
	info.hp = 100;

	return info;
}

void CreateMonster(OUT StartInfo& info) {
	info.attack = 20;
	info.defence = 5;
	info.hp = 80;
}
#endif // POINTER_REFERENCE

#ifdef ARRAY
void Test(char a[2]) {
	a[0] = 'x';
	a[3] = 'b';
}

int main() {
	const char* test1 = "Hello World";

	char test2[] = "Hello World";
	Test(test2);

	int arr[5] = { 0 };
	int(*ptrArr)[5] = &arr;

	std::cout << test2 << std::endl;

	return 0;
}
#endif // ARRAY

#ifdef LOTTO
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void Swap(char& a, char& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void BubbleSort(int* arr, int size) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
		}
	}
}

void SelectionSort(int* arr, int size) {
	int minIdx = 0;

	for (int i = 0; i < size - 1; i++) {
		minIdx = i;

		for (int j = i + 1; j < size; j++) {
			if (arr[minIdx] > arr[j])
				minIdx = j;
		}

		if (i < minIdx)
			Swap(arr[i], arr[minIdx]);
	}
}

void InsertionSort(int* arr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1])
				Swap(arr[j], arr[j - 1]);
			else
				break;
		}
	}
}

void InputLotto(int numbers[]) {
	for (int i = 0; i < 6; i++) {
		int num;
		bool inputFlag = false;

		std::cout << i + 1
			<< "번째 로또 번호를 골라주세요"
			<< std::endl;

		while (std::cin >> num) {
			if (0 < num && num < 46) {
				int j;

				for (j = 0; j < i; j++) {
					if (num == numbers[j]) {
						std::cout << "중복된 숫자입니다"
							<< std::endl;
						break;
					}
				}

				if (j == i) {
					numbers[i] = num;
					inputFlag = true;
					break;
				}
			}
			else
			{
				std::cout << "1~45 사이의 숫자를 입력하세요"
					<< std::endl;
			}
		}

		if (inputFlag == false) {
			std::cout << "잘못된 입력입니다"
				<< std::endl;
			return;
		}
	}

	InsertionSort(numbers, 6);
}

void GenerateLotto(int numbers[]) {
	srand((unsigned)time(0));

	for (int i = 0; i < 6; i++) {
		int randNum = rand() % 45 + 1;
		bool isSame = false;

		for (int j = 0; j < i; j++) {
			if (randNum == numbers[j]) {
				isSame = true;
				i--;
				break;
			}
		}

		if (isSame)
			continue;
		numbers[i] = randNum;
	}

	SelectionSort(numbers, 6);
}

int main() {
	int inputNums[6];
	InputLotto(inputNums);

	int lottoNums[6];
	GenerateLotto(lottoNums);

	return 0;
}
#endif // LOTTO

#ifdef MULTI_ARRAY
int main() {
	int apartment[2][5] = {
		{ 4, 2, 3, 4, 1 },
		{ 1, 1, 5, 2, 2 }
	};

	int row = sizeof(apartment) / sizeof(apartment[0]);
	int column = sizeof(apartment[0]) / sizeof(int);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			std::cout << apartment[i][j] << " ";
		}
		std::cout << std::endl;
	}

	int arr[10] = {
		1, 2, 3, 4, 5, 6, 7, 8
	};

	int* p = arr;

	std::cout << sizeof(arr) << std::endl;
	std::cout << sizeof(p) << std::endl;

	int arr2[2][2] = {
		{1, 2},
		{3, 4}
	};

	int** pp = (int**)arr2;
	p = *pp;

	int(*rowArr)[2] = arr2;
	std::cout << *(*(rowArr + 1) + 1) << std::endl;

	return 0;
}
#endif // MULTI_ARRAY

#ifdef WRONG_POINTER
int* TestPointer() {
	int a = 0x11111111;

	return &a;
}

void TestWrong(int* ptr) {
	int arr[10] = {};
	arr[9] = 0x22222222;

	*ptr = 0x33333333;
}

int main() {
	int* pointer = TestPointer();
	TestWrong(pointer);

	return 0;
}
#endif // WRONG_POINTER

#ifdef STRING
#pragma warning(disable: 4996)
#define POINTER

size_t Strlen(const char* str) {
	size_t len = 0;

	while (str[len] != '\0')
		len++;

	return len;
}

void Strcpy(char* dest, const char* source) {
#ifdef INDEX
	int idx = 0;

	while (source[idx] != '\0') {
		dest[idx] = source[idx];
		idx++;
	}

	dest[idx] = '\0';
#endif // INDEX

#ifdef POINTER
	while (*source != '\0')
		*dest++ = *source++;

	*dest = '\0';
#endif // POINTER
}

void Strcat(char* dest, const char* src) {
	while (*dest != '\0')
		dest++;

	while (*src != '\0')
		*dest++ = *src++;

	*dest = '\0';
}

int Strcmp(const char* str1, const char* str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		int diff = *(str1++) - *(str2++);

		if (diff != 0)
			return diff;
	}

	return *str1 - *str2;
}

void Strrevrs(char* str) {
#ifdef INDEX
	auto len = Strlen(str);

	for (int i = 0; i < len / 2; i++) {
		char tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
#endif // INDEX

#ifdef POINTER
	int len = Strlen(str);
	char* front = str;
	char* rear = str + len - 1;

	while (front < rear) {
		char tmp = *front;
		*front = *rear;
		*rear = tmp;

		front++;
		rear--;
	}
#endif // POINTER
}

int main() {
	const size_t bufSize = 100;

	char str[bufSize] = "Hello World";

	auto len = Strlen(str);
	std::cout << len << std::endl;

	char dest[bufSize];
	Strcpy(dest, str);
	std::cout << dest << std::endl;

	char cat[bufSize] = ", I'm Jun!";
	Strcat(str, cat);
	std::cout << str << std::endl;

	char src[] = "aaaa";
	char dst[] = "aa";
	std::cout << Strcmp(src, dst) << std::endl;

	Strrevrs(str);
	std::cout << str << std::endl;

	return 0;
}
#endif // STRING

#ifdef SNAIL
#define BUF_SIZE 100
#define FUNCTION

#ifdef INDEX
int main() {
	int arr[BUF_SIZE][BUF_SIZE];
	int n, i, cnt;

	std::cin >> n;
	i = 0;
	cnt = 1;

	while (i < n / 2) {
		for (int c = i; c < n - i - 1; c++)
			arr[i][c] = cnt++;
		for (int r = i; r < n - i - 1; r++)
			arr[r][n - 1 - i] = cnt++;
		for (int c = n - 1 - i; c > i; c--)
			arr[n - 1 - i][c] = cnt++;
		for (int r = n - 1 - i; r > i; r--)
			arr[r][i] = cnt++;

		i++;
	}

	if (n % 2 == 1)
		arr[n / 2][n / 2] = cnt;

	int quotient = cnt;
	int digit = 0;

	do {
		quotient /= 10;
		digit++;
	} while (quotient != 0);

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			std::cout.width(digit);
			std::cout.fill('0');
			std::cout << arr[r][c];
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
#endif // INDEX

#ifdef FUNCTION
enum DIRECTION {
	RIGHT,
	DOWN,
	LEFT,
	UP
};
DIRECTION dir = RIGHT;

int rowDiff[] = { 0, 1, 0, -1 };
int colDiff[] = { 1, 0, -1, 0 };

struct Pos {
	int row;
	int	col;
};
Pos curPos = {};
Pos nextPos = {};

int board[BUF_SIZE][BUF_SIZE] = { 1 };
int cnt = 1;

bool isValidDir(const int& refSize) {
	nextPos.row = curPos.row + rowDiff[dir];
	nextPos.col = curPos.col + colDiff[dir];

	if (nextPos.row < 0 || refSize <= nextPos.row ||
		nextPos.col < 0 || refSize <= nextPos.col ||
		board[nextPos.row][nextPos.col] != 0) return false;

	return true;
}

void movePos() {
	curPos = nextPos;
	board[curPos.row][curPos.col] = ++cnt;
}

void changeDir() {
	dir = (DIRECTION)((dir + 1) % 4);
}

void printBoard(const int& refSize) {
	int digit = 1;
	int quotient = cnt;
	
	while (quotient /= 10)
		digit++;

	for (int r = 0; r < refSize; r++) {
		for (int c = 0; c < refSize; c++) {
			std::cout.width(digit);
			std::cout.fill('0');

			std::cout << board[r][c];
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

int main() 
{
	int size = 0;
	std::cin >> size;

	while (true) {
		if (isValidDir(size)) {
			movePos();
		}
		else {
			if (cnt == size * size)
				break;
			changeDir();
		}
	}

	printBoard(size);

	return 0;
}
#endif // FUNCTION

#endif // SNAIL
