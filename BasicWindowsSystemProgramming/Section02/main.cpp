#include <iostream>
#include <Windows.h>
#include <process.h>

namespace CreateThreadEx {
	DWORD WINAPI ThreadProc(LPVOID lpParameter) {
		std::cout << "CreateThreadEx::ThreadProc() - Begin" << std::endl;
		std::cout << (const char*)lpParameter << std::endl;
		std::cout << "CreateThreadEx::ThreadProc() - End" << std::endl;

		return 0;
	}

	int MainProc() {
		std::cout << "CreateThreadEx::MainProc - Begin" << std::endl;

		DWORD dwThreadId = 0;
		HANDLE hThread = CreateThread(
			NULL,
			0,
			ThreadProc,
			(LPVOID)"PARAM",
			0,
			&dwThreadId
		);

		if (hThread == NULL) {
			std::cout << "Fail to create thread" << std::endl;
			return 1;
		}

		std::cout << "CreateThreadEx::MainProc - before WaitForSingleObject()"
			<< std::endl;

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);

		std::cout << "CreateThreadEx::MainProc - after WaitForSingleObject()\n"
			<< "CreateThreadEx::MainProc - End" << std::endl;

		return 0;
	}
}

namespace beginthreadexEx {
	UINT WINAPI ThreadProc(LPVOID lpParameter) {
		std::cout << "beginthreadexEx::ThreadProc() - Begin" << std::endl;
		std::cout << (const char*)lpParameter << std::endl;
		std::cout << "beginthreadexEx::ThreadProc() - End" << std::endl;

		return 0;
	}

	int MainProc() {
		std::cout << "beginthreadexEx::MainProc - Begin" << std::endl;
		
		UINT uThreadId;
		HANDLE hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			ThreadProc,
			(LPVOID)"PARAM",
			0,
			&uThreadId
		);

		if (hThread == NULL) {
			std::cout << "Fail to _beginthreadex()\n"
				<< "Error code: " << GetLastError() << std::endl;

			return 1;
		}

		std::cout << "beginthreadexEx::MainProc - Before WaitForSingleObject()" << std::endl;
		
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);

		std::cout << "beginthreadexEx::MainProc - After WaitForSingleObject()\n" 
			<< "beginthreadexEx::MainProc - End" << std::endl;

		return 0;
	}
}

namespace CtrlThreadEx {
	bool g_bFlag = false;
	
	UINT WINAPI ThreadProc(LPVOID lpParameter) {
		std::cout << "ThreadProc - Begin" << std::endl;

		g_bFlag = true;

		while (g_bFlag) {
			std::cout << "ThreadProc - Sleep 1s" << std::endl;
			Sleep(1000);
		}

		std::cout << "ThreadProc - End" << std::endl;

		return 0;
	}

	int MainProc() {
		std::cout << "MainProc - Begin" << std::endl;

		UINT uThreadId;
		HANDLE hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			ThreadProc,
			NULL,
			0,
			&uThreadId
		);

		if (hThread == NULL) {
			std::cout << "MainProc - Fail to _beginthreadex (error code: "
				<< GetLastError() << ")" << std::endl;
			
			return 1;
		}

		std::cout << "MainProc - Sleep 2s" << std::endl;
		Sleep(2000);

		std::cout << "MainProc - Call SuspendThread" << std::endl;
		SuspendThread(hThread);

		for (int i = 0; i < 3; i++) {
			std::cout << "MainProc - Call WaitForSingleObject 1s"
				<< std::endl;
			WaitForSingleObject(hThread, 1000);
		}

		std::cout << "MainProc - Call ResumeThread" << std::endl;
		ResumeThread(hThread);

		std::cout << "MainProc - Sleep 2s" << std::endl;
		Sleep(2000);

		g_bFlag = false;

		std::cout << "MainProc - Call WaitForSingleObject" << std::endl;
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);

		std::cout << "MainProc - End" << std::endl;

		return 0;
	}
}

namespace SleepRandomEx {
	LARGE_INTEGER freq;
	LARGE_INTEGER begin;
	LARGE_INTEGER end;
	__int64 elapsed;

	int MainProc() {
		QueryPerformanceFrequency(&freq);
		std::cout << "Frequency per sec: " << freq.QuadPart << std::endl;

		for (int i = 0; i < 5; i++) {
			QueryPerformanceCounter(&begin);
			Sleep(10);
			QueryPerformanceCounter(&end);
		
			elapsed = end.QuadPart - begin.QuadPart;

			std::cout << "실제로 흘러간 시간: "
				<< elapsed << std::endl;
			std::cout << "실제로 흘러간 시간(ms): "
				<< (double)elapsed / freq.QuadPart * 1000 << std::endl;
			std::cout << "실제로 흘러간 시간(micro): "
				<< (double)elapsed / freq.QuadPart * 1000 * 1000 << std::endl;
			std::cout << "랜덤 값(0~99): "
				<< elapsed % 100 << std::endl;
		}

		return 0;
	}
}

int main() {
	// CreateThreadEx::MainProc();
	// beginthreadexEx::MainProc();
	// CtrlThreadEx::MainProc();
	SleepRandomEx::MainProc();

	return 0;
}