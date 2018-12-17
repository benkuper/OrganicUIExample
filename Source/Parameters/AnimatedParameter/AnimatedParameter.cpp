/*
  ==============================================================================

    AnimatedParameter.cpp
    Created: 8 Nov 2018 2:44:46pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameter.h"

AnimatedParameter::AnimatedParameter(WeakReference<Parameter> target) :
	BaseItem(target == nullptr?"No target":target->niceName, false),
	target(target)
{
	
}

AnimatedParameter::~AnimatedParameter()
  {
  }
