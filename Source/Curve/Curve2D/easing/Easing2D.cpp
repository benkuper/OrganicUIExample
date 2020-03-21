/*
  ==============================================================================

	Curve2DEasing.cpp
	Created: 21 Mar 2020 4:06:44pm
	Author:  bkupe

  ==============================================================================
*/

#include "Curve2DEasing.h"

const String Easing2D::typeNames[Easing2D::TYPE_MAX] = { "Linear", "Bezier" };

Easing2D::Easing2D(Type type) :
	ControllableContainer("Easing"),
	type(type),
	length(0)
{
}

Easing2D::~Easing2D()
{
}

void Easing2D::updateKeys(const Point<float>& _start, const Point<float>& _end, bool updateKeys)
{
	start = _start;
	end = _end;
	if(updateKeys) updateLength();
}

LinearEasing2D::LinearEasing2D() :
	Easing2D(LINEAR)
{
}

Point<float> LinearEasing2D::getValue(const float& weight)
{
	return start + (end - start) * weight;
}

void LinearEasing2D::updateLength()
{
	length = end.getDistanceFrom(start);
}

Rectangle<float> LinearEasing2D::getBounds()
{
	return Rectangle<float>(jmin(start.x, end.x), jmin(start.y, end.y), jmax(start.x, end.x), jmax(start.y, end.y));
}

/*
Easing2DUI* LinearEasing2D::createUI()
{
	return nullptr;
}
*/

CubicEasing2D::CubicEasing2D() :
	Easing2D(BEZIER)
{
	anchor1 = addPoint2DParameter("Anchor 1", "First anchor for this interpolation");
	anchor2 = addPoint2DParameter("Anchor 2", "Second anchor for this interpolation");
}

void CubicEasing2D::updateKeys(const Point<float>& _start, const Point<float>& _end, bool updateKeys)
{
	Easing2D::updateKeys(_start, _end, false);
	if(updateKeys) updateBezier();
}

void CubicEasing2D::updateBezier()
{
	Point<float> a1 = start + anchor1->getPoint();
	Point<float> a2 = end + anchor2->getPoint();

	bezier = Bezier::Bezier<3>({ {start.x, start.y},{a1.x, a1.y},{a2.x,a2.y},{end.x,end.y} });
}

Point<float> CubicEasing2D::getValue(const float& weight)
{
	Bezier::Point p;
	p = bezier.valueAt(weight);
	return Point<float>(p.x, p.y);
}

void CubicEasing2D::updateLength()
{
	float result = 0;
	Point<float> a1 = start + anchor1->getPoint();
	Point<float> a2 = end + anchor2->getPoint();
	getBezierLength(start, a1, a2, end, 5, result);

	length = result;
}

void CubicEasing2D::getBezierLength(Point<float> A, Point<float> B, Point<float> C, Point<float> D, int precision, float& _length)
{
	if (precision > 0)
	{
		Point<float> a = A + (B - A) * 0.5f;
		Point<float> b = B + (C - B) * 0.5f;
		Point<float> c = C + (D - C) * 0.5f;
		Point<float> d = a + (b - a) * 0.5f;
		Point<float> e = b + (c - b) * 0.5f;
		Point<float> f = d + (e - d) * 0.5f;

		// left branch
		getBezierLength(A, a, d, f, precision - 1, _length);
		// right branch
		getBezierLength(f, e, c, D, precision - 1, _length);
	}
	else
	{
		float controlNetLength = (B - A).getDistanceFromOrigin() + (C - B).getDistanceFromOrigin() + (D - C).getDistanceFromOrigin();
		float chordLength = (D - A).getDistanceFromOrigin();
		_length += (chordLength + controlNetLength) / 2.0f;
	}
}

Rectangle<float> CubicEasing2D::getBounds()
{
	return Rectangle<float>();
}

void CubicEasing2D::onContainerParameterChanged(Parameter* p)
{
}

/*
Easing2DUI* CubicEasing2D::createUI()
{
	return nullptr;
}
*/