#define _USE_MATH_DEFINES
#include <math.h>
#include "Canvas.h"
#include "../lib/include/GLFW/glfw3.h"

CCanvas::CCanvas(GLFWwindow* window)
	:m_window(window)
{
}

void CCanvas::SetColor(Color color)
{
	m_color = GetRgb(color);
}

void CCanvas::DrawLine(const CPoint& firstPoint, const CPoint& secondPoint)
{
	glLineWidth(2);
	glColor3d(m_color.m_red, m_color.m_green, m_color.m_blue);
	glBegin(GL_LINES);
	

	glVertex2d(firstPoint.GetX(), firstPoint.GetY());
	glVertex2d(secondPoint.GetX(), secondPoint.GetY());

	glEnd();

	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius)
{
	glLineWidth(4);
	glColor3d(m_color.m_red, m_color.m_green, m_color.m_blue);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++) {
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * horizontalRadius) + center.GetX(), (sin(degInRad) * verticalRadius) + center.GetY());
	}

	glEnd();
	glEnable(GL_LINE_SMOOTH);
}
