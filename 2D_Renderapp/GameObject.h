#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <windows.h>

struct RectangleObject {
    int id;
    int position[2];
    int size[2];
    COLORREF color;
    bool physicsObject;
};

int createRectangle(int position[], int size[], COLORREF color, bool physicsObject);
RectangleObject getRectangleObjectById(int id);
void drawRectangle(HDC hdc, RectangleObject& rect);

void addRectangle(RectangleObject& rect);
bool checkCollision(const RectangleObject& rect);
void drawRectangle(HDC hdc, RectangleObject& rect);
void freeRectObjectsMem();

#endif
