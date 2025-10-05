#include "GameObject.h"
#include <windows.h>

RectangleObject *rectArray = nullptr;
int lenghtOfRectArray = 0;

int createRectangle(int position[], int size[], COLORREF color, bool physicsObject) {
    RectangleObject rect; 
    rect.position[0] = position[0];
    rect.position[1] = position[1];
    rect.size[0] = size[0];
    rect.size[1] = size[1];
    rect.color = color;
    rect.physicsObject = physicsObject;

    if (rectArray == nullptr) {
        rect.id = lenghtOfRectArray;
        rectArray = (RectangleObject*)malloc(sizeof(RectangleObject));
        rectArray[lenghtOfRectArray] = rect;
    } else {
        rect.id = rectArray[lenghtOfRectArray - 1].id + 1;
        rectArray = (RectangleObject*)realloc(rectArray, sizeof(RectangleObject) * (lenghtOfRectArray + 1));
        rectArray[lenghtOfRectArray] = rect;
    }
    
    rectArray[lenghtOfRectArray].id = lenghtOfRectArray;
    lenghtOfRectArray++;
    return rect.id;
}

RectangleObject getRectangleObjectById(int id) {
    for (int i = 0; i < lenghtOfRectArray; i++) {
        if (rectArray[i].id == id) {
            return rectArray[i];
        }
    }

    RectangleObject empty = {0};
    return empty;
}

void drawRectangle(HDC hdc, RectangleObject &rect) {
    HBRUSH brush = CreateSolidBrush(rect.color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    Rectangle(hdc, rect.position[0], 
              rect.position[1], 
              rect.position[0] + rect.size[0], 
              rect.position[1] + rect.size[1]);
              
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

void freeRectObjectsMem() {
    free(rectArray);
}

