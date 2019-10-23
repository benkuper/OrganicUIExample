/*
  ==============================================================================

    ExampleManagerViewUI.h
    Created: 4 Apr 2019 1:55:13pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "ExampleItemViewUI.h"
#include "ExampleManager.h"

class ExampleManagerViewUI :
	public BaseManagerShapeShifterViewUI<ExampleManager, ExampleItem, ExampleItemViewUI>
{
public:
	ExampleManagerViewUI(ExampleManager * manager);
	~ExampleManagerViewUI();


	static ExampleManagerViewUI * create(const String &name = "") { return new ExampleManagerViewUI(ExampleManager::getInstance()); }
};