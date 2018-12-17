/*
  ==============================================================================

    AnimatedParameterContainer.h
    Created: 8 Nov 2018 2:44:41pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AnimatedParameterManager.h"

class AnimatedParameterContainer :
	public BaseItem
{
public:
	AnimatedParameterContainer(WeakReference<ControllableContainer> targetContainer = nullptr);
	~AnimatedParameterContainer();

	AnimatedParameterManager parameterManager;

	WeakReference<ControllableContainer> targetContainer;

	void addItem(ControllableContainer * target, bool addToUndo = true);
};