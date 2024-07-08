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
			"가위",
			"바위",
			"보"
		};

		srand((unsigned)time(nullptr));

		while (true)
		{
			std::cout << "가위(1) 바위(2) 보(3) 골라주세요!" << std::endl;

			if (uRound > 0)
				std::cout << "> 현재 승률: " << uWinRate << "%" << std::endl;
			else
				std::cout << "> 현재 승률: 없음" << std::endl;
			
			if (std::cin >> uUserNum) {
				uComNum = (rand() % 3) + 1;

				if (uUserNum == 4)
					break;
				if ((uUserNum - uComNum) == 1 || (uComNum - uUserNum) == 2) {
					std::cout << strRpsArr[uUserNum] << "(님) vs "
						<< strRpsArr[uComNum] << "(컴퓨터) 이겼습니다!"
						<< std::endl << std::endl;

					uWinRate = (++uWinCnt * 100) / ++uRound;
				} else if (0 < uUserNum && uUserNum < 4) {
					std::cout << strRpsArr[uUserNum] << "(님) vs "
						<< strRpsArr[uComNum];

					if (uUserNum == uComNum)
						std::cout << "(컴퓨터) 비겼습니다!";
					else
						std::cout << "(컴퓨터) 졌습니다!";

					std::cout << std::endl << std::endl;

					uWinRate = (uWinCnt * 100) / ++uRound;
				} else {
					std::cout << "1~3 중 하나를 고르거나 종료하시려면 4를 누르세요."
						<< std::endl << std::endl;
				}
			}
			else {
				std::cout << std::endl << "입력이 잘못됐습니다.";
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