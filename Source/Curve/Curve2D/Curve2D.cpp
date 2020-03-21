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
    editorCanBeCollapsed = false;
    showInspectorOnSelect = false;
    userCanAddItemsManually = false;
    canInspectChildContainers = false;

    length = addFloatParameter("Length", "The length of the curve", 0, 0);
    length->hideInEditor = true;
    length->setControllableFeedbackOnly(true);
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

