/*
  ==============================================================================

    ExampleSequence.cpp
    Created: 17 Jul 2019 7:07:45pm
    Author:  bkupe

  ==============================================================================
*/

#include "ExampleSequence.h"
#include "BlockLayer.h"
#include "AutomationLayer.h"

ExampleSequence::ExampleSequence() :
	Sequence()
{
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Automation", AutomationLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Automation 2D", AutomationLayer::create, this)->addParam("dimensions",2));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Automation 3D", AutomationLayer::create, this)->addParam("dimensions",3));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Blocks", BlockLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Trigger", TriggerLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Audio", AudioLayer::create, this));
}
