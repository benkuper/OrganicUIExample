/*
  ==============================================================================

    ParametersLayerTimeline.h
    Created: 8 Nov 2018 3:02:46pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../ParametersLayer.h"
#include "../AnimatedParameter/Block/ui/ParametersLayerBlockManagerUI.h"

class ParametersLayerTimeline :
	public SequenceLayerTimeline
{
public:
	ParametersLayerTimeline(ParametersLayer * layer);
	~ParametersLayerTimeline();

	ParametersLayer * parametersLayer;
	std::unique_ptr<ParametersLayerBlockManagerUI> bmUI;

	void resized();
	void updateContent() override;

};