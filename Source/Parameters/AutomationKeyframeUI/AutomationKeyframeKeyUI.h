/*
  ==============================================================================

    AutomationKeyframeKeyUI.h
    Created: 18 Dec 2018 11:24:23am
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class AutomationKeyframeKeyUI :
	public BaseItemMinimalUI<AutomationKey>
{
public:
	AutomationKeyframeKeyUI(AutomationKey * key);
	~AutomationKeyframeKeyUI();


	float posAtMouseDown;


	Path keyframePath;

	void paint(Graphics &g) override;
	void resized();

	void mouseDown(const MouseEvent &e) override;
	void mouseUp(const MouseEvent &e) override;
};