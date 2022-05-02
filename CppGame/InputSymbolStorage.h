#pragma once
#include <windows.h>
#include <thread>
#include <string>
#include "Renderer.h"
#include "Button_defines.h"

typedef struct button {
	bool isDown;
	bool isChanged;
};

class inputSymbolStorage {
public:
	inputSymbolStorage(RenderState *rs) {
		frameBuf = rs;
		for (int i = 0; i < 300; i++) {
			_storage[i].isChanged = false;
			_storage[i].isDown = false;
		}
		std::thread t(StartPrinting);
		t.detach();
	}
	void Set(int input, bool isDown);
	std::string GetState();
	static void ReactOnButton(int Button);
private:
	static void StartPrinting();
	static button _storage[300];
	static RenderState* frameBuf;
	static std::string buf;
};

