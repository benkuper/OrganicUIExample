/*
  ==============================================================================

    ParametersLayerBlockUI.h
    Created: 8 Nov 2018 3:00:24pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../ParametersLayerBlock.h"
#include "../Track/ui/AnimatedParameterContainerTrackUI.h"
#include "../Track/ui/AnimatedParameterTrackUI.h"

class ParametersLayerTimeline;

class ParametersLayerBlockUI :
	public BaseItemUI<ParametersLayerBlock>,
	public ParametersLayerBlock::AsyncListener
{
public:
	ParametersLayerBlockUI(ParametersLayerBlock * clip, ParametersLayerTimeline * timeline = nullptr);
	~ParametersLayerBlockUI();

	//interaction
	float timeAtMouseDown;
	int posAtMouseDown;

	ParametersLayerBlock * block;
	ParametersLayerTimeline * timeline;

	OwnedArray<AnimatedParameterContainerTrackUI> containerTracksUIs;
	OwnedArray<AnimatedParameterTrackUI> tracksUIs;

	void paint(Graphics &g) override;
	void resizedInternalHeader(Rectangle<int> &r) override;
	void resizedInternalContent(Rectangle<int> &r) override;

	void mouseDown(const MouseEvent &e) override;
	void mouseDrag(const MouseEvent &e) override;
	void mouseUp(const MouseEvent &e) override;

	void controllableFeedbackUpdateInternal(Controllable *) override;

	void newMessage(const ParametersLayerBlock::BlockEvent &e) override;

	class BlockUIListener
	{
	public:
		virtual ~BlockUIListener() {}
		virtual void blockUITimeChanged(ParametersLayerBlockUI *) {}
		virtual void blockUIDragged(ParametersLayerBlockUI *, const MouseEvent &) {}
	};

	ListenerList<BlockUIListener> blockUIListeners;
	void addBlockUIListener(BlockUIListener* newListener) { blockUIListeners.add(newListener); }
	void removeBlockUIListener(BlockUIListener* listener) { blockUIListeners.remove(listener); }

};

