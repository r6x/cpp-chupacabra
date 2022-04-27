#pragma once


class vec2 {
public:
	vec2() : x(0), y(0) {};
	vec2(int x, int y) : x(x), y(y) {};
	vec2 operator + (vec2);
	vec2 operator = (vec2);
	vec2 operator * (vec2);
	vec2 operator / (vec2);
	int getX();
	int getY();
private:
	int x;
	int y;
};