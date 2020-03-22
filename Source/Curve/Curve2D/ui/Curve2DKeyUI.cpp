/*
  ==============================================================================

	Curve2DKeyUI.cpp
	Created: 21 Mar 2020 4:06:36pm
	Author:  bkupe

  ==============================================================================
*/

#include "Curve2DKeyUI.h"
#include "../easing/ui/Easing2DUI.h"

Curve2DKeyUI::Curve2DKeyUI(Curve2DKey* key) :
	BaseItemMinimalUI(key),
	handle(key),
	easingUI(nullptr)
{
	autoDrawContourWhenSelected = false;
	dragAndDropEnabled = false;

	addAndMakeVisible(&handle);

	if (item->nextKey != nullptr) item->nextKey->addInspectableListener(this);
	updateEasingUI();
}

Curve2DKeyUI::~Curve2DKeyUI()
{
	if (!inspectable.wasObjectDeleted())
	{
		if (item->easing != nullptr) item->easing->removeInspectableListener(this);
		if (item->nextKey != nullptr)
		{
			item->nextKey->removeInspectableListener(this);
			if (item->nextKey->easing != nullptr) item->nextKey->easing->removeInspectableListener(this);
		}
	}

}

void Curve2DKeyUI::resized()
{
	Point<int> hp = getUIPosForValuePos(item->position->getPoint());
	const int handleSize = 14;
	handle.setBounds(Rectangle<int>(hp.x - handleSize / 2, hp.y - handleSize / 2, handleSize, handleSize));
	if (easingUI != nullptr) easingUI->setBounds(getLocalBounds());
}

void Curve2DKeyUI::paint(Graphics& g)
{
	//g.fillAll(Colours::orange.withAlpha(.05f));
}

void Curve2DKeyUI::setShowEasingHandles(bool showFirst, bool showLast)
{
	if (inspectable.wasObjectDeleted()) return;
	if (easingUI != nullptr) easingUI->setShowEasingHandles(showFirst, showLast);
}

void Curve2DKeyUI::updateEasingUI()
{
	if (easingUI != nullptr)
	{
		removeChildComponent(this);
	}

	if (item->easing == nullptr)
	{
		easingUI.reset();
		return;
	}

	easingUI.reset(item->easing->createUI());

	if (easingUI != nullptr)
	{
		addAndMakeVisible(easingUI.get(), 0);
		easingUI->setBounds(getLocalBounds());
		easingUI->setValueBounds(valueBounds);
	}

}

bool Curve2DKeyUI::hitTest(int x, int y)
{
	if (handle.getBounds().contains(x, y)) return true;
	if (easingUI != nullptr && easingUI->hitTest(x, y)) return true;
	return false;
}

void Curve2DKeyUI::setValueBounds(const Rectangle<float> _valueBounds)
{
	valueBounds = _valueBounds;
	if (easingUI != nullptr) easingUI->setValueBounds(valueBounds);
	resized();
}


Point<int> Curve2DKeyUI::getUIPosForValuePos(const Point<float>& valuePos) const
{
	return getLocalBounds().getRelativePoint((valuePos.x - valueBounds.getX()) / valueBounds.getWidth(), (valuePos.y - valueBounds.getY()) / valueBounds.getHeight());
}


void Curve2DKeyUI::controllableFeedbackUpdateInternal(Controllable* c)
{
	if (c == item->easingType) updateEasingUI();
	else if (CubicEasing2D* ce = dynamic_cast<CubicEasing2D*>(c->parentContainer.get()))
	{
		if (c == ce->anchor1 || c == ce->anchor2)
		{
			keyUIListeners.call(&KeyUIListener::keyEasingHandleMoved, this, true, c == ce->anchor1);
		}
	}
}

bool Curve2DKeyUI::keyPressed(const KeyPress& key, Component* originatingComponent)
{
	LOG("Key pressed : " << key.getTextDescriptionWithIcons());
	return false;
}

Curve2DKeyHandle::Curve2DKeyHandle(Curve2DKey* key) :
	InspectableContentComponent(key),
	key(key)
{
	autoDrawContourWhenSelected = false;
	setRepaintsOnMouseActivity(true);

}

Curve2DKeyHandle::~Curve2DKeyHandle()
{
}

void Curve2DKeyHandle::paint(Graphics& g)
{
	if (inspectable.wasObjectDeleted()) return;

	Colour c = key->isSelected ? HIGHLIGHT_COLOR : NORMAL_COLOR;
	if (isMouseOverOrDragging()) c = c.brighter(.2f);

	Rectangle<float> r = getLocalBounds().reduced(3).toFloat();
	g.setColour(c);
	g.fillEllipse(r);
	g.setColour(c.darker());
	g.drawEllipse(r, 1);
}

void Curve2DKeyHandle::inspectableSelectionChanged(Inspectable* i)
{
	repaint();
}
