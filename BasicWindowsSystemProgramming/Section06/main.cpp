#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <strsafe.h>

namespace EnumeratingProcessesEx {
	int Main() {
		_wsetlocale(LC_ALL, L"korean");

		DWORD pidArray[512] = { 0 };
		DWORD cbNeeded = 0;
		DWORD nProcesses = 0;
		TCHAR szBuffer[MAX_PATH + _MAX_FNAME] = { 0 };
		UINT uCounter = 0;

		if (EnumProcesses(
			pidArray,
			sizeof(pidArray),
			&cbNeeded)) {
			nProcesses = cbNeeded / sizeof(DWORD);

			for (DWORD i = 0; i < nProcesses; i++) {
				HANDLE hProcess;
				DWORD pid = pidArray[i];

				hProcess = OpenProcess(
					PROCESS_QUERY_LIMITED_INFORMATION,
					FALSE,
					pid
				);

				if (hProcess != NULL) {
					SecureZeroMemory(szBuffer, MAX_PATH + _MAX_FNAME);

					if (GetModuleFileNameEx(
						hProcess,
						NULL,
						szBuffer,
						MAX_PATH + _MAX_FNAME
					) != NULL) {
						_tprintf(
							TEXT("[PID: %d] %s\n"),
							pid,
							szBuffer
						);
					}

					CloseHandle(hProcess);
				}
				else {
					_tprintf(
						TEXT("[PID: %d] Error code: %u\n"),
						pid,
						GetLastError()
					);
				}
			}
		}

		return 0;
	}
}

namespace ProcessSnapshotEx {
	int Main() {
		_wsetlocale(LC_ALL, L"korean");
		
		HANDLE hSnapshot = INVALID_HANDLE_VALUE;
		hSnapshot = CreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS,
			0
		);

		if (hSnapshot != INVALID_HANDLE_VALUE) {
			PROCESSENTRY32 pe32 = { sizeof(pe32) };

			BOOL bFlag = Process32First(
				hSnapshot,
				&pe32
			);

			while (bFlag) {
				_tprintf(
					TEXT("[PID: %d] %s\n"),
					pe32.th32ProcessID,
					pe32.szExeFile
				);

				bFlag = Process32Next(
					hSnapshot,
					&pe32
				);
			}

			CloseHandle(hSnapshot);
		}

		return 0;
	}
}

namespace SharedMemClientEx {
	int Main() {
		OutputDebugString(_T("Client - begin\n"));

		HANDLE hMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			128,
			_T("IPC_TEST_SHARED_MEMORY")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_TEST_SHARED_MEMORY already exists");

			hMap = OpenFileMapping(
				FILE_MAP_ALL_ACCESS,
				FALSE,
				_T("IPC_TEST_SHARED_MEMORY")
			);

			if (hMap == NULL) {
				_tprintf(
					_T("Failed to open file mapping obj [Error code: %u]\n"),
					GetLastError()
				);

				return 1;
			}
		}

		LPTCH pSharedMemory = (LPTCH)MapViewOfFile(
			hMap,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			128
		);

		if (pSharedMemory == NULL) {
			_tprintf(
				_T("Failed to get shared memory [Error code: %u]\n"),
				GetLastError()
			);

			CloseHandle(hMap);
			return 2;
		}

		HANDLE hEvent = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			_T("IPC_SHAREDMEM_ACCESS")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_ACCESS already exists");

			HANDLE hEvent = OpenEvent(
				EVENT_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_ACCESS")
			);

			if (hEvent == NULL) {
				_tprintf(
					_T("Failed to open event obj [Error code: %u]\n"),
					GetLastError()
				);

				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				return 3;
			}
		}

		HANDLE hEvtComplete = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			_T("IPC_SHAREDMEM_RECV_COMPLETE")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_RECV_COMPLETE already exists");

			hEvtComplete = OpenEvent(
				EVENT_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_RECV_COMPLETE")
			);

			if (hEvtComplete == NULL) {
				_tprintf(
					_T("Failed to open event complete obj [Error code: %u]\n"),
					GetLastError()
				);


				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				CloseHandle(hEvent);
				return 3;
			}
		}

		HANDLE hMutex = CreateMutex(
			NULL,
			FALSE,
			_T("IPC_SHAREDMEM_MUTEX")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_MUTEX already exists");

			hMutex = OpenMutex(
				MUTEX_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_MUTEX")
			);

			if (hMutex == NULL) {
				_tprintf(
					_T("Failed to open mutex obj [Error code: %u]\n"),
					GetLastError()
				);

				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				CloseHandle(hEvent);
				CloseHandle(hEvtComplete);
				return 4;
			}
		}

		OutputDebugString(_T("Waiting message from server...\n"));

		if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0) {
			if (WaitForSingleObject(hMutex, INFINITE) == WAIT_OBJECT_0)
				OutputDebugString(_T("MUTEX Lock\n"));
			else
				OutputDebugString(_T("MUTEX Error\n"));

			OutputDebugString(pSharedMemory);
			
			ReleaseMutex(hMutex);
			OutputDebugString(_T("MUTEX Unlock\n"));

			SetEvent(hEvtComplete);
			OutputDebugString(_T("Completetion  event for server\n"));
		}

		UnmapViewOfFile(pSharedMemory);
		CloseHandle(hMap);
		CloseHandle(hEvent);
		CloseHandle(hEvtComplete);
		CloseHandle(hMutex);

		OutputDebugString(_T("Client - end\n"));

		return 0;
	}
}

namespace SharedMemServerEx {
	int Main() {
		OutputDebugString(_T("Server - begin\n"));

		HANDLE hMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			128,
			_T("IPC_TEST_SHARED_MEMORY")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_TEST_SHARED_MEMORY already exists");

			hMap = OpenFileMapping(
				FILE_MAP_ALL_ACCESS,
				FALSE,
				_T("IPC_TEST_SHARED_MEMORY")
			);

			if (hMap == NULL) {
				_tprintf(
					_T("Failed to open file mapping obj [Error code: %u]\n"),
					GetLastError()
				);

				return 1;
			}
		}

		LPTCH pSharedMemory = (LPTCH)MapViewOfFile(
			hMap,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			128
		);

		if (pSharedMemory == NULL) {
			_tprintf(
				_T("Failed to get shared memory [Error code: %u]\n"),
				GetLastError()
			);

			CloseHandle(hMap);
			return 2;
		}

		HANDLE hEvent = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			_T("IPC_SHAREDMEM_ACCESS")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_ACCESS already exists");

			HANDLE hEvent = OpenEvent(
				EVENT_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_ACCESS")
			);

			if (hEvent == NULL) {
				_tprintf(
					_T("Failed to open event obj [Error code: %u]\n"),
					GetLastError()
				);

				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				return 3;
			}
		}

		HANDLE hEvtComplete = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			_T("IPC_SHAREDMEM_RECV_COMPLETE")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_RECV_COMPLETE already exists");

			hEvtComplete = OpenEvent(
				EVENT_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_RECV_COMPLETE")
			);

			if (hEvtComplete == NULL) {
				_tprintf(
					_T("Failed to open event complete obj [Error code: %u]\n"),
					GetLastError()
				);


				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				CloseHandle(hEvent);
				return 3;
			}
		}

		HANDLE hMutex = CreateMutex(
			NULL,
			FALSE,
			_T("IPC_SHAREDMEM_MUTEX")
		);

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			_putws(L"IPC_SHAREDMEM_MUTEX already exists");

			hMutex = OpenMutex(
				MUTEX_ALL_ACCESS,
				FALSE,
				_T("IPC_SHAREDMEM_MUTEX")
			);

			if (hMutex == NULL) {
				_tprintf(
					_T("Failed to open mutex obj [Error code: %u]\n"),
					GetLastError()
				);

				UnmapViewOfFile(pSharedMemory);
				CloseHandle(hMap);
				CloseHandle(hEvent);
				CloseHandle(hEvtComplete);
				return 4;
			}
		}

		if (WaitForSingleObject(hMutex, INFINITE) == WAIT_OBJECT_0)
			OutputDebugString(_T("MUTEX Lock\n"));
		else
			OutputDebugString(_T("MUTEX Error\n"));

		StringCbPrintf(
			pSharedMemory,
			128,
			_T("Hello, Shared memory!")
		);

		ReleaseMutex(hMutex);
		OutputDebugString(_T("MUTEX Unlock\n"));

		SetEvent(hEvent);
		OutputDebugString(_T("Message event set\n"));

		OutputDebugString(_T("Waiting recv event...\n"));
		if (WaitForSingleObject(hEvtComplete, INFINITE) == WAIT_OBJECT_0)
			OutputDebugString(_T("Received completion evenet from client\n"));

		UnmapViewOfFile(pSharedMemory);
		CloseHandle(hMap);
		CloseHandle(hEvent);
		CloseHandle(hEvtComplete);
		CloseHandle(hMutex);

		OutputDebugString(_T("Server - end\n"));

		return 0;
	}
}

int main() {
	UINT ret;

	ret = SharedMemClientEx::Main();

	_tprintf(_T("Return value: %u"), ret);

	return 0;
}