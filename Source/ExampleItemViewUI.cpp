/*
  ==============================================================================

    ExampleItemViewUI.cpp
    Created: 4 Apr 2019 1:55:23pm
    Author:  bkupe

  ==============================================================================
*/

#include "ExampleItemViewUI.h"

ExampleItemViewUI::ExampleItemViewUI(ExampleItem * item) :
	BaseItemUI(item, Direction::ALL)
{
	setSize(100, 100);
	autoHideWhenDragging = false;
	drawEmptyDragIcon = true;
}

ExampleItemViewUI::~ExampleItemViewUI()
{
}
