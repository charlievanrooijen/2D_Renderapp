#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <windows.h>

struct RectangleObject {
    int id;
    int left;
    int top; 
    int right; 
    int bottom;
};

extern std::vector<RectangleObject> rectangles;

void addRectangle(const RectangleObject& rect);
bool checkCollision(const RectangleObject& rect);
void drawRectangle(HDC hdc, const RectangleObject& rect);

#endif
