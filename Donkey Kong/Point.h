#pragma once
class Point {
    int x;
    int y;

public:
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
};
