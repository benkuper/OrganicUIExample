/*
  ==============================================================================

    Mapping2DLayerPanel.cpp
    Created: 23 Mar 2020 5:18:05pm
    Author:  bkupe

  ==============================================================================
*/

#include "Mapping2DLayerPanel.h"

Mapping2DLayerPanel::Mapping2DLayerPanel(Mapping2DLayer* layer) :
     SequenceLayerPanel(layer),
     mappingLayer(layer)
{
    keySyncUI.reset(mappingLayer->curve.keySyncMode->createToggle());
    addAndMakeVisible(keySyncUI.get());
}

Mapping2DLayerPanel::~Mapping2DLayerPanel()
{
}

void Mapping2DLayerPanel::resizedInternalContent(Rectangle<int>& r)
{
    SequenceLayerPanel::resizedInternalContent(r);
    r.removeFromTop(4);
    keySyncUI->setBounds(r.removeFromTop(16));
}
