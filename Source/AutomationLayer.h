/*
  ==============================================================================

    AutomationLayer.h
    Created: 4 Dec 2019 12:45:51pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class AutomationLayer :
public SequenceLayer
{
public:
	AutomationLayer(Sequence * s, var params);
	~AutomationLayer();

	Automation automation;

	SequenceLayerTimeline* getTimelineUI() override;

	void selectAll(bool addToSelection = false) override;

	void sequenceCurrentTimeChanged(Sequence* s, float prevTime, bool seeking) override;
	void sequenceTotalTimeChanged(Sequence* s) override;

	String getTypeString() const override { return "Automation"; }
	static AutomationLayer* create(Sequence* s, var params) { return new AutomationLayer(s, params); }
};