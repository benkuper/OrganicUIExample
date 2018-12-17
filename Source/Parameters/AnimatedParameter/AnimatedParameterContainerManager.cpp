/*
  ==============================================================================

    AnimatedParameterContainerManager.cpp
    Created: 8 Nov 2018 2:44:31pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainerManager.h"

AnimatedParameterContainerManager::AnimatedParameterContainerManager() : 
	BaseManager("Objects")
{
}

AnimatedParameterContainerManager::~AnimatedParameterContainerManager()
{
}


void AnimatedParameterContainerManager::addItem(ControllableContainer * target, bool addToUndo)
{
	AnimatedParameterContainer * apc = new AnimatedParameterContainer(target);
	BaseManager::addItem(apc, var(), addToUndo);
}
