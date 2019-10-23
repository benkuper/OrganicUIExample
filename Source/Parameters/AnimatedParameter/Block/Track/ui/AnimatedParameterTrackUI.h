/*
  ==============================================================================

    AnimatedParameterTrackUI.h
    Created: 8 Nov 2018 2:59:37pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterTrack.h"
#include "../../../../AutomationKeyframeUI/AutomationKeyframeUI.h"

class AnimatedParameterTrackUI :
	public Component
{
public:
	AnimatedParameterTrackUI(AnimatedParameterTrack * track);
	~AnimatedParameterTrackUI();

	AnimatedParameterTrack * track;
	AutomationKeyframeUI kui;

	void paint(Graphics &g) override;
	void resized() override;
};