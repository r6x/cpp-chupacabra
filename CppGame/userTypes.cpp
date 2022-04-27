#include "userTypes.h"

vec2 vec2::operator*(vec2 a) {
	this->x *= a.x;
	this->y *= a.y;
	return *this;
}

vec2 vec2::operator+(vec2 a) {
	this->x += a.x;
	this->y += a.y;
	return *this;
}

vec2 vec2::operator/(vec2 a) {
	this->x /= a.x;
	this->y /= a.y;
	return *this;
}

vec2 vec2::operator=(vec2 a) {
	this->x = a.x;
	this->x = a.y;
	return *this;
}

int vec2::getX() {
	return this->x;
}

int vec2::getY() {
	return this->y;
}