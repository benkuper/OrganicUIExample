/*
  ==============================================================================

    Curve2DUI.h
    Created: 21 Mar 2020 4:06:30pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../Curve2D.h"
#include "Curve2DKeyUI.h"

class Curve2DUI :
    public BaseManagerViewUI<Curve2D, Curve2DKey, Curve2DKeyUI>,
    public Curve2DKeyUI::AsyncListener
{
public:
    Curve2DUI(Curve2D * manager);
    ~Curve2DUI();

    void updateViewUIPosition(Curve2DKeyUI * ui) override;
    void mouseDoubleClick(const MouseEvent& e) override;

    void addItemUIInternal(Curve2DKeyUI* ui) override;
    void removeItemUIInternal(Curve2DKeyUI* ui) override;

    void mouseDrag(const MouseEvent& e) override;

    void newMessage(const Curve2DKeyUI::Curve2DKeyUIEvent& e) override;

};