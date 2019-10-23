/*
  ==============================================================================

    AutomationKeyframeKeyUI.cpp
    Created: 18 Dec 2018 11:24:23am
    Author:  bkupe

  ==============================================================================
*/

#include "AutomationKeyframeKeyUI.h"

AutomationKeyframeKeyUI::AutomationKeyframeKeyUI(AutomationKey * key) :
	BaseItemMinimalUI(key)
{
	autoDrawHighlightWhenSelected = false;
}

AutomationKeyframeKeyUI::~AutomationKeyframeKeyUI()
{
}

void AutomationKeyframeKeyUI::paint(Graphics & g)
{
	Colour c = item->isSelected ? Colours::yellow : FRONT_COLOR;
	if (isMouseOver()) c = c.brighter();

	g.setColour(c);
	g.strokePath(keyframePath,PathStrokeType(1));
	g.setColour(c.darker(.2f));
	g.fillPath(keyframePath);
}

void AutomationKeyframeKeyUI::resized()
{
	keyframePath.clear();
	Rectangle<int> r = getLocalBounds().reduced(4);
	keyframePath.addRoundedRectangle(r, 2);
	keyframePath.applyTransform(AffineTransform::translation(-getLocalBounds().getCentre()));
	keyframePath.applyTransform(AffineTransform::rotation(float_Pi / 4));
	keyframePath.applyTransform(AffineTransform::translation(getLocalBounds().getCentre()));
}

void AutomationKeyframeKeyUI::mouseDown(const MouseEvent & e)
{
	BaseItemMinimalUI::mouseDown(e);
	posAtMouseDown = item->position->floatValue();
}

void AutomationKeyframeKeyUI::mouseUp(const MouseEvent & e)
{
	setMouseCursor(MouseCursor::NormalCursor);
}
