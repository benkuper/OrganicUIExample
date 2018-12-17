/*
  ==============================================================================

    AnimatedParameterManagerUI.h
    Created: 9 Nov 2018 2:02:18pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterManager.h"
#include "AnimatedParameterUI.h"

class AnimatedParameterManagerUI :
	public BaseManagerUI<AnimatedParameterManager, AnimatedParameter, AnimatedParameterUI>
{
public:
	AnimatedParameterManagerUI(AnimatedParameterManager * manager);
	~AnimatedParameterManagerUI();

	void showMenuAndAddItem(bool, Point<int>) override;

};