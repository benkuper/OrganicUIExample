/*
  ==============================================================================

    Mapping2DLayerPanel.h
    Created: 23 Mar 2020 5:18:05pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../Mapping2DLayer.h"

class Mapping2DLayerPanel :
    public SequenceLayerPanel
{
public:
    Mapping2DLayerPanel(Mapping2DLayer* layer);
    ~Mapping2DLayerPanel();

    Mapping2DLayer* mappingLayer;

    std::unique_ptr<BoolToggleUI> keySyncUI;

    void resizedInternalContent(Rectangle<int>& r) override;
};