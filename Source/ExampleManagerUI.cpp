/*
  ==============================================================================

    ExampleManagerUI.cpp
    Created: 1 Jun 2018 12:51:36pm
    Author:  Ben

  ==============================================================================
*/

#include "ExampleManagerUI.h"

ExampleManagerUI::ExampleManagerUI(ExampleManager * m) :
	BaseManagerShapeShifterUI(m->niceName,m)
{
	addExistingItems();

}

ExampleManagerUI::~ExampleManagerUI()
{
}
