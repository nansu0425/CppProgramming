#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <process.h>

namespace EventEx {
	UINT WINAPI ThreadProc(LPVOID lpParameter) {
		HANDLE hEvent = lpParameter;
		std::cout << "ThreadProc - Begin" << std::endl;

		_getch();

		std::cout << "ThreadProc - Set hEvent" << std::endl;
		SetEvent(hEvent);

		std::cout << "ThreadProc - End" << std::endl;
		
		return 0;
	}

	int MainProc() {
		std::cout << "MainProc - Begin" << std::endl;

		HANDLE hEvent = CreateEvent(
			NULL,
			false,
			false,
			NULL
		);

		if (hEvent == NULL) {
			std::cout << "Fail to CreateEvent (Error code: "
				<< GetLastError() << ")" << std::endl;
			return 1;
		}

		UINT uThreadId;
		HANDLE hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			ThreadProc,
			hEvent,
			0,
			&uThreadId
		);

		if (hThread == NULL) {
			std::cout << "Fail to _beginthreadex (Error code: "
				<< GetLastError() << ")" << std::endl;
			return 2;
		}

		std::cout << "MainProc - Wait hEvent" << std::endl;
		if (WaitForSingleObject(hEvent, INFINITE)
			== WAIT_OBJECT_0) {
			std::cout << "MainProc - hEvent is signaled" << std::endl;
			CloseHandle(hEvent);
		}

		std::cout << "MainProc - Wait hThread" << std::endl;
		if (WaitForSingleObject(hThread, INFINITE)
			== WAIT_OBJECT_0) {
			std::cout << "MainProc - hThread is signaled" << std::endl;
		}
		CloseHandle(hThread);

		std::cout << "MainProc - End" << std::endl;

		return 0;
	}
}

namespace SemaphoreEx {
	HANDLE g_hSema;
	TCHAR g_StringList[10][64] = { 0 };

	UINT WINAPI ThreadProc(LPVOID lpParam) {
		int nIndex = (int)lpParam;

		while (true) {
			wsprintf(
				g_StringList[nIndex],
				TEXT("%d thread is waiting!"),
				nIndex
				);
			Sleep(500);

			DWORD dwResult = WaitForSingleObject(g_hSema, INFINITE);

			wsprintf(
				g_StringList[nIndex],
				TEXT("%d thread is selected!"),
				nIndex
			);
			Sleep(500);

			ReleaseSemaphore(g_hSema, 1, NULL);
		}
		
		return 0;
	}

	int MainProc() {
		g_hSema = CreateSemaphore(
			NULL,
			3,
			3,
			NULL
		);

		UINT nThreadId = 0;
		HANDLE hThread = NULL;

		for (int i = 0; i < 10; i++) {
			hThread = (HANDLE)_beginthreadex(
				NULL,
				0,
				ThreadProc,
				(LPVOID)i,
				0,
				&nThreadId
			);

			if (hThread)
				CloseHandle(hThread);
		}

		while (true) {
			system("cls");
			for (int i = 0; i < 10; i++)
				_putws(g_StringList[i]);

			Sleep(500);
		}

		CloseHandle(g_hSema);

		return 0;
	}
}

namespace AffinityEx {
	UINT WINAPI ThreadProc(LPVOID lpParameter) {
		int nTmp = 0;

		while (1) {
			++nTmp;
		}

		return 0;
	}

	int MainProc() {
		UINT nThreadId = 0;
		HANDLE hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			ThreadProc,
			NULL,
			0,
			&nThreadId
		);

		if (hThread == NULL) {
			std::cout << "Fail to _beginthreadex() [error code: "
				<< GetLastError() << "]" << std::endl;
			return 1;
		}

		for (int i = 0; i < 12; i++) {
			SetThreadAffinityMask(hThread, (DWORD_PTR)1 << i);
			Sleep(5000);
		}

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);

		return 0;
	}
}

int main() {
	// EventEx::MainProc();
	// SemaphoreEx::MainProc();
	AffinityEx::MainProc();

	return 0;
}