/*
  ==============================================================================

    Curve2DKey.h
    Created: 21 Mar 2020 4:06:25pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "easing/Curve2DEasing.h"

class Curve2DKey :
    public BaseItem,
    public Inspectable::InspectableListener
{
public:
    Curve2DKey();
    ~Curve2DKey();

    EnumParameter* easingType;
    std::unique_ptr<Easing2D> easing;
    Curve2DKey* nextKey;

    Point2DParameter* position;
    float curvePosition; //position on the curve, calculated by the curve to distribute evenly the points

    void setEasing(Easing2D::Type type);
    void setNextKey(Curve2DKey* key);

    Point<float> getValueAt(const float &position);
    float getLength() const;

    void onContainerParameterChangedInternal(Parameter* p) override;

    void inspectableDestroyed(Inspectable* i) override;

    String getTypeString() const override { return "2DKey"; }
};