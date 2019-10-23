/*
  ==============================================================================

    AutomationKeyframeUI.h
    Created: 18 Dec 2018 11:24:14am
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "AutomationKeyframeKeyUI.h"

class AutomationKeyframeUI :
	public BaseManagerUI<Automation, AutomationKey, AutomationKeyframeKeyUI>,
	public ContainerAsyncListener,
	public InspectableSelectionManager::Listener,
	public Thread,
	public Timer
{
public:
	AutomationKeyframeUI(Automation * _automation, Colour c = Colours::white);
	virtual ~AutomationKeyframeUI();

	//View optimisation, generate in thread a preview of the image
	enum ViewMode { EDIT, VIEW };
	ViewMode viewMode;
	bool autoSwitchMode;

	Image viewImage;
	bool shouldUpdateImage;
	SpinLock imageLock;

	float viewStartPos;
	float viewEndPos;

	int firstROIKey;
	int lastROIKey;

	bool autoResetViewRangeOnLengthUpdate;

	float currentPosition;
	float currentValue;

	bool fixedPosOrValueEnabled; //When using shift key and moving handles, keep either position or value

	Colour color;

	AutomationKeyframeKeyUI * currentUI;
	std::unique_ptr<AutomationMultiKeyTransformer> transformer;

	bool shouldRepaint;

	void setCurrentPosition(const float &pos);
	void setCurrentValue(const float &val);

	void setViewMode(ViewMode mode);

	void setViewRange(float start, float end);
	void updateROI();

	void paint(Graphics &g) override;

	void resized() override;
	void placeKeyUI(AutomationKeyframeKeyUI * kui);

	int getXForPos(float time);
	float getPosForX(int tx, bool offsetStart = true);

	//int getYForValue(float value);
	//float getValueForY(int ty);

	bool isInView(AutomationKeyframeKeyUI * kui);

	AutomationKeyframeKeyUI * getClosestKeyUIForPos(float pos, int start = -1, int end = -1);

	void itemAddedAsync(AutomationKey *) override;
	void itemsReorderedAsync() override;

	AutomationKeyframeKeyUI * createUIForItem(AutomationKey * item) override;

	void addItemUIInternal(AutomationKeyframeKeyUI *) override;
	void removeItemUIInternal(AutomationKeyframeKeyUI *) override;

	void showMenuAndAddItem(bool, Point<int>) override {}; //no menu

	void mouseDown(const MouseEvent &e) override;
	void mouseDoubleClick(const MouseEvent &e) override;
	void mouseDrag(const MouseEvent &e) override;
	void mouseUp(const MouseEvent &e) override;
	bool keyPressed(const KeyPress &e) override;

	void newMessage(const ContainerAsyncEvent &e) override;

	void inspectablesSelectionChanged() override;

	void focusGained(FocusChangeType cause) override;
	void focusLost(FocusChangeType cause) override;

	//Generate image thread
	void run() override;

	void timerCallback() override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutomationKeyframeUI)

};