/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ExampleManagerUI.h"
#include "ExampleManagerViewUI.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

void MainComponent::init()
{

	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition(ExampleManager::getInstance()->niceName, &ExampleManagerUI::create));
	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition(SequenceManager::getInstance()->niceName, &SequenceManagerUI::create)); 
	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Example View", &ExampleManagerViewUI::create));
	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Sequence Editor", &TimeMachineView::create));

	ShapeShifterManager::getInstance()->setLayoutInformations("exlayout", "OrganicUIExample/layouts");
	ShapeShifterManager::getInstance()->loadDefaultLayoutFile();

	OrganicMainContentComponent::init();
}
