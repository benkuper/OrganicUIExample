/*
  ==============================================================================

    AnimatedParameterManager.cpp
    Created: 9 Nov 2018 2:02:25pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterManager.h"

AnimatedParameterManager::AnimatedParameterManager() :
	BaseManager("Parameters")
{
}	

AnimatedParameterManager::~AnimatedParameterManager()
{
}

void AnimatedParameterManager::addItem(Parameter * target, bool addToUndo)
{
	AnimatedParameter * ap = new AnimatedParameter(target);
	BaseManager::addItem(ap, var(), addToUndo);
}
