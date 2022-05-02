#include "Renderer.h"

void RenderBackground(RenderState rs) {
	unsigned int* pixel = (unsigned int*)rs.frameBuf;
	for (int i = 0; i < rs.width; i++) {
		for (int j = 0; j < rs.height; j++) {
			*pixel++ = j*i;
		}
	}
}

internal void DrawPixel(vec2 pos, unsigned int color, RenderState rs) {
	unsigned int* frameBuf = (unsigned int*)rs.frameBuf;
	int y = pos.y;
	int x = pos.x;
	if (pos.x < 0 || pos.x > rs.width || pos.y < 0 || pos.y > rs.height) {
		return;
	}
	frameBuf[y * rs.width + x] = color;
}

 void FillScreen(unsigned int Color, RenderState rs) {
	unsigned int* frameBuf = (unsigned int*)rs.frameBuf;
	for (int x = 0; x < rs.width; x++) {
		for (int y = 0; y < rs.height; y++) {
			*frameBuf++ = Color;
		}
	}
}

internal void DrawRectInPixels(int startX, int startY, int sizeX, int sizeY, unsigned int color, RenderState rs) {
	unsigned int* buf = (unsigned int*)rs.frameBuf;
	
	startX = Clamp(0, startX, rs.width);
	startY = Clamp(0, startY, rs.height);
	sizeX = Clamp(0, sizeX, rs.width - startX);
	sizeY = Clamp(0, sizeY, rs.height - startY);
	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			buf[(startY + y) * rs.width + startX + x] = color;
		}
	}
}

globalVariable float renderScale = 0.01f;

internal void DrawRect(float x, float y, float width, float height, unsigned int color, RenderState rs) {

	x *= rs.height * renderScale;
	y *= rs.height * renderScale;

	width *= rs.height * renderScale;
	height *= rs.height * renderScale;

	x += rs.width / 2.f;
	y += rs.height / 2.f;

	int xPix = x - width / 2;
	int yPix = y - height / 2;

	int widthPix = x + width;
	int heightPix = y + height;

	DrawRectInPixels(xPix, yPix, width, height, color, rs);
}

int PrintChar(vec2 pos, const char in, unsigned int color, font fontSize, RenderState rs) {

	int bytesPerSymbol = (fontSize.height * fontSize.width) / 8 + 1;

	int symbol = in - 32; // minus 32 because symbols in font array starts with ' '
	vec2 p = pos;
	int count = 0;

	for (int x = 0; x < fontSize.font[symbol * bytesPerSymbol] + 1; x++) {
		char temp = 0;
		for (int y = 0; y < fontSize.height; y++) {
			if (count % 8 == 0) {
				temp = fontSize.font[symbol * bytesPerSymbol + 1 + count / 8];
			}
			if ((temp & 1) == 1) {
				DrawPixel(p, color, rs);
			}
			temp = temp >> 1;
			count++;
			p.y -= 1;
		}
		p.y = pos.y;
		p.x += 1;
		
	}
	return fontSize.font[symbol * bytesPerSymbol];
}

int PrintAlternateChar(vec2 pos, const char in, unsigned int color, font fontSize, RenderState rs) {
	char d;
	switch (in)
	{
		case BUTTON_ONE:
		d = '!';
		break;
	}
	return 0;
}

void PrintString(vec2 pos, const char* in, unsigned int color, font fontSize, RenderState rs) {
	int count = CountSize(in);
	int temp = 0;
	for (int i = 0; i < count; i++) {
		temp = PrintChar(pos, *in, color, fontSize, rs);
		pos.x += temp;
		in++;
	}
}