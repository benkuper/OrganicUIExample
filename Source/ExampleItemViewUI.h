/*
  ==============================================================================

    ExampleItemViewUI.h
    Created: 4 Apr 2019 1:55:23pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "ExampleItem.h"

class ExampleItemViewUI :
	public BaseItemUI<ExampleItem>
{
public:
	ExampleItemViewUI(ExampleItem * item);
	~ExampleItemViewUI();
};