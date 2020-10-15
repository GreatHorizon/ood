#pragma once
#include "ICanvas.h"
#include "Point.h"
#include "../lib/include/GLFW/glfw3.h"

struct RGB
{
	double m_red;
	double m_green;
	double m_blue;

	RGB(double red = 255, double green = 255, double blue = 255)
		: m_red(red)
		, m_green(green)
		, m_blue(blue)
	{
	}
};

inline RGB GetRgb(Color color)
{
	switch (color)
	{
	case Color::GREEN:
		return RGB(0, 255, 0);
	case Color::RED:
		return RGB(255, 0, 0);
	case Color::BLUE:
		return RGB(0, 0, 255);
	case Color::YELLOW:
		return RGB(255, 255, 0);
	case Color::PINK:
		return RGB(255, 192, 203);
	case Color::BLACK:
		return RGB(0, 0, 0);
	default:
		return RGB(255, 255, 255);
	}
}

class CCanvas : public ICanvas
{
public:
	void SetColor(Color color) override;
	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override;
	void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius) override;

	CCanvas(GLFWwindow* window);
private:
	GLFWwindow* m_window;
	RGB m_color;
};