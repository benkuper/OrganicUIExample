/*
  ==============================================================================

    Mapping2DLayerLayer.h
    Created: 23 Mar 2020 5:17:47pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "../../Curve/Curve2D/Curve2D.h"

class Mapping2DLayer :
	public SequenceLayer
{
public:
	Mapping2DLayer(Sequence* s, var params);
	~Mapping2DLayer();

	Curve2D curve;
	Automation * automation;


	SequenceLayerPanel* getPanel() override;
	SequenceLayerTimeline* getTimelineUI() override;

	void selectAll(bool addToSelection = false) override;

	void sequenceCurrentTimeChanged(Sequence* s, float prevTime, bool seeking) override;
	void sequenceTotalTimeChanged(Sequence* s) override;

	String getTypeString() const override { return "Mapping 2D"; }
	static Mapping2DLayer* create(Sequence* s, var params) { return new Mapping2DLayer(s, params); }
};