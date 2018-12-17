/*
  ==============================================================================

    AnimatedParameterManager.h
    Created: 9 Nov 2018 2:02:25pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AnimatedParameter.h"

class AnimatedParameterManager :
	public BaseManager<AnimatedParameter>
{
public:
	AnimatedParameterManager();
	~AnimatedParameterManager();

	void addItem(Parameter * target, bool addToUndo = true);
};