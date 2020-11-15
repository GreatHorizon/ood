#pragma once
#include "../Slide/ICanvas.h"
#include <sstream>
#include <iomanip> 

class MockCanvas : public ICanvas
{
public:

	MockCanvas(std::stringstream& out)
		: m_out(out)
	{
	}

	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override
	{
		m_out << "Drawing line\n";
	}

	void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius) override
	{
		m_out << "Drawing ellipse\n";
	}

	void SetFillColor(RGBAColor color) override
	{
		m_out << "Set " << std::hex << std::setfill('0') << std::setw(8) << color << " fill color\n";
	}

	void SetOutlineColor(RGBAColor color) override
	{
		m_out << "Set " << std::hex << std::setfill('0') << std::setw(8) <<color << " outline color\n";
	}

	void SetLineWidth(float thickness) override
	{
		m_out << "Set " << thickness << " line width\n";
	}

	void FillPolygon(const std::vector<CPoint>& vertices) override
	{
		m_out << "Fill poligon\n";
	}

	void FillEllipse(const CPoint& center, double horizontalRadius, double verticalRadius) override
	{
		m_out << "Fill ellipse\n";
	}
private:
	std::stringstream& m_out;
};