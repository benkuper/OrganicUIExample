/*
  ==============================================================================

    ParametersLayer.h
    Created: 8 Nov 2018 2:43:52pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AnimatedParameter/AnimatedParameterContainerManager.h"

class ParametersLayerBlockManager;

class ParametersLayer :
	public SequenceLayer
{
public:
	ParametersLayer(Sequence * s, var params);
	~ParametersLayer();

	AnimatedParameterContainerManager apcm;
	ScopedPointer<ParametersLayerBlockManager> blockManager;

	virtual SequenceLayerPanel * getPanel() override;
	virtual SequenceLayerTimeline * getTimelineUI() override;

	void sequenceCurrentTimeChanged(Sequence *, float prevTime, bool evaluatedSkippedData) override;
	void sequenceTotalTimeChanged(Sequence *) override;
	void sequencePlayStateChanged(Sequence *) override;

	static ParametersLayer * create(Sequence * sequence, var params) { return new ParametersLayer(sequence, params); }
	virtual String getTypeString() const override { return "Parameters"; }

};