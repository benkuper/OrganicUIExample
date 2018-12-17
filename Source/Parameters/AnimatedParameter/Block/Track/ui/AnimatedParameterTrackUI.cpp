/*
  ==============================================================================

    AnimatedParameterTrackUI.cpp
    Created: 8 Nov 2018 2:59:37pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterTrackUI.h"

AnimatedParameterTrackUI::AnimatedParameterTrackUI(AnimatedParameterTrack * track) :
	track(track)
{
}

AnimatedParameterTrackUI::~AnimatedParameterTrackUI()
  {
  }

void AnimatedParameterTrackUI::paint(Graphics & g)
{
	g.fillAll(Colours::orange.withAlpha(.5f));
}
