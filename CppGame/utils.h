#pragma once
#include <windows.h>

#define globalVariable static
#define internal static

inline int Clamp(int min, int val, int max);
char* LoadFile(const char* path);
int CountSize(const char* in);

globalVariable int sizeOfPixel = 32;

struct vec2 {
	float x;
	float y;
};