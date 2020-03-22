/*
  ==============================================================================

    ExampleEngine.cpp
    Created: 1 Jun 2018 12:48:01pm
    Author:  Ben

  ==============================================================================
*/

#include "ExampleEngine.h"
#include "ExampleManager.h"
#include "ExampleSequence.h"
#include "Helpers/KeyboardUtil.h"

ExampleEngine::ExampleEngine() :
	Engine("Example File",".example")
{
	mainEngine = this;
	addChildControllableContainer(ExampleManager::getInstance());
	addChildControllableContainer(SequenceManager::getInstance());
	
	SequenceManager::getInstance()->managerFactory = &sequenceFactory;
	sequenceFactory.defs.add(new Factory<Sequence>::Definition("", "Sequence", ExampleSequence::create));

	KeyboardUtil::getInstance();
}

ExampleEngine::~ExampleEngine()
{
	ExampleManager::deleteInstance();
	SequenceManager::deleteInstance();
	KeyboardUtil::deleteInstance();
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
