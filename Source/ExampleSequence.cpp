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
#include "Timeline/Mapping2D/Mapping2DLayer.h"

ExampleSequence::ExampleSequence() :
	Sequence()
{
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Mapping", AutomationLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Mapping 2D", Mapping2DLayer::create, this));
	//layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Automation 3D", AutomationLayer::create, this)->addParam("dimensions",3));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Blocks", BlockLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Trigger", TriggerLayer::create, this));
	layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Audio", AudioLayer::create, this));
}
