/*
  ==============================================================================

    Curve2DKey.cpp
    Created: 21 Mar 2020 4:06:25pm
    Author:  bkupe

  ==============================================================================
*/

#include "Curve2DKey.h"

Curve2DKey::Curve2DKey() :
    BaseItem(getTypeString(), false, false),
    easing(nullptr),
    curvePosition(0),
    nextKey(nullptr),
    keyNotifier(5)
{
    showInspectorOnSelect = false;

    easingType = addEnumParameter("Easing Type", "The type of interpolation to use");
    easingType->addOption("Linear", Easing2D::LINEAR, false)->addOption("Bezier", Easing2D::BEZIER);

    easingType->setValueWithData(Easing2D::BEZIER);

    position = addPoint2DParameter("Position", "The position of the key");
}

Curve2DKey::~Curve2DKey()
{
    setNextKey(nullptr);
    masterReference.clear();
}

void Curve2DKey::setEasing(Easing2D::Type type)
{
    if (easing != nullptr)
    {
        if (easing->type == type) return;
        removeChildControllableContainer(easing.get());
    }

    Easing2D* e = nullptr;
    switch (type)
    {
    case Easing2D::LINEAR: e = new LinearEasing2D(); break;
    case Easing2D::BEZIER: e = new CubicEasing2D(); break;
    default:
        break;
    }

    easing.reset(e);

    if (e != nullptr)
    {
        addChildControllableContainer(easing.get());
    }

    updateEasingKeys();
}

void Curve2DKey::setNextKey(Curve2DKey* key)
{
    if (nextKey == key) return;

    if (nextKey != nullptr)
    {
        nextKey->removeInspectableListener(this);
        nextKey->position->removeParameterListener(this);

    }

    Curve2DKey* oldNextkey = nextKey;

    nextKey = key;

    if (nextKey != nullptr)
    {
        nextKey->addInspectableListener(this);
        nextKey->position->addParameterListener(this);
        updateEasingKeys();
    }

    keyNotifier.addMessage(new Curve2DKeyEvent(Curve2DKeyEvent::NEXTKEY_CHANGED, this, oldNextkey));
}

Point<float> Curve2DKey::getValueAt(const float& _position)
{
    if (easing == nullptr && easing->length > 0) return position->getPoint();
    return easing->getValue(_position / easing->length);
}

float Curve2DKey::getLength() const
{
    return easing != nullptr ? easing->length : 0;
}

void Curve2DKey::onContainerParameterChangedInternal(Parameter* p)
{
    BaseItem::onContainerParameterChangedInternal(p);
    if (p == easingType)
    {
        setEasing(easingType->getValueDataAsEnum<Easing2D::Type>());
    }
    else if (p == position)
    {
        updateEasingKeys();
    }
}

void Curve2DKey::onExternalParameterValueChanged(Parameter* p)
{
    BaseItem::onExternalParameterValueChanged(p);
    if (nextKey != nullptr && p == nextKey->position)
    {
        updateEasingKeys();
    }
}

void Curve2DKey::onControllableFeedbackUpdateInternal(ControllableContainer* cc, Controllable* c)
{
    if (cc == easing.get()) notifyKeyUpdated();
}

void Curve2DKey::inspectableDestroyed(Inspectable* i)
{
    if (i == nextKey) setNextKey(nullptr);
}

void Curve2DKey::updateEasingKeys()
{
    if (easing != nullptr && nextKey != nullptr)
    {
        easing->updateKeys(position->getPoint(), nextKey->position->getPoint());  notifyKeyUpdated();
    }

    notifyKeyUpdated();
}

void Curve2DKey::notifyKeyUpdated()
{
    keyNotifier.addMessage(new Curve2DKeyEvent(Curve2DKeyEvent::KEY_UPDATED, this));
}
