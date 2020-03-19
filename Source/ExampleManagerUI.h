/*
  ==============================================================================

    ExampleManagerUI.h
    Created: 1 Jun 2018 12:51:36pm
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "ExampleManager.h"

class ExampleManagerUI :
	public BaseManagerShapeShifterUI<ExampleManager, ExampleItem, BaseItemUI<ExampleItem>>
{
public:
	ExampleManagerUI(ExampleManager * m);
	~ExampleManagerUI();

	static ExampleManagerUI * create(const String &name = "") { return new ExampleManagerUI(ExampleManager::getInstance()); }
};