/*
  ==============================================================================

    AnimatedParameterTrackUI.cpp
    Created: 8 Nov 2018 2:59:37pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterTrackUI.h"

AnimatedParameterTrackUI::AnimatedParameterTrackUI(AnimatedParameterTrack * track) :
	track(track),
	kui(&track->automation)
{
	addAndMakeVisible(&kui);
}

AnimatedParameterTrackUI::~AnimatedParameterTrackUI()
  {
  }

void AnimatedParameterTrackUI::paint(Graphics & g)
{
	g.fillAll(BG_COLOR.brighter(.2f));
}

void AnimatedParameterTrackUI::resized()
{
	kui.setBounds(getLocalBounds());
}
