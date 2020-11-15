#pragma once

#include "ICanvas.h"
#include "Point.h"
#include "../lib/include/GLFW/glfw3.h"

struct RGBA
{
	double m_red;
	double m_green;
	double m_blue;
	double m_opacity;

	RGBA(double red = 255, double green = 255, double blue = 255, double opacity = 1)
		: m_red(red)
		, m_green(green)
		, m_blue(blue)
		, m_opacity(opacity)
	{
	}
};

inline RGBA GetRGBA(RGBAColor color)
{
	auto r = ((color >> 24) & 255) / 255.0;
	auto g = ((color >> 16) & 255) / 255.0;
	auto b = ((color >> 8)& 255) / 255.0;
	auto alpha = (color & 255) / 255.0;

	return RGBA(r, g, b, alpha);
}

class CCanvas : public ICanvas
{
public:
	void SetFillColor(RGBAColor color) override;
	void SetOutlineColor(RGBAColor color) override;
	void SetLineWidth(float thickness);

	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override;
	void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius) override;

	void FillPolygon(const std::vector<CPoint>& vertices) override;
	void FillEllipse(const CPoint& center, double horizontalRadius, double verticalRadius) override;
	
	CCanvas(GLFWwindow* window);
private:
	GLFWwindow* m_window;

	RGBAColor m_fillColor;
	RGBAColor m_outlineColor;
	float m_lineWidth = 2.f;
};

