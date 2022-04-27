#include "fontStorage.cpp"

struct font {
    int height;
    int width;
    const unsigned short* font;
};

static font font32 = { 32, 24, Arial_Narrow24x32 };