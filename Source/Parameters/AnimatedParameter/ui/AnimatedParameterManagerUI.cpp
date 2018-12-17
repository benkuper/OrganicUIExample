/*
  ==============================================================================

    AnimatedParameterManagerUI.cpp
    Created: 9 Nov 2018 2:02:18pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterManagerUI.h"



AnimatedParameterManagerUI::AnimatedParameterManagerUI(AnimatedParameterManager * manager) : 
	BaseManagerUI("Parameters", manager, false)
{
	addExistingItems();
}

AnimatedParameterManagerUI::~AnimatedParameterManagerUI()
{
}

void AnimatedParameterManagerUI::showMenuAndAddItem(bool, Point<int>)
{
	ControllableChooserPopupMenu chooser(((AnimatedParameterContainer *)(manager->parentContainer.get()))->targetContainer, true, false);

	Parameter * p = dynamic_cast<Parameter *>(chooser.showAndGetControllable());
	if (p != nullptr) manager->addItem(p);
}
