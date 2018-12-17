/*
  ==============================================================================

    AnimatedParameterContainerUI.h
    Created: 8 Nov 2018 3:03:34pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../AnimatedParameterContainer.h"
#include "AnimatedParameterManagerUI.h"

class AnimatedParameterContainerUI :
	public BaseItemUI<AnimatedParameterContainer>
{ 
public:
	AnimatedParameterContainerUI(AnimatedParameterContainer * item);
	~AnimatedParameterContainerUI();
	
	AnimatedParameterManagerUI parameterManagerUI;

	void resizedInternalContent(Rectangle<int> &r) override;

	void childBoundsChanged(Component * c) override;
};