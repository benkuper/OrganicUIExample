/*
  ==============================================================================

    KeyboardUtil.h
    Created: 22 Mar 2020 3:49:20pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KeyboardUtil
{
public:

    juce_DeclareSingleton(KeyboardUtil, true);

    KeyboardUtil();
    ~KeyboardUtil();
};