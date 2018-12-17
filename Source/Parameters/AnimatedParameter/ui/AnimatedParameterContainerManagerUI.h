/*
  ==============================================================================

    AnimatedParameterContainerManagerUI.h
    Created: 8 Nov 2018 3:03:28pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterContainerManager.h"
#include "AnimatedParameterContainerUI.h"

class AnimatedParameterContainerManagerUI :
	public BaseManagerUI<AnimatedParameterContainerManager, AnimatedParameterContainer, AnimatedParameterContainerUI>
{
public:
	AnimatedParameterContainerManagerUI(AnimatedParameterContainerManager * manager);
	~AnimatedParameterContainerManagerUI();


	void showMenuAndAddItem(bool, Point<int>) override;
};