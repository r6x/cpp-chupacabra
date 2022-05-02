#define isDown(a) input->buttons[a].isDown
#define ifPressed(a) input->buttons[a].isDown && input->buttons[a].changed
#define ifReleased(a) (!input->buttons[a].isDown && input->buttons[a].changed)
/*
globalVariable vec2 playerPos = { 0.f, 0.f };

vec2 startPos{50, 50};
internal void simulate(Input* input, long double deltaTime, unsigned int vkCode) {
	//FillScreen(0xFF000000);
	float speed = 150.f;
	if (ifPressed(BUTTON_UP)) {
		playerPos.y += speed * deltaTime;
	}
	if (ifPressed(BUTTON_DOWN)) {
		playerPos.y -= speed * deltaTime;
	}
	if (ifPressed(BUTTON_LEFT)) {
		playerPos.x -= speed * deltaTime;
	}
	if (ifPressed(BUTTON_RIGHT)) {
		playerPos.x += speed * deltaTime;
	}
	vec2 pos = startPos;
	PrintChar(pos, char(vkCode), 0x00FFFF, font32);
	//PrintString(pos, "Privet", 0x00FFFF , font32);
	//DrawRect(playerPos.x, playerPos.y, 5, 5, 0xFF0000FF);
}

*/