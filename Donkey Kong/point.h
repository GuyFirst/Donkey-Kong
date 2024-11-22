#pragma once
class point
{
	int x;
	int y;
public:
    void init(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() const { return x; }
    int getY() const { return y; }
};

