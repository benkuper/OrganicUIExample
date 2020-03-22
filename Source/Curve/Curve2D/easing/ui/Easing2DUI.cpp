/*
  ==============================================================================

	Easing2DUI.cpp
	Created: 16 Dec 2016 7:13:11pm
	Author:  Ben

  ==============================================================================
*/

#include "Easing2DUI.h"

#pragma warning(disable:4244)

Easing2DUI::Easing2DUI(Easing2D* e) :
	InspectableContentComponent(e),
	easing(e),
	showFirstHandle(false),
	showLastHandle(false)
{
	autoDrawContourWhenSelected = false;

	bringToFrontOnSelect = false;

	setRepaintsOnMouseActivity(true);
	easing->addAsyncContainerListener(this);
}

Easing2DUI::~Easing2DUI()
{
	if (!easing.wasObjectDeleted()) easing->removeAsyncContainerListener(this);
}

void Easing2DUI::paint(Graphics& g)
{
	//g.fillAll(Colours::purple.withAlpha(.2f));

	Colour c = NORMAL_COLOR;
	if (easing.wasObjectDeleted()) return;
	if (easing->isSelected) c = HIGHLIGHT_COLOR;
	if (isMouseOver()) c = c.brighter();

	g.setColour(c);
	g.strokePath(drawPath, PathStrokeType(isMouseOver() ? 2 : 1));

	//g.setColour(Colours::purple);
	//g.strokePath(hitPath, PathStrokeType(2));

	paintInternal(g);

}

void Easing2DUI::resized()
{
	generatePath();
}

void Easing2DUI::generatePath()
{

	drawPath.clear();
	drawPath.startNewSubPath(getUIPosForValuePos(easing->start).toFloat());

	if (valueBounds.isEmpty() || (easing->start == easing->end)) return;

	generatePathInternal();
	if (drawPath.getLength()) buildHitPath();

}

void Easing2DUI::generatePathInternal()
{
	autoGeneratePathWithPrecision();
}

void Easing2DUI::autoGeneratePathWithPrecision(int precision)
{
	if (getHeight() == 0) return;
	if (precision == 0) precision = getWidth();
	else precision = jmin(getWidth(), precision);

	for (int i = 1; i <= precision; i++)
	{
		float t = i * 1.f / precision;
		Point<float> v = easing->getValue(t);
		
		Point<int> pv = getUIPosForValuePos(v);
		drawPath.lineTo(pv.toFloat());
	}
}

void Easing2DUI::buildHitPath()
{
	Array<Point<float>> hitPoints;

	for (int i = 0; i <= hitPathPrecision; i++)
	{
		hitPoints.add(drawPath.getPointAlongPath(drawPath.getLength() * i / (hitPathPrecision - 1)));
	}

	const float margin = 5;

	hitPath.clear();
	Array<Point<float>> firstPoints;
	Array<Point<float>> secondPoints;
	for (int i = 0; i < hitPathPrecision; i++)
	{
		Point<float> tp;
		Point<float> sp;
		if (i == 0 || i == hitPathPrecision - 1)
		{
			tp = hitPoints[i].translated(0, -margin);
			sp = hitPoints[i].translated(0, margin);
		}
		else
		{
			float angle1 = 0;
			float angle2 = 0;
			/*if (hitPoints[i].x == hitPoints[i - 1].x) angle1 = 0;
			else if (hitPoints[i].y == hitPoints[i - 1].y) angle1 = -float_Pi / 4;
			else */ angle1 = hitPoints[i].getAngleToPoint(hitPoints[i - 1]);

			/*if (hitPoints[i].x == hitPoints[i - 1].x) angle1 = 0;
			else if (hitPoints[i].y == hitPoints[i - 1].y) angle1 = -float_Pi / 4;
			else */angle2 = hitPoints[i].getAngleToPoint(hitPoints[i + 1]);


			if (angle1 < 0) angle1 += float_Pi * 2;
			if (angle2 < 0) angle2 += float_Pi * 2;

			float angle = (angle1 + angle2) / 2.f;

			if (angle1 < angle2) angle += float_Pi;

			tp = hitPoints[i].getPointOnCircumference(margin, angle + float_Pi);
			sp = hitPoints[i].getPointOnCircumference(margin, angle);
		}

		firstPoints.add(tp);
		secondPoints.insert(0, sp);
	}

	if (firstPoints.size() > 1 && !std::isnan(firstPoints[0].x))
	{
		hitPath.startNewSubPath(firstPoints[0]);
		for (int i = 1; i < firstPoints.size(); i++)
		{
			if (!std::isnan(firstPoints[i].x)) hitPath.lineTo(firstPoints[i]);
		}
		for (int i = 0; i < secondPoints.size(); i++)
		{
			if (!std::isnan(firstPoints[i].x)) hitPath.lineTo(secondPoints[i]);
		}
		hitPath.closeSubPath();
	}
}

bool Easing2DUI::hitTest(int tx, int ty)
{
	Point<int> p(tx, ty);
	Point<int> p1 = Point<int>(getUIPosForValuePos(easing->start));
	Point<int> p2 = Point<int>(getUIPosForValuePos(easing->end));
	
	return p.getDistanceFrom(p1) > 16 && p.getDistanceFrom(p2) > 16 && hitPath.contains((float)tx, (float)ty);
}

void Easing2DUI::setShowEasingHandles(bool showFirst, bool showLast)
{
	showFirstHandle = showFirst;
	showLastHandle = showLast;
}


void Easing2DUI::newMessage(const ContainerAsyncEvent& e)
{
	if (e.type == ContainerAsyncEvent::ControllableFeedbackUpdate)
	{
		easingControllableFeedbackUpdate(e.targetControllable);
		repaint();
	}
}


void Easing2DUI::setValueBounds(const Rectangle<float> _valueBounds)
{
	valueBounds = _valueBounds;
	resized();
}


Point<int> Easing2DUI::getUIPosForValuePos(const Point<float>& valuePos) const
{
	return getLocalBounds().getRelativePoint((valuePos.x - valueBounds.getX()) / valueBounds.getWidth(), (valuePos.y - valueBounds.getY()) / valueBounds.getHeight());
}

Point<float> Easing2DUI::getValuePosForUIPos(const Point<int>& uiPos) const
{
	return valueBounds.getRelativePoint(uiPos.x * 1.0f / getWidth(), uiPos.y*1.0f / getHeight());
}

// EASINGS
LinearEasing2DUI::LinearEasing2DUI(LinearEasing2D* e) :
	Easing2DUI(e)
{

}

void LinearEasing2DUI::generatePathInternal()
{
	drawPath.lineTo(getUIPosForValuePos(easing->end).toFloat());
}

CubicEasing2DUI::CubicEasing2DUI(CubicEasing2D* e) :
	Easing2DUI(e),
	syncHandles(false)
{
	addChildComponent(h1);
	addChildComponent(h2);
	h1.setVisible(showFirstHandle);
	h2.setVisible(showLastHandle);

	h1.addMouseListener(this, false);
	h2.addMouseListener(this, false);
}

bool CubicEasing2DUI::hitTest(int tx, int ty)
{
	bool result = Easing2DUI::hitTest(tx, ty);

	if (showFirstHandle)
	{
		result |= h1.getLocalBounds().contains(h1.getMouseXYRelative());
	}

	if (showLastHandle)
	{
		result |= h2.getLocalBounds().contains(h2.getMouseXYRelative());
	}

	return result;
}

void CubicEasing2DUI::resized()
{

	Point<int> p1 = Point<int>(getUIPosForValuePos(easing->start));
	Point<int> p2 = Point<int>(getUIPosForValuePos(easing->end));

	CubicEasing2D* ce = static_cast<CubicEasing2D*>(easing.get());

	Point<int> a = getUIPosForValuePos(easing->start + ce->anchor1->getPoint());
	Point<int> b = getUIPosForValuePos(easing->end + ce->anchor2->getPoint());

	h1.setBounds(juce::Rectangle<int>(0, 0, 16, 16).withCentre(a));
	h2.setBounds(juce::Rectangle<int>(0, 0, 16, 16).withCentre(b));

	Easing2DUI::resized();
}

void CubicEasing2DUI::generatePathInternal()
{
	Point<int> p1 = Point<int>(getUIPosForValuePos(easing->start));
	Point<int> p2 = Point<int>(getUIPosForValuePos(easing->end));

	CubicEasing2D* ce = static_cast<CubicEasing2D*>(easing.get());

	Point<int> a = getUIPosForValuePos(easing->start + ce->anchor1->getPoint());
	Point<int> b = getUIPosForValuePos(easing->end + ce->anchor2->getPoint());

	drawPath.cubicTo(a.toFloat(), b.toFloat(), p2.toFloat());
}

void CubicEasing2DUI::paintInternal(Graphics& g)
{
	if (!showFirstHandle && !showLastHandle) return;

	Point<int> p1 = Point<int>(getUIPosForValuePos(easing->start));
	Point<int> p2 = Point<int>(getUIPosForValuePos(easing->end));

	Colour c = LIGHTCONTOUR_COLOR;
	if (isMouseOver()) c = c.brighter();
	g.setColour(c);

	if(showFirstHandle) g.drawLine(p1.x, p1.y, h1.getBounds().getCentreX(), h1.getBounds().getCentreY());
	if(showLastHandle) g.drawLine(p2.x, p2.y, h2.getBounds().getCentreX(), h2.getBounds().getCentreY());

}

void CubicEasing2DUI::easingControllableFeedbackUpdate(Controllable* c)
{
	CubicEasing2D* ce = static_cast<CubicEasing2D*>(easing.get());
	if (c == ce->anchor1 || c == ce->anchor2)
	{
		resized();
		repaint();
	}
}

void CubicEasing2DUI::setShowEasingHandles(bool showFirst, bool showLast)
{
	Easing2DUI::setShowEasingHandles(showFirst, showLast);
	h1.setVisible(showFirstHandle);
	h2.setVisible(showLastHandle);
	resized();
	repaint();
}

void CubicEasing2DUI::mouseDrag(const MouseEvent& e)
{
	syncHandles = !e.mods.isAltDown();

	if (e.eventComponent == &h1 || e.eventComponent == &h2)
	{
		CubicEasing2D* ce = static_cast<CubicEasing2D*>(easing.get());

		Point2DParameter* targetAnchor = (e.eventComponent == &h1) ? ce->anchor1 : ce->anchor2;
		Point<float> targetRefPoint = (e.eventComponent == &h1) ? ce->start : ce->end;

		Point<float> targetPoint = getValuePosForUIPos(e.getEventRelativeTo(this).getPosition()); //Point<float>(mp.x * 1.f / getWidth(), jmap<float>(mp.y, y1, y2, 0, 1));
		targetAnchor->setPoint(targetPoint - targetRefPoint);
	}
	else
	{
		CubicEasing2D* ce = static_cast<CubicEasing2D*>(easing.get());

		Point<int> p1 = getUIPosForValuePos(easing->start);
		Point<int> p2 = getUIPosForValuePos(easing->end);
		Point<float> mVal = getValuePosForUIPos(e.getEventRelativeTo(this).getPosition());
		
		ce->anchor1->setPoint((mVal - easing->start) / 2);
		ce->anchor2->setPoint((mVal - easing->end) / 2);
	}
}

// HANDLES
Easing2DUI::Easing2DHandle::Easing2DHandle()
{
	setRepaintsOnMouseActivity(true);
}

void Easing2DUI::Easing2DHandle::paint(Graphics& g)
{
	//g.fillAll((isMouseOver()?Colours::yellow:Colours::orange).withAlpha(.5f));

	Colour c = LIGHTCONTOUR_COLOR;
	if (isMouseOver()) c = c.brighter(.8f);
	g.setColour(c);
	g.fillEllipse(getLocalBounds().reduced(isMouseOver() ? 4 : 6).toFloat());
}