#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <process.h>

namespace FileInfoEx 
{
	void LoadDiskInfo(const TCHAR* pszPath)
	{
		TCHAR szVolName[MAX_PATH] = { 0 };
		TCHAR szFileSys[MAX_PATH] = { 0 };
		TCHAR szRoot[MAX_PATH] = { 0 };
		DWORD dwSerialNum = 0, dwMaxComLen = 0, dwSysFlag = 0;

		memcpy(szRoot, pszPath, sizeof(TCHAR) * 3);

		GetVolumeInformation(
			szRoot,
			szVolName,
			MAX_PATH,
			&dwSerialNum,
			&dwMaxComLen,
			&dwSysFlag,
			szFileSys,
			MAX_PATH
		);

		wprintf(
			TEXT("Volume name: %s, File System: %s\n"),
			szVolName, szFileSys
		);

		ULARGE_INTEGER llAvailableSpace = { 0 };
		ULARGE_INTEGER llTotalSpace = { 0 };
		ULARGE_INTEGER llFreeSpace = { 0 };

		if (GetDiskFreeSpaceEx(
			szRoot,
			&llAvailableSpace,
			&llTotalSpace,
			&llFreeSpace
		))
		{
			wprintf(
				TEXT("Disk free space: %I64u/%I64u GB\n"),
				llFreeSpace.QuadPart / (1024 * 1024 * 1024),
				llTotalSpace.QuadPart / (1024 * 1024 * 1024)
			);
		}
	}

	void LoadFileList(const TCHAR* pszPath)
	{
		TCHAR szPath[MAX_PATH] = { 0 };
		wsprintf(szPath, TEXT("%s\\*.*"), pszPath);

		WIN32_FIND_DATA FindData;
		BOOL bResult = TRUE;
		ZeroMemory(&FindData, sizeof(WIN32_FIND_DATA));

		HANDLE hFirstFile = FindFirstFile(
			szPath,
			&FindData
		);

		while (bResult)
		{
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				wprintf(TEXT("[DIR] %s\n"), FindData.cFileName);
			else
				wprintf(TEXT("%s\n"), FindData.cFileName);

			bResult = FindNextFile(hFirstFile, &FindData);
		}
	}

	int Main() {
		_wsetlocale(LC_ALL, TEXT("korean"));

		LoadDiskInfo(TEXT("C:\\"));
		LoadFileList(TEXT("C:\\"));

		TCHAR szCurDir[MAX_PATH] = { 0 };

		GetCurrentDirectory(MAX_PATH, szCurDir);
		wprintf(TEXT("Current Directory: %s\n"), szCurDir);

		return 0;
	}
}

namespace FileCopyEx {
	
	int Main() {
		_wsetlocale(LC_ALL, TEXT("korean"));

		HANDLE hFileSource = NULL, hFileTarget = NULL;

		hFileSource = CreateFile
		(
			TEXT("C:\\TEST\\videos.zip"),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileSource == INVALID_HANDLE_VALUE)
		{
			wprintf
			(
				TEXT("Failed to open source file [Error code: %u]\n"), 
				GetLastError()
			);

			CloseHandle(hFileSource);
			return 1;
		}

		hFileTarget = CreateFile
		(
			TEXT("C:\\TEST\\videos-copy.zip"),
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileTarget == INVALID_HANDLE_VALUE)
		{
			wprintf
			(
				TEXT("Failed to open target file [Error code: %u]\n"),
				GetLastError()
			);

			CloseHandle(hFileTarget);
			return 2;
		}

		LARGE_INTEGER llFileSize = { 0 };
		LONGLONG llTotalReadSize = 0;
		DWORD dwReadSize = 0, dwWriteSize = 0;
		BOOL bResult = FALSE;
		BYTE byBuffer[65536];

		if (!GetFileSizeEx(hFileSource, &llFileSize))
		{
			wprintf(TEXT("원본 파일의 크기를 알 수 없습니다.\n"));
			
			CloseHandle(hFileSource);
			CloseHandle(hFileTarget);
			return 3;
		}

		for (LONGLONG i = 0; i < llFileSize.QuadPart; i += dwReadSize)
		{
			SecureZeroMemory(byBuffer, 65536);

			bResult = ReadFile
			(
				hFileSource,
				byBuffer,
				65536,
				&dwReadSize,
				NULL
			);

			if (!bResult)
			{
				wprintf
				(
					TEXT("Failed to read source file [Error Code: %u]\n"), 
					GetLastError()
				);

				CloseHandle(hFileSource);
				CloseHandle(hFileTarget);
				return 4;
			}

			llTotalReadSize += dwReadSize;
			wprintf
			(
				TEXT("%I64d%%\n"),
				llTotalReadSize * 100 / llFileSize.QuadPart
			);	

			if (!WriteFile
			(
				hFileTarget,
				byBuffer,
				dwReadSize,
				&dwWriteSize,
				NULL
			) || dwReadSize != dwWriteSize
			)
			{
				wprintf(
					TEXT("Failed to write target file [Error Code: %u]\n"),
					GetLastError()
				);

				CloseHandle(hFileSource);
				CloseHandle(hFileTarget);
				return 5;
			}
		}

		_putws(TEXT("File I/O Complete!\n"));
		CloseHandle(hFileSource);
		CloseHandle(hFileTarget);

		return 0;
	}
}

namespace OverlappedEventEx {
	int Main() {
		_wsetlocale(LC_ALL, L"korea");

		HANDLE hFile = CreateFile(
			TEXT("TestFile.txt"),
			GENERIC_WRITE,
			0,
			nullptr,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL
		);

		DWORD dwWrite;
		OVERLAPPED aOL[3] = { 0 };
		HANDLE aEvt[3] = { 0 };

		for (int i = 0; i < 3; i++) {
			aEvt[i] = CreateEvent(
				NULL,
				FALSE,
				FALSE,
				NULL
			);
			
			aOL[i].hEvent = aEvt[i];
		}

		aOL[0].Offset = 0;
		aOL[1].Offset = 50 * 1024 * 1024;
		aOL[2].Offset = 16;

		for (int i = 0; i < 3; i++)
		{
			printf("%d번째 중첩된 쓰기 시도\n", i);

			WriteFile(
				hFile,
				"0123456789",
				10,
				&dwWrite,
				&aOL[i]
			);
			
			DWORD dwErrCode = GetLastError();
			if (dwErrCode != ERROR_IO_PENDING)
			{
				printf(
					"Failed to write file [Error code: %u, Overlapped index: %u]",
					dwErrCode,
					i
				);

				return 1;
			}
		}

		DWORD dwResult = 0;

		for (int i = 0; i < 3; i++)
		{
			dwResult = WaitForMultipleObjects(
				3,
				aEvt,
				FALSE,
				INFINITE
			);

			printf("-> %d번째 쓰기 완료\n", dwResult - WAIT_OBJECT_0);
		}

		return 0;
	}
}

namespace OverlappedCallbackEx {
	VOID CALLBACK FileIoComplete(
		DWORD dwError,
		DWORD dwTransfered,
		LPOVERLAPPED pOL)
	{
		printf("FileIoComplete Callback - [%d 바이트] 쓰기 완료 - %s\n",
			dwTransfered, (char*)pOL->hEvent);

		Sleep(3000);

		delete[] pOL->hEvent;
		delete pOL;
		puts("FileIoComplete Callback - 종료");
	}

	UINT WINAPI IoThread(LPVOID lpParameter) {
		char* pszBuffer = new char[16];
		SecureZeroMemory(pszBuffer, sizeof(char) * 16);
		strcpy_s(pszBuffer, sizeof(char) * 16, "Hello IOCP");

		LPOVERLAPPED pOverlapped = NULL;
		pOverlapped = new OVERLAPPED;
		SecureZeroMemory(pOverlapped, sizeof(OVERLAPPED));

		pOverlapped->Offset = 512 * 1024 * 1024;
		pOverlapped->hEvent = pszBuffer;

		puts("IoThread - 중첩된 쓰기 시도");
		
		WriteFileEx(
			(HANDLE)lpParameter,
			pszBuffer,
			sizeof(char) * 16,
			pOverlapped,
			FileIoComplete
		);

		if (SleepEx(INFINITE, TRUE) == WAIT_IO_COMPLETION)
			puts("IoThread - SleepEx == WAIT_IO_COMPLETION");
		
		puts("IoThread - 중첩된 쓰기 완료");

		return 0;
	}

	int Main() {
		HANDLE hFile = CreateFile(
			TEXT("TestFile.txt"),
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL
		);

		HANDLE hThread = NULL;
		UINT dwThreadId = 0;

		hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			IoThread,
			hFile,
			0,
			&dwThreadId
		);

		if (hThread == NULL)
		{
			printf("Failed to create thread [Error Code: %u]",
				GetLastError());

			return 1;
		}

		WaitForSingleObject(hThread, INFINITE);


		return 0;
	}
}

namespace FileMappingWriteEx {
	int Main() {
		HANDLE hFile = CreateFile(
			TEXT("C:\\TEST\\MYFILE.txt"),
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		SetFilePointer(
			hFile,
			128 * 1024,
			NULL,
			FILE_BEGIN
		);

		HANDLE hMap = CreateFileMapping(
			hFile,
			NULL,
			PAGE_READWRITE,
			0,
			128 * 1024,
			NULL
		);

		if (hMap == NULL) {
			printf("Failed to create file mapping [Error code: %u]\n",
				GetLastError());

			return 1;
		}

		char* pszMemory = (char*)MapViewOfFile(
			hMap,
			FILE_MAP_ALL_ACCESS,
			0,
			64 * 1024,
			100
		);

		if (pszMemory == NULL) {
			printf("Failed to map view of file [Error code: %u]\n",
				GetLastError());

			CloseHandle(hMap);
			return 2;
		}

		SecureZeroMemory(pszMemory, 100);

		strcpy_s(
			pszMemory,
			27,
			"Hello, Memory Mapped file!"
		);
		
		FlushViewOfFile(pszMemory, 100);
		FlushFileBuffers(hFile);
		
		UnmapViewOfFile(pszMemory);
		CloseHandle(hMap);

		return 0;
	}
}

namespace FileMappingCopyEx {
	int Main() {
		HANDLE hFileSource = NULL, hFileTarget = NULL;

		hFileSource = CreateFile(
			TEXT("C:\\Test\\videos.zip"),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileSource == INVALID_HANDLE_VALUE) {
			printf(
				"Failed to open source file [Error code: %u]\n",
				GetLastError()
			);

			return 1;
		}

		hFileTarget = CreateFile(
			TEXT("C:\\Test\\videos copy.zip"),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileTarget == INVALID_HANDLE_VALUE) {
			printf(
				"Failed to create target file [Error code: %u]\n",
				GetLastError()
			);

			return 2;
		}

		LARGE_INTEGER llFileSize = { 0 };

		if (!GetFileSizeEx(
			hFileSource,
			&llFileSize
		)) {
			printf(
				"Failed to get source file size [Error code: %u]\n",
				GetLastError()
			);

			return 3;
		}

		if (!SetFilePointerEx(
			hFileTarget,
			llFileSize,
			NULL,
			FILE_BEGIN
		)) {
			printf(
				"Failed to set file pointer of target [Error code: %u]\n",
				GetLastError()
			);

			return 4;
		}

		HANDLE hMapSource = NULL, hMapTarget = NULL;

		hMapSource = CreateFileMapping(
			hFileSource,
			NULL,
			PAGE_READONLY,
			llFileSize.HighPart,
			llFileSize.LowPart,
			NULL
		);

		if (!hMapSource) {
			printf(
				"Failed to create file mapping of source [Error code: %u]\n",
				GetLastError()
			);

			return 5;
		}

		hMapTarget = CreateFileMapping(
			hFileTarget,
			NULL,
			PAGE_READWRITE,
			llFileSize.HighPart,
			llFileSize.LowPart,
			NULL
		);

		if (!hMapTarget) {
			printf(
				"Failed to create file mapping of target [Error code: %u]\n",
				GetLastError()
			);

			return 6;
		}

		char* pszSource = (char*)MapViewOfFile(
			hMapSource,
			FILE_MAP_READ,
			0,
			0,
			llFileSize.QuadPart
		);

		if (!pszSource) {
			printf(
				"Failed to map view file of source [Error code: %u]\n",
				GetLastError()
			);

			return 7;
		}

		char* pszTarget = (char*)MapViewOfFile(
			hMapTarget,
			FILE_MAP_WRITE,
			0,
			0,
			llFileSize.QuadPart
		);

		if (!pszTarget) {
			printf(
				"Failed to map view file of target [Error code: %u]\n",
				GetLastError()
			);

			return 8;
		}
		
		if (!memcpy_s(
			pszTarget,
			llFileSize.QuadPart,
			pszSource,
			llFileSize.QuadPart
		)) printf("File copy was successful!\n");
		

		UnmapViewOfFile(pszSource);
		UnmapViewOfFile(pszTarget);
		CloseHandle(hMapSource);
		CloseHandle(hFileSource);
		CloseHandle(hMapTarget);
		CloseHandle(hFileTarget);

		return 0;
	}
}

namespace AsyncEventFileCopyEx {
	void CloseAll(char* pszMem, HANDLE hMap, HANDLE hSrc, HANDLE hDst)
	{
		if (pszMem)
			UnmapViewOfFile(pszMem);
		if (hMap)
			CloseHandle(hMap);
		if (hSrc)
			CloseHandle(hSrc);
		if (hDst)
			CloseHandle(hDst);
	}

	int Main() {
		_wsetlocale(LC_ALL, L"korean");

		HANDLE hFileSource = NULL, hFileTarget = NULL;
		LARGE_INTEGER llFileSize = { 0 };
		HANDLE hMap = NULL;
		char* pszMemory = NULL;

		hFileSource = CreateFile(
			TEXT("C:\\TEST\\videos.zip"),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileSource == INVALID_HANDLE_VALUE)
		{
			wprintf(
				L"Failed to open source file [Error Code: %u]",
				GetLastError()
			);

			return 1;
		}

		if (!GetFileSizeEx(hFileSource, &llFileSize))
		{
			wprintf(
				L"Failed to open get file size [Error Code: %u]",
				GetLastError()
			);

			CloseAll(NULL, NULL, hFileSource, NULL);
			return 2;
		}

		hMap = CreateFileMapping(
			hFileSource,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL
		);

		if (hMap == NULL)
		{
			wprintf(
				L"Failed to open create file mapping obj [Error Code: %u]",
				GetLastError()
			);

			CloseAll(NULL, hMap, hFileSource, NULL);
			return 3;
		}

		pszMemory = (char*)MapViewOfFile(
			hMap,
			FILE_MAP_READ,
			0,
			0,
			(DWORD)llFileSize.QuadPart
		);

		if (pszMemory == NULL)
		{
			wprintf(
				L"Failed to get mapped view [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, NULL);
			return 3;
		}

		DeleteFile(
			TEXT("C:\\TEST\\videos copy.zip")
		);

		hFileTarget = CreateFile(
			TEXT("C:\\TEST\\videos copy.zip"),
			GENERIC_ALL,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL
		);

		if (hFileTarget == INVALID_HANDLE_VALUE) {
			wprintf(
				L"Failed to create target file [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, NULL);
			return 4;
		}

		LPOVERLAPPED pOverLapped = (LPOVERLAPPED)malloc(sizeof(OVERLAPPED));

		if (!pOverLapped) {
			wprintf(
				L"Failed to allocate overlapped struct [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 5;
		}

		pOverLapped->OffsetHigh = 0;
		pOverLapped->Offset = 0;
		pOverLapped->hEvent = CreateEvent(
			NULL,
			FALSE,
			FALSE,
			NULL
		);

		if (pOverLapped->hEvent == NULL) {
			wprintf(
				L"Failed to create event [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 6;
		}

		DWORD dWritten = 0;

		WriteFile(
			hFileTarget,
			pszMemory,
			llFileSize.LowPart,
			&dWritten,
			pOverLapped
		);

		if (GetLastError() != ERROR_IO_PENDING) {
			wprintf(
				L"Failed to write file [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 7;
		}

		if (WaitForSingleObject(
			pOverLapped->hEvent,
			INFINITE
		) == WAIT_OBJECT_0) {
			_putws(L"Completed writing file");
		}

		CloseAll(pszMemory, hMap, hFileSource, hFileTarget);

		CloseHandle(pOverLapped->hEvent);
		free(pOverLapped);

		return 0;
	}
}

namespace AsyncCallbackFileCopyEx {
	typedef struct {
		LPVOID pMapView;
		HANDLE hMap;
		HANDLE hFileSource;
		HANDLE hFileTarget;
	} COPY_DATA;

	void CloseAll(char* pszMem, HANDLE hMap, HANDLE hSrc, HANDLE hDst)
	{
		if (pszMem)
			UnmapViewOfFile(pszMem);
		if (hMap)
			CloseHandle(hMap);
		if (hSrc)
			CloseHandle(hSrc);
		if (hDst)
			CloseHandle(hDst);
	}

	VOID CALLBACK WriteFileIOCompletionRoutine(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped
	) {
		_putws(L"WriteFileIOCompletionRoutine() - Begin");

		if (lpOverlapped->hEvent != NULL) {
			COPY_DATA* pCopyData = (COPY_DATA*)lpOverlapped->hEvent;

			UnmapViewOfFile(pCopyData->pMapView);
			CloseAll(
				NULL,
				pCopyData->hMap,
				pCopyData->hFileSource,
				pCopyData->hFileTarget
			);
			free(pCopyData);

			_putws(L"WriteFileIOCompletionRoutine() - Release memory & handles");
		}

		free(lpOverlapped);
		_putws(L"WriteFileIOCompletionRoutine() - End");
	}

	int Main() {
		_putws(L"main() - Begin\n");
		
		_wsetlocale(LC_ALL, L"korean");

		HANDLE hFileSource = NULL, hFileTarget = NULL;
		LARGE_INTEGER llFileSize = { 0 };
		HANDLE hMap = NULL;
		char* pszMemory = NULL;

		hFileSource = CreateFile(
			TEXT("C:\\TEST\\videos.zip"),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFileSource == INVALID_HANDLE_VALUE)
		{
			wprintf(
				L"Failed to open source file [Error Code: %u]",
				GetLastError()
			);

			return 1;
		}

		if (!GetFileSizeEx(hFileSource, &llFileSize))
		{
			wprintf(
				L"Failed to open get file size [Error Code: %u]",
				GetLastError()
			);

			CloseAll(NULL, NULL, hFileSource, NULL);
			return 2;
		}

		hMap = CreateFileMapping(
			hFileSource,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL
		);

		if (hMap == NULL)
		{
			wprintf(
				L"Failed to open create file mapping obj [Error Code: %u]",
				GetLastError()
			);

			CloseAll(NULL, hMap, hFileSource, NULL);
			return 3;
		}

		pszMemory = (char*)MapViewOfFile(
			hMap,
			FILE_MAP_READ,
			0,
			0,
			(DWORD)llFileSize.QuadPart
		);

		if (pszMemory == NULL)
		{
			wprintf(
				L"Failed to get mapped view [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, NULL);
			return 3;
		}

		DeleteFile(
			TEXT("C:\\TEST\\videos copy.zip")
		);

		hFileTarget = CreateFile(
			TEXT("C:\\TEST\\videos copy.zip"),
			GENERIC_ALL,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL
		);

		if (hFileTarget == INVALID_HANDLE_VALUE) {
			wprintf(
				L"Failed to create target file [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, NULL);
			return 4;
		}

		LPOVERLAPPED pOverLapped = (LPOVERLAPPED)malloc(sizeof(OVERLAPPED));

		if (pOverLapped == NULL) {
			wprintf(
				L"Failed to allocate overlapped struct [Error Code: %u]",
				GetLastError()
			);

			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 5;
		}

		pOverLapped->OffsetHigh = 0;
		pOverLapped->Offset = 0;

		COPY_DATA* pCopyData = (COPY_DATA*)malloc(sizeof(COPY_DATA));

		if (pCopyData == NULL) {
			wprintf(
				L"Failed to allocate copy data struct [Error Code: %u]",
				GetLastError()
			);

			free(pOverLapped);
			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 6;
		}

		pCopyData->hFileSource = hFileSource;
		pCopyData->hFileTarget = hFileTarget;
		pCopyData->hMap = hMap;
		pCopyData->pMapView = pszMemory;

		pOverLapped->hEvent = pCopyData;

		if (WriteFileEx(
			hFileTarget,
			pszMemory,
			llFileSize.LowPart,
			pOverLapped,
			WriteFileIOCompletionRoutine
		) == NULL) {
			wprintf(
				L"Failed to write file [Error Code: %u]",
				GetLastError()
			);

			free(pOverLapped);
			CloseAll(pszMemory, hMap, hFileSource, hFileTarget);
			return 7;
		}

		if (SleepEx(INFINITE, TRUE) == WAIT_IO_COMPLETION) {
			_putws(L"APC Queue is empty\n");
		}

		_putws(L"main() - End\n");

		return 0;
	}
}

int main() 
{
	int retValue;

	retValue = AsyncCallbackFileCopyEx::Main();

	printf("Return Value: %d\n", retValue);

	return 0;
}