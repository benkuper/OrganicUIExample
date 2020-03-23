/*
  ==============================================================================

    Mapping2DTimeline.cpp
    Created: 23 Mar 2020 5:18:10pm
    Author:  bkupe

  ==============================================================================
*/

#include "Mapping2DLayerTimeline.h"

Mapping2DTimeline::Mapping2DTimeline(Mapping2DLayer * layer) :
	SequenceLayerTimeline(layer),
	mapping2DLayer(layer),
	automationUI(layer->automation)
{
	addAndMakeVisible(&automationUI);
	needle.toFront(false);
	resized();
}

void Mapping2DTimeline::paint(Graphics& g)
{
	SequenceLayerTimeline::paint(g);

	Path xPath;
	Path yPath;
	xPath.startNewSubPath(0, getHeight());
	yPath.startNewSubPath(0, getHeight());
	int precision = getWidth()/3;
	for (int i = 0; i < precision; i++)
	{
		float p = i * 1.0f / precision;
		float t = getTimeForX(p*getWidth());
		Point<float> pos = mapping2DLayer->curve.getValueAtNormalizedPosition(mapping2DLayer->automation->getValueForPosition(t));
		xPath.lineTo(getXForTime(t), getHeight() * (1 - pos.x));
		yPath.lineTo(getXForTime(t), getHeight() * (1 - pos.y));
	}

	g.setColour(RED_COLOR);
	g.strokePath(xPath, PathStrokeType(1));
	g.setColour(GREEN_COLOR);
	g.strokePath(yPath, PathStrokeType(1));
}

void Mapping2DTimeline::resized()
{
	SequenceLayerTimeline::resized();
	automationUI.setBounds(getLocalBounds());
}

void Mapping2DTimeline::updateContent()
{
	automationUI.setViewRange(item->sequence->viewStartTime->floatValue(), item->sequence->viewEndTime->floatValue());
}

bool Mapping2DTimeline::keyPressed(const KeyPress& e)
{
	if (automationUI.keyPressed(e)) return true;
	return SequenceLayerTimeline::keyPressed(e);
}
