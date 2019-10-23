/*
  ==============================================================================

    AutomationKeyframeUI.cpp
    Created: 18 Dec 2018 11:24:14am
    Author:  bkupe

  ==============================================================================
*/

#include "AutomationKeyframeUI.h"

AutomationKeyframeUI::AutomationKeyframeUI(Automation * _automation, Colour c) :
	BaseManagerUI("Automation", _automation, false),
	Thread("AutomationViewGenerator"),
	autoSwitchMode(false),
	firstROIKey(0),
	lastROIKey(0),
	autoResetViewRangeOnLengthUpdate(true),
	currentPosition(0),
	color(c),
	currentUI(nullptr),
	transformer(nullptr)
{

	autoDrawHighlightWhenSelected = false;
	manager->selectionManager->addSelectionListener(this);

	setShowAddButton(false);
	animateItemOnAdd = false;

	transparentBG = true;
	//bgColor = Colours::orange.withAlpha(.5f);
	
	setViewRange(0, manager->length->floatValue());
	manager->addAsyncContainerListener(this);

	resizeOnChildBoundsChanged = false;
	addExistingItems();

	noItemText = "Add keys by double-clicking here";

	viewMode = autoSwitchMode ? EDIT : VIEW; //force trigger change on setViewMode
	setViewMode(autoSwitchMode ? VIEW : EDIT);

	//updateROI();

	setSize(100, 100);
	startTimerHz(20);
}

AutomationKeyframeUI::~AutomationKeyframeUI()
{
	if (!inspectable.wasObjectDeleted() && manager->selectionManager != nullptr)
	{
		manager->selectionManager->removeSelectionListener(this);
		manager->removeAsyncContainerListener(this);
	}

	signalThreadShouldExit();
	stopThread(1000);
}

void AutomationKeyframeUI::setCurrentPosition(const float &pos)
{
	currentPosition = pos;
	currentUI = getClosestKeyUIForPos(currentPosition);
	shouldRepaint = true;
}

void AutomationKeyframeUI::setCurrentValue(const float &val)
{
	currentValue = val;
	shouldRepaint = true;
}

void AutomationKeyframeUI::setViewMode(ViewMode mode)
{
	if (viewMode == mode) return;
	viewMode = mode;

	switch (viewMode)
	{
	case EDIT:
		signalThreadShouldExit();
		waitForThreadToExit(500);

		updateROI();
		break;

	case VIEW:
	{
		for (auto &i : itemsUI) i->setVisible(false);
		shouldUpdateImage = true;
		startThread();
	}
	break;
	}

	repaint();
}

void AutomationKeyframeUI::setViewRange(float start, float end)
{
	if (viewStartPos == start && viewEndPos == end) return;

	viewStartPos = start;
	viewEndPos = end;

	updateROI();
	shouldUpdateImage = true;
	shouldRepaint = true;
}

void AutomationKeyframeUI::updateROI()
{
	if (viewMode != EDIT) return;

	if (itemsUI.size() == 0) return;

	int len = itemsUI.size() - 1;
	for (int i = 0; i < len; i++)
	{
		itemsUI[i]->setVisible(false);
		if (isInView(itemsUI[i]))
		{
			firstROIKey = jmax<int>(i - 1, 0);
			break;
		}
	}

	for (int i = len; i >= 0; i--)
	{
		itemsUI[i]->setVisible(false);
		if (isInView(itemsUI[i]))
		{
			lastROIKey = jmin<int>(i + 1, len);
			break;
		}
	}

	for (int i = firstROIKey; i <= lastROIKey; i++)
	{
		if (itemsUI[i] != nullptr) itemsUI[i]->setVisible(true);
	}

	resized();
}

void AutomationKeyframeUI::paint(Graphics & g)
{
	BaseManagerUI::paint(g);

	

	if (getWidth() == 0 || getHeight() == 0) return;

	if (viewMode == VIEW)
	{
		imageLock.enter();
		//{
		g.setColour(Colours::white);
		g.drawImage(viewImage, getLocalBounds().toFloat());
		imageLock.exit();
		//}
	}
}


void AutomationKeyframeUI::resized()
{
	if (viewMode == VIEW)
	{
		shouldUpdateImage = true;
		return;
	}

	MessageManagerLock mm;

	if (getParentComponent() == nullptr) return;
	if (getWidth() == 0 || getHeight() == 0) return;
	if (itemsUI.size() == 0) return;

	for (int i = firstROIKey; i <= lastROIKey; i++)
	{
		placeKeyUI(itemsUI[i]);
	}

	if (transformer != nullptr) transformer->updateBoundsFromKeys();

	shouldRepaint = true;//overkill? needed to have proper value feedback when creating ui and resizing for the first time
}

void AutomationKeyframeUI::placeKeyUI(AutomationKeyframeKeyUI * kui)
{

	//int index = itemsUI.indexOf(kui);
	if (kui == nullptr) return;

	int tx = getXForPos(kui->item->position->floatValue());
	//int ty = getYForValue(kui->item->value->floatValue());
	
	juce::Rectangle<int> kr(tx - getHeight() / 2, 0, getHeight(), getHeight());
	kui->setBounds(kr.reduced(2));

	//if (index < itemsUI.size() - 1)
	//{
	//	AutomationKeyframeKeyUI * nextKey = itemsUI[index + 1];
	//	int tx2 = getXForPos(nextKey->item->position->floatValue());
		
		//int ty2 = getYForValue(nextKey->item->value->floatValue());

		////Rectangle<int> kr2 = Rectangle<int>(0, 0, AutomationKeyframeKeyUI::handleClickZone, AutomationKeyframeKeyUI::handleClickZone).withCentre(Point<int>(tx2, ty2));
		//kr = juce::Rectangle<int>(tx, 0, tx2 - tx, getHeight()).expanded(AutomationKeyframeKeyUI::handleClickZone / 2, 0);
		//kui->setKeyPositions(ty, ty2);
	//}
	//else
	//{
	//	kr = juce::Rectangle<int>(0, 0, AutomationKeyframeKeyUI::handleClickZone, getHeight()).withPosition(tx - AutomationKeyframeKeyUI::handleClickZone / 2, 0);
	//	kui->setKeyPositions(ty, 0);
	//}


	/*
	if (placePrevKUI && index > 0)
	{
		placeKeyUI(itemsUI[index - 1], false);
	}
	*/
}

int AutomationKeyframeUI::getXForPos(float time)
{
	if (viewStartPos == viewEndPos) return 0;
	return (int)jmap<float>(time, viewStartPos, viewEndPos, 0, (float)getWidth());
}

float AutomationKeyframeUI::getPosForX(int tx, bool offsetStart)
{

	float viewRange = viewEndPos - viewStartPos;
	float mapStart = offsetStart ? viewStartPos : 0;

	if (getWidth() == 0) return mapStart;
	return jmap<float>((float)tx, 0, (float)getWidth(), mapStart, mapStart + viewRange);
}


bool AutomationKeyframeUI::isInView(AutomationKeyframeKeyUI * kui)
{
	return kui->item->position->floatValue() >= viewStartPos && kui->item->position->floatValue() <= viewEndPos;
}

AutomationKeyframeKeyUI * AutomationKeyframeUI::getClosestKeyUIForPos(float pos, int start, int end)
{
	if (itemsUI.size() == 0) return nullptr;

	if (start == -1) start = 0;
	if (end == -1) end = itemsUI.size() - 1;


	if (pos < itemsUI[0]->item->position->floatValue()) return itemsUI[0];
	if (pos > itemsUI[itemsUI.size() - 1]->item->position->floatValue()) return itemsUI[itemsUI.size() - 1];


	if (end - start <= 1) return itemsUI[start];

	int midIndex = (int)floor((start + end) / 2);
	float medPos = itemsUI[midIndex]->item->position->floatValue();

	if (pos == medPos) return itemsUI[midIndex];

	else if (pos > medPos)
	{
		return getClosestKeyUIForPos(pos, midIndex, end);
	}
	else
	{
		return getClosestKeyUIForPos(pos, start, midIndex);
	}
}

void AutomationKeyframeUI::itemAddedAsync(AutomationKey * k)
{
	BaseManagerUI::itemAddedAsync(k);
	updateROI();

}

void AutomationKeyframeUI::itemsReorderedAsync()
{
	BaseManagerUI::itemsReorderedAsync();
	updateROI();
}

AutomationKeyframeKeyUI * AutomationKeyframeUI::createUIForItem(AutomationKey * item)
{
	return new AutomationKeyframeKeyUI(item);
}

void AutomationKeyframeUI::addItemUIInternal(AutomationKeyframeKeyUI * kui)
{
	kui->addMouseListener(this, false);
}

void AutomationKeyframeUI::removeItemUIInternal(AutomationKeyframeKeyUI * kui)
{
	if (transformer != nullptr)
	{
		removeChildComponent(transformer);
		transformer = nullptr;
	}

	kui->removeMouseListener(this);
	updateROI();
}

void AutomationKeyframeUI::mouseDown(const MouseEvent & e)
{
	BaseManagerUI::mouseDown(e);

	if (e.eventComponent == this)
	{
		if (e.mods.isLeftButtonDown() && e.mods.isAltDown())
		{
			float pos = getPosForX(e.getPosition().x);
			float val = manager->getValueForPosition(pos);
			manager->addItem(pos, val);
			manager->reorderItems();
		}
		else
		{
			Array<Component *> selectables;
			Array<Inspectable *> inspectables;
			for (auto &i : itemsUI) if (i->isVisible())
			{
				selectables.add(i);
				inspectables.add(i->inspectable);
			}

			if (transformer != nullptr)
			{
				removeChildComponent(transformer);
				transformer = nullptr;
			}

			if (InspectableSelector::getInstance()) InspectableSelector::getInstance()->startSelection(this, selectables, inspectables, manager->selectionManager, !e.mods.isCommandDown() && !e.mods.isShiftDown());
		}
	}
	else
	{
		if (e.mods.isShiftDown())
		{
			AutomationKeyframeKeyUI * kui = dynamic_cast<AutomationKeyframeKeyUI *>(e.eventComponent);
			if (kui != nullptr)
			{
				if (manager->selectionManager->currentInspectables.size() > 0)
				{
					AutomationKey * lastSelectedKey = (AutomationKey *)manager->selectionManager->currentInspectables[manager->selectionManager->currentInspectables.size() - 1];
					AutomationKey * sKey = kui->item;

					int i1 = manager->items.indexOf(lastSelectedKey);
					int i2 = manager->items.indexOf(sKey);

					int index1 = jmin(i1, i2) + 1;
					int index2 = jmax(i1, i2) - 1;

					for (int i = index1; i <= index2; i++)
					{
						manager->items[i]->selectThis(true);
					}
				}
			}
		}

	}

}

void AutomationKeyframeUI::mouseDoubleClick(const MouseEvent & e)
{
	if (e.eventComponent == this)
	{
		float pos = getPosForX(e.getPosition().x);
		float val = manager->getValueForPosition(pos);
		manager->addItem(pos, val); 
		manager->reorderItems();
	}
}

void AutomationKeyframeUI::mouseDrag(const MouseEvent & e)
{
	if (e.originalComponent == this)
	{

	}
	else
	{
		AutomationKeyframeKeyUI * kui = dynamic_cast<AutomationKeyframeKeyUI *>(e.eventComponent);

		if (kui != nullptr)
		{
			if (e.mods.isLeftButtonDown())
			{
				Point<int> mp = e.getEventRelativeTo(this).getPosition();
				float pos = getPosForX(mp.x);
				//float val = getValueForY(mp.y);

				MouseInputSource source = Desktop::getInstance().getMainMouseSource();

				/*if (e.mods.isShiftDown())
				{
					//float initX = getXForPos(kui->posAtMouseDown);
					//float initY = getYForValue(kui->valueAtMouseDown);

					if (fabsf(mp.x - initX) > fabsf(mp.y - initY))
					{
						kui->setMouseCursor(MouseCursor::LeftRightResizeCursor);
						val = kui->valueAtMouseDown;
					}
					else
					{
						kui->setMouseCursor(MouseCursor::UpDownResizeCursor);
						pos = kui->posAtMouseDown;
					}
				}
				else
				{
					kui->setMouseCursor(MouseCursor::NormalCursor);
				}*/


				if (GlobalSettings::getInstance()->constrainKeysToNeighbours->boolValue())
				{
					int index = manager->items.indexOf(kui->item);
					if (index > 0) pos = jmax(pos, manager->items[index - 1]->position->floatValue() + .01f);
					if (index < manager->items.size() - 1)  pos = jmin(pos, manager->items[index + 1]->position->floatValue() - .01f);
				}

				kui->item->position->setValue(pos);
				//kui->item->value->setValue(val);

			}
		}
	}
}

void AutomationKeyframeUI::mouseUp(const MouseEvent & e)
{
	if (e.originalComponent == this)
	{

	}
	else
	{
		AutomationKeyframeKeyUI * kui = dynamic_cast<AutomationKeyframeKeyUI *>(e.eventComponent);
		if (e.mods.isLeftButtonDown())
		{

			Array<UndoableAction *> actions;
			actions.add(kui->item->position->setUndoableValue(kui->posAtMouseDown, kui->item->position->floatValue(), true));
			//actions.add(kui->item->value->setUndoableValue(kui->valueAtMouseDown, kui->item->value->floatValue(), true));
			UndoMaster::getInstance()->performActions("Move automation key", actions);

		}
	}
}

bool AutomationKeyframeUI::keyPressed(const KeyPress & e)
{
	BaseManagerUI::keyPressed(e);
	return false;
}

void AutomationKeyframeUI::newMessage(const ContainerAsyncEvent & e)
{
	if (e.type == ContainerAsyncEvent::EventType::ControllableFeedbackUpdate)
	{
		if (e.targetControllable == manager->position)
		{
			setCurrentPosition(manager->position->floatValue());
		}
		else if (e.targetControllable == manager->value)
		{
			setCurrentValue(manager->value->floatValue());
		}
		else if (e.targetControllable == manager->length)
		{
			if (autoResetViewRangeOnLengthUpdate) setViewRange(0, manager->length->floatValue());
			else resized();
		}
		else if (e.targetControllable != nullptr)
		{
			AutomationKey * k = dynamic_cast<AutomationKey *>(e.targetControllable->parentContainer);
			if (k != nullptr)
			{
				if (e.targetControllable == k->easingType)
				{
					//repaint();
				}
				else if (e.targetControllable == k->position || e.targetControllable == k->value)
				{
					placeKeyUI(getUIForItem(k));
					//repaint();
				}
			}
		}

	}

}

void AutomationKeyframeUI::inspectablesSelectionChanged()
{
	if (transformer != nullptr)
	{
		removeChildComponent(transformer);
		transformer = nullptr;
	}

	Array<AutomationKeyframeKeyUI *> uiSelection;
	if (manager->selectionManager->currentInspectables.size() >= 2)
	{

	}
	for (auto &i : manager->selectionManager->currentInspectables)
	{
		AutomationKey * k = static_cast<AutomationKey *>(i);
		if (k == nullptr) continue;
		AutomationKeyframeKeyUI * kui = getUIForItem(k);
		if (kui == nullptr) return;

		uiSelection.add(kui);
	}

	/*
	if (uiSelection.size() >= 2)
	{
		transformer = new AutomationMultiKeyTransformer(this, uiSelection);
		addAndMakeVisible(transformer);
		transformer->grabKeyboardFocus(); // so no specific key has the focus for deleting
	}
	*/
}

void AutomationKeyframeUI::focusGained(FocusChangeType cause)
{
	if (autoSwitchMode) setViewMode(EDIT);
}

void AutomationKeyframeUI::focusLost(FocusChangeType cause)
{
	//DBG("AUI Focus lost " << cause);
	if (autoSwitchMode) setViewMode(VIEW);
}


void AutomationKeyframeUI::run()
{
	bool firstRun = true;

	while (!threadShouldExit())
	{
		sleep(50); //20ms is plenty enough

		if (Engine::mainEngine->isLoadingFile || Engine::mainEngine->isClearing) continue;
		if (!shouldUpdateImage) continue;

		shouldUpdateImage = false;

		imageLock.enter();

		const int resX = getWidth();
		const int resY = getHeight();

		if (resX == 0 || resY == 0)
		{
			imageLock.exit();
			return;
		}

		if (resX != viewImage.getWidth() || resY != viewImage.getHeight()) viewImage = Image(Image::ARGB, resX, resY, true);
		else viewImage.clear(viewImage.getBounds());


		for (int tx = 0; tx < resX; tx++)
		{
			if (threadShouldExit())
			{
				imageLock.exit();
				return;
			}

			float val = manager->getValueForPosition(getPosForX(tx));
			float y = (1 - val)*getHeight();
			int ty = (int)y;
			int maxDist = 1;
			for (int i = ty - maxDist; i <= ty + maxDist; i++)
			{
				if (i < 0 || i > viewImage.getHeight()) continue;
				float alpha = jlimit<float>(0, 1, 1 - (abs(y - i) / maxDist));
				viewImage.setPixelAt(tx, i, Colours::white.withAlpha(alpha));
			}

			//if(ty < viewImage.getHeight()) viewImage.setPixelAt(tx, ty+1, Colours::white.withAlpha(.2f));
			//if(ty > 0) viewImage.setPixelAt(tx, ty-1, Colours::white.withAlpha(.2f));
		}

		imageLock.exit();

		if (firstRun)
		{
			firstRun = false;
			MessageManagerLock mmLock;
			shouldRepaint = true;
		}
	}

	imageLock.enter();
	viewImage.clear(viewImage.getBounds());
	imageLock.exit();

	//DBG("Exit AutomationKeyframeUI Thread");
}

void AutomationKeyframeUI::timerCallback()
{
	if (shouldRepaint)
	{
		repaint();
		shouldRepaint = false;
	}
}
