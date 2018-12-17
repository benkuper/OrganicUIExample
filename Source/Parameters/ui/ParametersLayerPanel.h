/*
  ==============================================================================

    ParametersLayerPanel.h
    Created: 8 Nov 2018 3:02:41pm
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "../ParametersLayer.h"
#include "../AnimatedParameter/ui/AnimatedParameterContainerManagerUI.h"

class ParametersLayerPanel :
	public SequenceLayerPanel
{
public:
	ParametersLayerPanel(ParametersLayer * layer);
	~ParametersLayerPanel();

	ParametersLayer * parametersLayer;
	AnimatedParameterContainerManagerUI managerUI;

	void resizedInternalContent(Rectangle<int> &r) override;

	Rectangle<int> getParameterBounds(AnimatedParameter * p);
	Rectangle<int> getContainerBounds(AnimatedParameterContainer * c);
};