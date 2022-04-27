#include <Windows.h>
//#include "userTypes.h"
#include "utils.cpp"
#include "font.cpp"
#include "sqlite3.h"
#include "InputSymbolStorage.h"
globalVariable bool running = true;

#define processButton(a,b) 	case b:\
input.buttons[a].changed = isDown != input.buttons[a].isDown;\
input.buttons[a].isDown = isDown;\
break;

struct RenderState {
	int width;
	int height;
	void* frameBuf;
	BITMAPINFO bitmapinfo;
};

globalVariable RenderState renderState;

#include "Renderer.cpp"
#include "platform_common.cpp"
#include "game.cpp"


LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	int bufferSize = 0;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY : 
		running = false;
		break;
	case WM_SIZE:
		RECT rect;
		GetClientRect(hwnd, &rect);
		renderState.width = rect.right - rect.left;
		renderState.height = rect.bottom - rect.top;

		bufferSize = renderState.width * renderState.height * sizeOfPixel;

		if (renderState.frameBuf) {
			VirtualFree(renderState.frameBuf, NULL, MEM_RELEASE);
		}
		renderState.frameBuf = VirtualAlloc(NULL, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		renderState.bitmapinfo.bmiHeader.biSize = sizeof(renderState.bitmapinfo.bmiHeader);
		renderState.bitmapinfo.bmiHeader.biWidth = renderState.width;
		renderState.bitmapinfo.bmiHeader.biHeight = renderState.height;
		renderState.bitmapinfo.bmiHeader.biPlanes = 1;
		renderState.bitmapinfo.bmiHeader.biBitCount = 32;
		renderState.bitmapinfo.bmiHeader.biCompression = BI_RGB;
		break;
	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return result;
}

inputSymbolStorage s;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window Class";
	windowClass.lpfnWndProc = WindowCallback;

	RegisterClass(&windowClass);
	
	
	HWND window = CreateWindow(windowClass.lpszClassName, L"My first window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0 , 0, hInstance, 0);

	HDC hdc = GetDC(window);

	Input input = {};
	vec2 d = {150, 150};
	long double deltaTime = 0.016666f;

	LARGE_INTEGER frameBeginTime;
	QueryPerformanceCounter(&frameBeginTime);

	long double performanceFrequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performanceFrequency = (long double)perf.QuadPart;
	}
	char sdf;
	unsigned int vkCode = 65;
	while (running) {
		//input
		MSG message;
		
		bool isDown = false;
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
				vkCode = (unsigned int)message.wParam;
				isDown = ((message.lParam & (1<<31)) == 0);
				s.Set(vkCode);
				switch (vkCode)
				{
				
					processButton(BUTTON_UP, VK_UP);
					processButton(BUTTON_DOWN, VK_DOWN);
					processButton(BUTTON_LEFT, VK_LEFT);
					processButton(BUTTON_RIGHT, VK_RIGHT);
				default:
					break;
				}
				break;
			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
				break;
			}
			
		}
		//simulate
		simulate(&input, deltaTime, vkCode);
		//render
		StretchDIBits(hdc, 0 ,0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.frameBuf, &renderState.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	
		LARGE_INTEGER frameEndTime;
		QueryPerformanceCounter(&frameEndTime);
		deltaTime = (long double)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / performanceFrequency;
		frameBeginTime = frameEndTime;
	}
}