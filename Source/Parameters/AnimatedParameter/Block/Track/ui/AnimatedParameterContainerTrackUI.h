/*
  ==============================================================================

    AnimatedParameterContainerTrackUI.h
    Created: 8 Nov 2018 2:59:27pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterContainerTrack.h"

class AnimatedParameterContainerTrackUI :
	public Component
{
public:
	AnimatedParameterContainerTrackUI(AnimatedParameterContainerTrack *containerTrack);
	~AnimatedParameterContainerTrackUI();

	AnimatedParameterContainerTrack * containerTrack;

	void paint(Graphics &g) override;
};