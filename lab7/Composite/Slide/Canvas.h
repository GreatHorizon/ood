#pragma once

#include "ICanvas.h"
#include "Point.h"
#include "../lib/include/GLFW/glfw3.h"
#include "iostream"


inline double NormalizeColorÑomponent(double component)
{
	if (component > 255)
	{
		component = 255;
	}

	if (component < 0)
	{
		component = 0;
	}

	return component;
}


inline double NormalizeOpacity(double opacity)
{
	if (opacity > 1)
	{
		opacity = 1;
	}

	if (opacity < 0)
	{
		opacity = 0;
	}

	return opacity;
}

struct RGBA
{
	double m_red;
	double m_green;
	double m_blue;
	double m_opacity;

	RGBA(double red = 255, double green = 255, double blue = 255, double opacity = 1)
		: m_red(NormalizeColorÑomponent(red))
		, m_green(NormalizeColorÑomponent(green))
		, m_blue(NormalizeColorÑomponent(blue))
		, m_opacity(NormalizeOpacity(opacity))
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

