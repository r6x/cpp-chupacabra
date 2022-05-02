#include "utils.h"
inline int Clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max)return max;
	return val;
}

char* LoadFile(const char* path) {
	HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		int fileSize = GetFileSize(file, NULL);
		char* fileCont = (char*)HeapAlloc(GetProcessHeap(), NULL, fileSize);
		if (fileCont != nullptr) {
			ReadFile(file, fileCont, fileSize, NULL, NULL);
			return fileCont;
		}
	}
	CloseHandle(file);
}

int CountSize(const char* in) {
	int count = 0;
	while (*in != '\0') {
		count++;
		in++;
	}
	return count;
}


