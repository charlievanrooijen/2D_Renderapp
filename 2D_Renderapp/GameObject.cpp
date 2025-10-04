#include "GameObject.h"
#include <windows.h>
#include <vector>

std::vector<RectangleObject> rectangles;

void addRectangle(const RectangleObject& rect) {
    rectangles.push_back(rect);
}

bool checkCollision(const RectangleObject& newRect) {
    for (const RectangleObject& rect : rectangles) {
        if (newRect.id != rect.id &&  
            newRect.right > rect.left &&
            newRect.left < rect.right &&
            newRect.bottom > rect.top &&
            newRect.top < rect.bottom) {
            return true;
        }
    }
    return false;
}

void drawRectangle(HDC hdc, const RectangleObject& rect) {
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
