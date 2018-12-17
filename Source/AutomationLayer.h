/*
  ==============================================================================

    AutomationLayer.h
    Created: 25 Oct 2018 10:18:28am
    Author:  Ben

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

	virtual SequenceLayerPanel * getPanel() override;
	virtual SequenceLayerTimeline * getTimelineUI() override;

	void sequenceCurrentTimeChanged(Sequence *, float prevTime, bool evaluatedSkippedData) override;
	void sequenceTotalTimeChanged(Sequence *) override;
	void sequencePlayStateChanged(Sequence *) override;

	static AutomationLayer * create(Sequence * sequence, var params) { return new AutomationLayer(sequence, params); }
	virtual String getTypeString() const override { return "Automation"; }

};
