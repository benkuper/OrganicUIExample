/*
  ==============================================================================

    Curve2DKeyUI.cpp
    Created: 21 Mar 2020 4:06:36pm
    Author:  bkupe

  ==============================================================================
*/

#include "Curve2DKeyUI.h"

Curve2DKeyUI::Curve2DKeyUI(Curve2DKey* key) :
    BaseItemMinimalUI(key),
    handle(key)
{
    autoDrawContourWhenSelected = false;
    dragAndDropEnabled = false;

    addAndMakeVisible(&handle);
}

Curve2DKeyUI::~Curve2DKeyUI()
{
}

void Curve2DKeyUI::resized()
{
    Point<int> hp = getUIPosForValuePos(item->position->getPoint());
    const int handleSize = 12;
    handle.setBounds(Rectangle<int>(hp.x - handleSize / 2, hp.y - handleSize / 2, handleSize, handleSize));
}

void Curve2DKeyUI::paint(Graphics& g)
{
    g.fillAll(Colours::orange.withAlpha(.05f));
   // Colour c = item->isSelected ? highlightColor : bgColor;
}

void Curve2DKeyUI::setValueBounds(const Rectangle<float> _valueBounds)
{
    valueBounds = _valueBounds;
    resized();
}


Point<int> Curve2DKeyUI::getUIPosForValuePos(const Point<float>& valuePos) const
{
   return getLocalBounds().getRelativePoint((valuePos.x - valueBounds.getX()) / valueBounds.getWidth(), (valuePos.y - valueBounds.getY()) / valueBounds.getHeight());
}

Curve2DKeyHandle::Curve2DKeyHandle(Curve2DKey* key) :
    InspectableContentComponent(key),
    key(key)
{
}

Curve2DKeyHandle::~Curve2DKeyHandle()
{
}

void Curve2DKeyHandle::paint(Graphics& g)
{
    if (inspectable.wasObjectDeleted()) return;

    Colour c = key->isSelected ? highlightColor : NORMAL_COLOR;
    if (isMouseOverOrDragging()) c = c.brighter(.2f);

    Rectangle<float> r = getLocalBounds().reduced(2).toFloat();
    g.setColour(c);
    g.fillEllipse(r);
    g.setColour(c.darker());
    g.drawEllipse(r, 1);
}

void Curve2DKeyHandle::inspectableSelectionChanged(Inspectable* i)
{
    repaint();
}
