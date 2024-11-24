#pragma once
class platform
{
	char m_shape;
	int m_length;
	int m_xStart;
	int m_yStart;

public:
	void init(char shape, int xStart, int yStart, int length = 20) { this->m_length = length; this->m_shape = shape; this->m_xStart = xStart; this->m_yStart = yStart; }

	void draw();
};

