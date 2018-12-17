/*
  ==============================================================================

    AnimatedParameterContainerManagerUI.cpp
    Created: 8 Nov 2018 3:03:28pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainerManagerUI.h"
#include "ExampleManager.h"

AnimatedParameterContainerManagerUI::AnimatedParameterContainerManagerUI(AnimatedParameterContainerManager * manager) :
	BaseManagerUI("Objects", manager, false)
{
	setSize(getWidth(), 150);
	addExistingItems();
}

AnimatedParameterContainerManagerUI::~AnimatedParameterContainerManagerUI()
  {
  }

void AnimatedParameterContainerManagerUI::showMenuAndAddItem(bool, Point<int>)
{
	ContainerChooserPopupMenu chooser(nullptr);
	
	ControllableContainer * cc = chooser.showAndGetContainer();
	if (cc != nullptr) manager->addItem(cc);
}
