/*
  ==============================================================================

    ExampleEngine.cpp
    Created: 1 Jun 2018 12:48:01pm
    Author:  Ben

  ==============================================================================
*/

#include "ExampleEngine.h"
#include "ExampleManager.h"
#include "AutomationLayer.h"
#include "Parameters/ParametersLayer.h"

ExampleEngine::ExampleEngine() :
	Engine("Example File",".example")
{
	mainEngine = this;
	addChildControllableContainer(ExampleManager::getInstance());
	addChildControllableContainer(SequenceManager::getInstance());

	//SequenceLayerFactory::getInstance()->layerDefs.add(SequenceLayerDefinition::createDef("Automation", &AutomationLayer::create));
	SequenceLayerFactory::getInstance()->layerDefs.add(SequenceLayerDefinition::createDef("Parameters", &ParametersLayer::create));
}

ExampleEngine::~ExampleEngine()
{
	ExampleManager::deleteInstance();
	SequenceManager::deleteInstance();
}

var ExampleEngine::getJSONData()
{
	var data = Engine::getJSONData();
	data.getDynamicObject()->setProperty("manager", ExampleManager::getInstance()->getJSONData());
	data.getDynamicObject()->setProperty("sequences", SequenceManager::getInstance()->getJSONData());
	return data;
}

void ExampleEngine::loadJSONDataInternalEngine(var data, ProgressTask *)
{
	ExampleManager::getInstance()->loadJSONData(data.getProperty("manager", var()));
	SequenceManager::getInstance()->loadJSONData(data.getProperty("sequences", var()));
}
