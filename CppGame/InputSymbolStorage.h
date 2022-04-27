#pragma once
#include <windows.h>

struct button {
	bool isDown;
	bool isChanged;
};

enum {
	/*ALL USED BUTTONS*/
	BUTTON_RSHIFT,
	BUTTON_LSHIFT,
	BUTTON_RCTRL,
	BUTTON_LCTRL,
	BUTTON_ESC,
	BUTTON_CMD,
	BUTTON_ALT,
	BUTTON_ENTER,
	BUTTON_BACKSPACE,
	BUTTON_CAPS,
	BUTTON_TAB,
	BUTTON_F1,
	BUTTON_F2,
	BUTTON_F3,
	BUTTON_F4,
	BUTTON_F5,
	BUTTON_F6,
	BUTTON_F7,
	BUTTON_F8,
	BUTTON_F9,
	BUTTON_F10,
	BUTTON_F11,
	BUTTON_F12,
	BUTTON_PRINT_SCREEN,
	BUTTON_DEL,
	BUTTON_INS,
	BUTTON_HOME,
	BUTTON_END,
	BUTTON_PAGE_UP,
	BUTTON_PAGE_DOWN,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_0,
	BUTTON_MINUS,
	BUTTON_PLUS,
	BUTTON_TILDA,
	BUTTON_NUM_LOCK,
	BUTTON_Q,
	BUTTON_W,
	BUTTON_E,
	BUTTON_R,
	BUTTON_T,
	BUTTON_Y,
	BUTTON_U,
	BUTTON_I,
	BUTTON_O,
	BUTTON_P,
	BUTTON_OPEN_BRACKET,
	BUTTON_CLOSE_BRACKET,
	BUTTON_A,
	BUTTON_S,
	BUTTON_D,
	BUTTON_F,
	BUTTON_G,
	BUTTON_H,
	BUTTON_J,
	BUTTON_K,
	BUTTON_L,
	BUTTON_SEMICOLON,
	BUTTON_QUOTES,
	BUTTON_Z,
	BUTTON_X,
	BUTTON_C,
	BUTTON_V,
	BUTTON_B,
	BUTTON_N,
	BUTTON_M,
	BUTTON_LESS_THAN,
	BUTTON_MORE_THAN,
	BUTTON_QUESTION,

	BUTTONS_COUNT//Should be last
};

static class inputSymbolStorage {
public:
	inputSymbolStorage() {
		ZeroMemory(_storage, BUTTONS_COUNT);
	}
	void Set(int input);
	void Remove();
	void GetLast();
private:
	button _storage[BUTTONS_COUNT];
};