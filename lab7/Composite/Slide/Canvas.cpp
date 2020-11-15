#define _USE_MATH_DEFINES
#include <cmath>
#include "Canvas.h"


void CCanvas::SetFillColor(RGBAColor color)
{
	m_fillColor = color;
}

void CCanvas::SetOutlineColor(RGBAColor color)
{
	m_outlineColor = color;
}

void CCanvas::SetLineWidth(float thickness)
{
	m_lineWidth = thickness;
}

void CCanvas::DrawLine(const CPoint& fromPoint, const CPoint& toPoint)
{
	glEnable(GL_BLEND);
	glLineWidth(m_lineWidth);
	
	auto rgba = GetRGBA(m_outlineColor);

	glColor4d(rgba.m_red, rgba.m_green, rgba.m_blue, rgba.m_opacity);

	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINES);

	glVertex2d(fromPoint.GetX(), fromPoint.GetY());
	glVertex2d(toPoint.GetX(), toPoint.GetY());

	glEnd();
}

void CCanvas::DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius)
{
	glLineWidth(m_lineWidth);
	auto rgba = GetRGBA(m_outlineColor);

	glColor4d(rgba.m_red, rgba.m_green, rgba.m_blue, rgba.m_opacity);
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++) {
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.GetX(), (sin(degInRad) * verticalRadius) + center.GetY());
	}

	glEnd();
}

void CCanvas::FillPolygon(const std::vector<CPoint>& vertices)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto rgba = GetRGBA(m_fillColor);

	glColor4d(rgba.m_red, rgba.m_green, rgba.m_blue, rgba.m_opacity);

	glBegin(GL_POLYGON);

	for (auto& vertex : vertices)
	{
		glVertex2d(vertex.GetX(), vertex.GetY());
	}

	glEnd();
}

void CCanvas::FillEllipse(const CPoint& center, double horizontalRadius, double verticalRadius)
{
	auto rgba = GetRGBA(m_fillColor);

	glColor4d(rgba.m_red, rgba.m_green, rgba.m_blue, rgba.m_opacity);
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++) {
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.GetX(), (sin(degInRad) * verticalRadius) + center.GetY());
	}

	glEnd();
}

CCanvas::CCanvas(GLFWwindow* window)
	: m_window(window)
{

}
