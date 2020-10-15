#pragma once

class CPoint
{
public:
	CPoint(double xCoord, double yCoord)
		: x(xCoord)
		, y(yCoord)
	{
	}

	double GetX() const
	{
		return x;
	}

	double GetY() const
	{
		return y;
	}

	bool operator == (CPoint const& rightPoint) const
	{
		return GetX() == rightPoint.GetX() && GetY() == rightPoint.GetY();
	}
private:
	double x;
	double y;

};
