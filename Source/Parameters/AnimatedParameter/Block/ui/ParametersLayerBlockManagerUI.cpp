/*
  ==============================================================================

    ParametersLayerBlockManagerUI.cpp
    Created: 8 Nov 2018 3:00:35pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerBlockManagerUI.h"
#include "../../../ui/ParametersLayerTimeline.h"

ParametersLayerBlockManagerUI::ParametersLayerBlockManagerUI(ParametersLayerTimeline * _timeline, ParametersLayerBlockManager * manager) :
	BaseManagerUI("Clip Manager", manager, false),
	timeline(_timeline)
{
	noItemText = "To add an automation block to this layer, double-click here";
	addItemText = "Add Automation Block";
	animateItemOnAdd = false;
	transparentBG = true;

	addItemBT->setVisible(false);
	addExistingItems();
}

ParametersLayerBlockManagerUI::~ParametersLayerBlockManagerUI()
{
}

void ParametersLayerBlockManagerUI::resized()
{
	updateContent();
}

void ParametersLayerBlockManagerUI::updateContent()
{
	for (auto &cui : itemsUI)
	{
		placeBlockUI(cui);
	}
}

ParametersLayerBlockUI * ParametersLayerBlockManagerUI::createUIForItem(ParametersLayerBlock * block)
{
	return new ParametersLayerBlockUI(block, timeline);
}

void ParametersLayerBlockManagerUI::placeBlockUI(ParametersLayerBlockUI * cui)
{
	int tx = timeline->getXForTime(cui->block->time->floatValue());
	int tx2 = timeline->getXForTime(cui->block->time->floatValue() + cui->block->blockLength->floatValue());
	cui->setBounds(tx, 0, tx2 - tx, getHeight());
}

void ParametersLayerBlockManagerUI::mouseDoubleClick(const MouseEvent & e)
{
	manager->addBlockAt(timeline->getTimeForX(getMouseXYRelative().x));
}

void ParametersLayerBlockManagerUI::addItemFromMenu(bool isFromAddButton, Point<int> mouseDownPos)
{
	if (isFromAddButton) return;
	manager->addBlockAt(timeline->getTimeForX(mouseDownPos.x));
}

void ParametersLayerBlockManagerUI::addItemUIInternal(ParametersLayerBlockUI * cui)
{
	cui->addBlockUIListener(this);
	placeBlockUI(cui);
}

void ParametersLayerBlockManagerUI::removeItemUIInternal(ParametersLayerBlockUI * cui)
{
	cui->removeBlockUIListener(this);
}

void ParametersLayerBlockManagerUI::blockUITimeChanged(ParametersLayerBlockUI * cui)
{
	placeBlockUI(cui);
}

void ParametersLayerBlockManagerUI::blockUIDragged(ParametersLayerBlockUI * cui, const MouseEvent & e)
{
	ParametersLayerBlockUI * bui = dynamic_cast<ParametersLayerBlockUI *>(e.eventComponent);
	if (bui != nullptr)
	{
		float targetTime = cui->timeAtMouseDown + timeline->getTimeForX(e.getOffsetFromDragStart().x, false);
		cui->block->time->setValue(targetTime);
		//repaint();
	}
	
}
