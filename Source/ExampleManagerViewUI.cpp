/*
  ==============================================================================

    ExampleManagerViewUI.cpp
    Created: 4 Apr 2019 1:55:13pm
    Author:  bkupe

  ==============================================================================
*/

#include "ExampleManagerViewUI.h"

ExampleManagerViewUI::ExampleManagerViewUI(ExampleManager * manager) :
	BaseManagerShapeShifterViewUI("Example View",manager)
  {
	updatePositionOnDragMove = true;
	enableSnapping = true;
  }

  ExampleManagerViewUI::~ExampleManagerViewUI()
  {
  }
