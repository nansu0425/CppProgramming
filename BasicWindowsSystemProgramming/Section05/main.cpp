#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>

namespace ProcessHeapEx {
	int Main() {
		// HANDLE hProcHeap = GetProcessHeap();
		HANDLE hProcHeap = HeapCreate(0, 0, 0);

		if (hProcHeap == NULL) {
			printf("Failed to create heap [Error code: %u]\n",
				GetLastError());

			return 1;
		}

		LPVOID pMem1 = HeapAlloc(hProcHeap, 0, 4);
		LPVOID pMem2 = HeapAlloc(hProcHeap, 0, 4 * 1024 * 1024);

		PSZ pszMem = (PSZ)pMem2;

		pszMem[0] = 'a';

		PROCESS_HEAP_ENTRY entry = { 0 };

		while (HeapWalk(hProcHeap, &entry) != FALSE) {
			if ((entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0) {
				_tprintf(TEXT("Allocated block"));

				if ((entry.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0) {
					_tprintf(TEXT(", movable with HANDLE %#p"), entry.Block.hMem);
				}

				if ((entry.wFlags & PROCESS_HEAP_ENTRY_DDESHARE) != 0) {
					_tprintf(TEXT(", DDESHARE"));
				}
			}
			else if ((entry.wFlags & PROCESS_HEAP_REGION) != 0) {
				_tprintf(
					TEXT("Region\n %d bytes committed\n") \
					TEXT(" %d bytes uncommitted\n First block address: %#p\n") \
					TEXT(" Last block address: %#p\n"),
					entry.Region.dwCommittedSize,
					entry.Region.dwUnCommittedSize,
					entry.Region.lpFirstBlock,
					entry.Region.lpLastBlock
				);
			}
			else if ((entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0) {
				_tprintf(TEXT("Uncommitted range\n")); 
			}
			else {
				_tprintf(TEXT("Block\n"));
			}

			_tprintf(
				TEXT(" Data portion begins at: %#p\n Size: %d bytes\n") \
				TEXT(" Overhead: %d bytes\n Region index: %d\n\n"),
				entry.lpData,
				entry.cbData,
				entry.cbOverhead,
				entry.iRegionIndex
			);
		}

		HeapFree(hProcHeap, 0, pMem1);
		HeapFree(hProcHeap, 0, pMem2);
		HeapDestroy(hProcHeap);

		return 0;
	}
}

int main() {
	unsigned ret;
	ret = ProcessHeapEx::Main();

	printf("Return code: %u\n", ret);

	return 0;
}