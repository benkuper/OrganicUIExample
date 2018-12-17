/*
  ==============================================================================

    AnimatedParameterContainer.cpp
    Created: 8 Nov 2018 2:44:41pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainer.h"

AnimatedParameterContainer::AnimatedParameterContainer(WeakReference<ControllableContainer> targetContainer) :
	BaseItem(targetContainer == nullptr?"No object":targetContainer->niceName),
	targetContainer(targetContainer)
{
	addChildControllableContainer(&parameterManager);

	if (targetContainer != nullptr)
	{
		for (auto &c : targetContainer->controllables)
		{
			if (c->isTargettable && c->type == Controllable::FLOAT)
			{
				parameterManager.addItem((Parameter *)c, true);
			}
		}
	}
}

AnimatedParameterContainer::~AnimatedParameterContainer()
{
}
