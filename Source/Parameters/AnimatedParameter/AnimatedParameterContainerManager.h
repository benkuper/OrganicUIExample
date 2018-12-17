/*
  ==============================================================================

    AnimatedParameterContainerManager.h
    Created: 8 Nov 2018 2:44:31pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AnimatedParameterContainer.h"

class AnimatedParameterContainerManager :
	public BaseManager<AnimatedParameterContainer>
{
public:
	AnimatedParameterContainerManager();
	~AnimatedParameterContainerManager();


	void addItem(ControllableContainer * target, bool addToUndo = true);
};