/*
  ==============================================================================

    ParametersLayerBlockManagerUI.h
    Created: 8 Nov 2018 3:00:35pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../ParametersLayerBlockManager.h"
#include "ParametersLayerBlockUI.h"

class ParametersLayerTimeline;

class ParametersLayerBlockManagerUI :
	public BaseManagerUI<ParametersLayerBlockManager, ParametersLayerBlock, ParametersLayerBlockUI>,
	public ParametersLayerBlockUI::BlockUIListener
{
public:
	ParametersLayerBlockManagerUI(ParametersLayerTimeline * timeline, ParametersLayerBlockManager * manager);
	~ParametersLayerBlockManagerUI();

	ParametersLayerTimeline * timeline;

	void resized() override;
	void updateContent();

	ParametersLayerBlockUI * createUIForItem(ParametersLayerBlock * block) override;

	void placeBlockUI(ParametersLayerBlockUI * cui);
	void mouseDoubleClick(const MouseEvent &e) override;

	void addItemFromMenu(bool, Point<int> mouseDownPos) override;
	void addItemUIInternal(ParametersLayerBlockUI * cui) override;
	void removeItemUIInternal(ParametersLayerBlockUI * cui) override;

	void blockUITimeChanged(ParametersLayerBlockUI * cui) override;
	void blockUIDragged(ParametersLayerBlockUI * cui, const MouseEvent &) override;
};

