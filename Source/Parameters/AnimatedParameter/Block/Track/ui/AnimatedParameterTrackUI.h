/*
  ==============================================================================

    AnimatedParameterTrackUI.h
    Created: 8 Nov 2018 2:59:37pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterTrack.h"

class AnimatedParameterTrackUI :
	public Component
{
public:
	AnimatedParameterTrackUI(AnimatedParameterTrack * track);
	~AnimatedParameterTrackUI();

	AnimatedParameterTrack * track;

	void paint(Graphics &g) override;
};