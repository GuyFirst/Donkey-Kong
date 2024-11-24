#include "platform.h"
#include "general.h"
#include <iostream>
void platform::draw()
{
	gotoxy(platform::m_xStart, platform::m_yStart);
	for (int i = 0; i < platform::m_length; i++) {
		std::cout << platform::m_shape;
	}
}
