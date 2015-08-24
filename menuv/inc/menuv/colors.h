#ifndef MENUV_COLORS_H_
#define MENUV_COLORS_H_

enum MenuVColor
{
	COLOR_PRIMARY,
	COLOR_SECONDARY
};

class MenuVColorRGBA
{
public:
	int r = 255;
	int g = 255;
	int b = 255;
	int a = 255;

	MenuVColorRGBA() {};

	MenuVColorRGBA(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

#endif
