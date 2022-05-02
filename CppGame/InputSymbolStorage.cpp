#include "InputSymbolStorage.h"

std::string inputSymbolStorage::GetState() {
	 return buf;
}

void inputSymbolStorage::Set(int input, bool isDown) {
	_storage[input].isChanged = isDown != _storage[input].isDown;
	_storage[input].isDown = isDown;
}

void inputSymbolStorage::StartPrinting() {
	while (true) {
		for (int i = 0; i < 300; i++) {
			if (_storage[i].isDown) {
				ReactOnButton(i);
			}
		}
	}
}

void inputSymbolStorage::ReactOnButton(int Button) {
	static float x = 50.0;
	int shift = 0;
	switch (Button)
	{
		case BUTTON_BACKSPACE:
			//todo
			//delete last
			if (!buf.empty()) {
				buf.pop_back();
			}
			_storage[Button].isDown = false;
			return;
		break;
		case BUTTON_LEFT_SHIFT:
			break;
		case BUTTON_ENTER:
			PrintString({50,100}, buf.c_str(), 0x00FFFFFF, font32, *frameBuf);
			break;
	default:
		if (Button > 64 && Button < 91) {
			if (_storage[BUTTON_LEFT_SHIFT].isDown) {
				//shift = PrintChar({x,50}, Button, 0x00FFFFFF, font32, *frameBuf);
				buf.push_back(Button);
			}
			else {
				//shift = PrintChar({ x,50 }, Button+32, 0x00FFFFFF, font32, *frameBuf);
				buf.push_back(Button + 32);
			}
		}
		else {
			//shift = PrintChar({x,50}, Button, 0x00FFFFFF, font32, *frameBuf);
			buf.push_back(Button);
		}
		x += shift;
		_storage[Button].isDown = false;
		break;
	}
	
}

std::string inputSymbolStorage::buf;
RenderState* inputSymbolStorage::frameBuf;
button inputSymbolStorage::_storage[300];