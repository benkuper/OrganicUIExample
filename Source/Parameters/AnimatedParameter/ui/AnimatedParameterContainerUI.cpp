/*
  ==============================================================================

    AnimatedParameterContainerUI.cpp
    Created: 8 Nov 2018 3:03:34pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainerUI.h"

AnimatedParameterContainerUI::AnimatedParameterContainerUI(AnimatedParameterContainer * item) :
	BaseItemUI(item, ResizeMode::VERTICAL, true),
	parameterManagerUI(&item->parameterManager)
{
	addAndMakeVisible(&parameterManagerUI);
	setSize(getWidth(), 150);
}

AnimatedParameterContainerUI::~AnimatedParameterContainerUI()
{
}

void AnimatedParameterContainerUI::resizedInternalContent(Rectangle<int>& r)
{
	if (r.getWidth() == 0 || r.getHeight() == 0) return;
	if (r.getHeight() == parameterManagerUI.getHeight()) return;

	//DBG(parameterManagerUI.getBounds().toString() << " > " << r.toString());
	parameterManagerUI.setBounds(r);
}

void AnimatedParameterContainerUI::childBoundsChanged(Component * c)
{
	/*if (c == &parameterManagerUI)
	{
		if (isShowing()) setContentSize(getWidth() - margin * 2, jmax(parameterManagerUI.getHeight(), parameterManagerUI.minHeight));
	}*/
}
