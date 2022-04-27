void RenderBackground() {
	unsigned int* pixel = (unsigned int*)renderState.frameBuf;
	for (int i = 0; i < renderState.width; i++) {
		for (int j = 0; j < renderState.height; j++) {
			*pixel++ = j*i;
		}
	}
}

internal void DrawPixel(vec2 pos, unsigned int color) {
	unsigned int* frameBuf = (unsigned int*)renderState.frameBuf;
	int y = pos.y;
	int x = pos.x;
	frameBuf[y * renderState.width + x] = color;
}

internal void FillScreen(unsigned int Color) {
	unsigned int* frameBuf = (unsigned int*)renderState.frameBuf;
	for (int x = 0; x < renderState.width; x++) {
		for (int y = 0; y < renderState.height; y++) {
			*frameBuf++ = Color;
		}
	}
}

internal void DrawRectInPixels(int startX, int startY, int sizeX, int sizeY, unsigned int color) {
	unsigned int* buf = (unsigned int*)renderState.frameBuf;
	
	startX = Clamp(0, startX, renderState.width);
	startY = Clamp(0, startY, renderState.height);
	sizeX = Clamp(0, sizeX, renderState.width - startX);
	sizeY = Clamp(0, sizeY, renderState.height - startY);
	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			buf[(startY + y) * renderState.width + startX + x] = color;
		}
	}
}

globalVariable float renderScale = 0.01f;

internal void DrawRect(float x, float y, float width, float height, unsigned int color) {

	x *= renderState.height * renderScale;
	y *= renderState.height * renderScale;

	width *= renderState.height * renderScale;
	height *= renderState.height * renderScale;

	x += renderState.width / 2.f;
	y += renderState.height / 2.f;

	int xPix = x - width / 2;
	int yPix = y - height / 2;

	int widthPix = x + width;
	int heightPix = y + height;

	DrawRectInPixels(xPix, yPix, width, height, color);
}

int PrintChar(vec2 pos, const char in, unsigned int color, font fontSize) {
	unsigned int* frame = (unsigned int*)renderState.frameBuf;

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
				DrawPixel(p, color);
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

void PrintString(vec2 pos, const char* in, unsigned int color, font fontSize) {
	int count = CountSize(in);
	int temp = 0;
	for (int i = 0; i < count; i++) {
		temp = PrintChar(pos, *in, color, fontSize);
		pos.x += temp;
		in++;
	}
}