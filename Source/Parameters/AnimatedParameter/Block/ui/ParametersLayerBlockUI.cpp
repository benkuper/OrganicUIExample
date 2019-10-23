/*
  ==============================================================================

    ParametersLayerBlockUI.cpp
    Created: 8 Nov 2018 3:00:24pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerBlockUI.h"
#include "../../../ui/ParametersLayerPanel.h"
#include "../../../ui/ParametersLayerTimeline.h"

ParametersLayerBlockUI::ParametersLayerBlockUI(ParametersLayerBlock * block, ParametersLayerTimeline * timeline) :
	BaseItemUI(block),
	block(block),
	timeline(timeline)
{
	block->addAsyncBlockListener(this);
	bgColor = block->isCurrent ? AUDIO_COLOR.brighter() : BG_COLOR.brighter(.1f);

	for (auto &ct : block->containerTracks)
	{
		AnimatedParameterContainerTrackUI * ctui = new AnimatedParameterContainerTrackUI(ct);
		addAndMakeVisible(ctui);
		containerTracksUIs.add(ctui);

		for (auto &t : ct->tracks)
		{
			AnimatedParameterTrackUI * tui = new AnimatedParameterTrackUI(t);
			addAndMakeVisible(tui);
			tracksUIs.add(tui);
		}
	}

	repaint();
}

ParametersLayerBlockUI::~ParametersLayerBlockUI()
{
	if (!inspectable.wasObjectDeleted()) block->removeAsyncBlockListener(this);
}

void ParametersLayerBlockUI::paint(Graphics & g)
{
	BaseItemUI::paint(g);
}

void ParametersLayerBlockUI::resizedInternalHeader(Rectangle<int>& r)
{
	r.removeFromRight(2);
}

void ParametersLayerBlockUI::resizedInternalContent(Rectangle<int>& r)
{
	if (timeline == nullptr)
	{
		DBG("TIMELINE NULL");
		return;
	}

	ParametersLayerPanel * panel = dynamic_cast<ParametersLayerPanel *>(timeline->getRelatedPanel());
	if (panel == nullptr)
	{
		DBG("PANEL IS NULL");
		return;
	}
	
	for (auto &ct : containerTracksUIs)
	{
		ct->setBounds(panel->getContainerBounds(ct->containerTrack->container).withX(0).withWidth(getWidth()).withHeight(10));
	}

	for (auto &t : tracksUIs)
	{
		t->setBounds(panel->getParameterBounds(t->track->parameter).withX(0).withWidth(getWidth()));
	}
}

void ParametersLayerBlockUI::mouseDown(const MouseEvent & e)
{
	BaseItemUI::mouseDown(e);
	timeAtMouseDown = block->time->floatValue();
	posAtMouseDown = getX();
}

void ParametersLayerBlockUI::mouseDrag(const MouseEvent & e)
{
	BaseItemUI::mouseDrag(e);
	blockUIListeners.call(&BlockUIListener::blockUIDragged, this, e);
}

void ParametersLayerBlockUI::mouseUp(const MouseEvent & e)
{
	BaseItemUI::mouseUp(e);
	item->time->setUndoableValue(timeAtMouseDown, item->time->floatValue());
}

void ParametersLayerBlockUI::controllableFeedbackUpdateInternal(Controllable * c)
{
	if (c == item->time || c == item->blockLength)
	{
		blockUIListeners.call(&BlockUIListener::blockUITimeChanged, this);
		repaint();
	}
}

void ParametersLayerBlockUI::newMessage(const ParametersLayerBlock::BlockEvent & e)
{
	switch (e.type)
	{
	case ParametersLayerBlock::BlockEvent::BLOCK_IS_CURRENT_CHANGED:
		bgColor = block->isCurrent ? AUDIO_COLOR.brighter() : BG_COLOR.brighter(.1f);
		repaint();
		break;
	}

}