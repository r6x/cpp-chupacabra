struct ButtonState {
	bool isDown;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, //should be last
};

struct Input {
	ButtonState buttons[BUTTON_COUNT];
};

