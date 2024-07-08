#include <iostream>

namespace StarEx {
	int MainProc() {
		int n;

		std::cin >> n;

		for (int i = n; i > 0; i--) {
			for (int j = 0; j < i; j++)
				std::cout << "*";
			std::cout << std::endl;
		}

		return 0;
	}
}

namespace RockPaperScissors {
	enum ENUM_RPS {
		SCISSOR = 1,
		ROCK,
		PAPER
	};

	int Main() {
		int uWinRate{ 0 }, uRound{ 0 }, uWinCnt{ 0 },
			uUserNum{ 0 }, uComNum{ 0 };
		const char* strRpsArr[4] = {
			"",
			"����",
			"����",
			"��"
		};

		srand((unsigned)time(nullptr));

		while (true)
		{
			std::cout << "����(1) ����(2) ��(3) ����ּ���!" << std::endl;

			if (uRound > 0)
				std::cout << "> ���� �·�: " << uWinRate << "%" << std::endl;
			else
				std::cout << "> ���� �·�: ����" << std::endl;
			
			if (std::cin >> uUserNum) {
				uComNum = (rand() % 3) + 1;

				if (uUserNum == 4)
					break;
				if ((uUserNum - uComNum) == 1 || (uComNum - uUserNum) == 2) {
					std::cout << strRpsArr[uUserNum] << "(��) vs "
						<< strRpsArr[uComNum] << "(��ǻ��) �̰���ϴ�!"
						<< std::endl << std::endl;

					uWinRate = (++uWinCnt * 100) / ++uRound;
				} else if (0 < uUserNum && uUserNum < 4) {
					std::cout << strRpsArr[uUserNum] << "(��) vs "
						<< strRpsArr[uComNum];

					if (uUserNum == uComNum)
						std::cout << "(��ǻ��) �����ϴ�!";
					else
						std::cout << "(��ǻ��) �����ϴ�!";

					std::cout << std::endl << std::endl;

					uWinRate = (uWinCnt * 100) / ++uRound;
				} else {
					std::cout << "1~3 �� �ϳ��� ���ų� �����Ͻ÷��� 4�� ��������."
						<< std::endl << std::endl;
				}
			}
			else {
				std::cout << std::endl << "�Է��� �߸��ƽ��ϴ�.";
				return 1;
			}
		}

		return 0;
	}
}

int main() {
	// StarEx::MainProc();
	RockPaperScissors::Main();

	return 0;
}