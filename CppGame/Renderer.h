#pragma once
#include "font.h"
#include "utils.h"
#include "Button_defines.h"
#include <Windows.h>

#define internal static
#define globalVariable static

struct RenderState {
	int width;
	int height;
	void* frameBuf;
	BITMAPINFO bitmapinfo;
};

void RenderBackground(RenderState rs);
internal void DrawPixel(vec2 pos, unsigned int color, RenderState rs);
 void FillScreen(unsigned int Color, RenderState rs);
internal void DrawRectInPixels(int startX, int startY, int sizeX, int sizeY, unsigned int color, RenderState rs);
internal void DrawRect(float x, float y, float width, float height, unsigned int color, RenderState rs);
int PrintChar(vec2 pos, const char in, unsigned int color, font fontSize, RenderState rs);
void PrintString(vec2 pos, const char* in, unsigned int color, font fontSize, RenderState rs);