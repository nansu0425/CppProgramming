#include <iostream>

namespace FunctionEx {
	int MultiplyBy(int first, int second)
	{
		int result = first * second;

		return result;
	}

	int Main() {
		int a = 3;
		int b = 5;
		int result = MultiplyBy(b, a);
		
		return 0;
	}
}

namespace DefaultFunctionEx {
	void SetPlayerInfo(int hp, int mp, int attack = 20, int id = 5) {
		return;
	}
	
	int Main() {
		SetPlayerInfo(100, 50, 40);

		return 0;
	}
}

namespace StackOverflowEx {
	int CalFactorial(int num) {
		if (num == 1)
			return 1;

		return num * CalFactorial(num - 1);
	}
	
	int Main() {
		std::cout << CalFactorial(1000000);

		return 0;
	}
}

int main() {
	

	return 0;
}