/*
  ==============================================================================

    AnimatedParameterUI.h
    Created: 8 Nov 2018 3:03:00pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterContainer.h"


class AnimatedParameterUI :
	public BaseItemUI<AnimatedParameter>
{
public:
	AnimatedParameterUI(AnimatedParameter * item);
	~AnimatedParameterUI();

};