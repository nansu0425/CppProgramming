#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define IMPLICIT_LINKING

#ifdef IMPLICIT_LINKING
#pragma comment(lib, "..\\x64\\Debug\\DllTest.lib")
VOID WINAPI DllTestFunction(int);

namespace ImplicitLinkingEx {

	int Main() {
		Sleep(1000);

		DllTestFunction(5);

		return 0;
	}
}
#endif // IMPLICIT_LINKING

#ifdef EXPLICIT_LINKING
namespace ExplicitLinkingEx {
	int Main() {
		_tprintf(_T("ExplicitLinkingEx: Load DLL\n"));
		HMODULE hModule = LoadLibrary(_T("DllTest.dll"));

		if (hModule == NULL) {
			_tprintf(
				_T("Failed to load DLL [Error code: %u]\n"),
				GetLastError()
			);
			
			return 1;
		}

		VOID(WINAPI * pfDllTestFunction)(int) = NULL;
		pfDllTestFunction = (VOID(WINAPI*)(int))GetProcAddress(
			hModule,
			"DllTestFunction"
		);

		if (pfDllTestFunction == NULL) {
			_tprintf(
				_T("Failed to get procedure address [Error code: %u]\n"),
				GetLastError()
			);

			return 2;
		}

		_tprintf(_T("ExplicitLinkingEx: Call DllTestFunction\n"));
		pfDllTestFunction(10);

		_tprintf(_T("ExplicitLinkingEx: Free Dll\n"));
		FreeLibrary(hModule);

		return 0;
	}
}
#endif // EXPLICIT_LINKING

int main() {
	UINT ret = 0;
	
#ifdef IMPLICIT_LINKING
	ret = ImplicitLinkingEx::Main();
#endif // IMPLICIT_LINKING

#ifdef EXPLICIT_LINKING
	ExplicitLinkingEx::Main();
#endif // EXPLICIT_LINKING

	printf("Return value: %u\n", ret);

	return 0;
}