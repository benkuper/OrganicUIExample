/*
  ==============================================================================

    Curve2D.cpp
    Created: 21 Mar 2020 4:06:01pm
    Author:  bkupe

  ==============================================================================
*/

#include "Curve2D.h"
#include "ui/Curve2DEditor.h"


Curve2D::Curve2D(const String &name) :
    BaseManager(name),
    showUIInEditor(true)
{
    isSelectable = false;

    editorCanBeCollapsed = false;
    showInspectorOnSelect = false;
    userCanAddItemsManually = false;
    canInspectChildContainers = false;

    length = addFloatParameter("Length", "The length of the curve", 0, 0);
    length->hideInEditor = true;
    length->setControllableFeedbackOnly(true);

    position = addFloatParameter("Position", "The length of the curve", 0, 0, 1);
    position->hideInEditor = true;
   
    value = addPoint2DParameter("Value", "The current value of the curve at the current position");
    value->hideInEditor = true;
    value->setControllableFeedbackOnly(true);

}

Curve2D::~Curve2D()
{

}

void Curve2D::addItemInternal(Curve2DKey*, var)
{
    updateCurve();
}

void Curve2D::removeItemInternal(Curve2DKey*)
{
    updateCurve();
}

void Curve2D::updateCurve()
{
    if (isCurrentlyLoadingData || Engine::mainEngine->isClearing) return;

    float curLength = 0;

    int numItems = items.size();
    for (int i = 0; i < numItems; i++)
    {
        if (i < numItems - 1) items[i]->setNextKey(items[i + 1]);
        items[i]->curvePosition = curLength;
        curLength += items[i]->getLength();
    }

    length->setValue(curLength);

    computeValue();
}

void Curve2D::computeValue()
{
    value->setPoint(getValueAtPosition(position->floatValue() * length->floatValue()));
}

Curve2DKey* Curve2D::getKeyForPosition(float pos)
{
    if (items.size() == 0) return nullptr;
    if (pos == 0) return items[0];

    for (int i = items.size()-1; i >= 0; i--)
    {
        if (items[i]->curvePosition <= pos) return items[i];
    }

    return nullptr;
}

Point<float> Curve2D::getValueAtPosition(float pos)
{
    if (items.size() == 0) return Point<float>();
    if (items.size() == 1) return items[0]->position->getPoint();
    if (pos == length->floatValue())  return items[items.size() - 1]->position->getPoint();

    Curve2DKey* k = getKeyForPosition(pos);
    if (k == nullptr || k->easing == nullptr) return Point<float>();
    float normPos = (pos - k->curvePosition) / k->getLength();
    return k->easing->getValue(normPos);
}

void Curve2D::onContainerParameterChanged(Parameter* p)
{
    BaseManager::onContainerParameterChanged(p);
    if (p == position)
    {
        computeValue();
    }
}

void Curve2D::onControllableFeedbackUpdate(ControllableContainer* cc, Controllable* c)
{
    BaseManager::onControllableFeedbackUpdate(cc, c);
    
    if (Curve2DKey* k = dynamic_cast<Curve2DKey*>(cc))
    {
        updateCurve();
    }
}

void Curve2D::afterLoadJSONDataInternal()
{
    updateCurve();
}

InspectableEditor* Curve2D::getEditor(bool isRoot)
{
    return new Curve2DEditor(this, isRoot);
}

