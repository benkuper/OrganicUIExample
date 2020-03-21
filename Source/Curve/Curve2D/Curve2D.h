/*
  ==============================================================================

    Curve2D.h
    Created: 21 Mar 2020 4:06:01pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "Curve2DKey.h"

class Curve2D :
    public BaseManager<Curve2DKey>
{
public:
    Curve2D(const String &name = "Curve 2D");
    ~Curve2D();

    FloatParameter* length;

    //ui
    bool showUIInEditor;


    void addItemInternal(Curve2DKey* k, var params) override;
    void removeItemInternal(Curve2DKey* k) override;

    void updateCurve();
    void onControllableFeedbackUpdate(ControllableContainer* cc, Controllable* c) override;

    void afterLoadJSONDataInternal() override;

    InspectableEditor* getEditor(bool isRoot) override;
};