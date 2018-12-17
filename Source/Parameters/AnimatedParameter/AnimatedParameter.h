/*
  ==============================================================================

    AnimatedParameter.h
    Created: 8 Nov 2018 2:44:46pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class AnimatedParameter :
	public BaseItem
{
public:
	AnimatedParameter(WeakReference<Parameter> target = nullptr);
	~AnimatedParameter();

	WeakReference<Parameter> target;
};