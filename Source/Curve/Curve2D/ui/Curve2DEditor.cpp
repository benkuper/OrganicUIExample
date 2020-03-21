/*
  ==============================================================================

    Curve2DEditor.cpp
    Created: 5 Feb 2017 2:58:27pm
    Author:  Ben

  ==============================================================================
*/

#include "Curve2DEditor.h"

Curve2DEditor::Curve2DEditor(Curve2D * curve, bool isRoot) :
	GenericControllableContainerEditor(curve, isRoot),
	curve(curve),
	curveUI(nullptr)
{
	if (curve->showUIInEditor)
	{
		curveUI.reset(new Curve2DUI(curve));

		curveUI->bgColor = BG_COLOR;
		curveUI->transparentBG = false;
		addAndMakeVisible(curveUI.get());
		setSize(100, 400);
	}
}

Curve2DEditor::~Curve2DEditor()
{
}

void Curve2DEditor::resizedInternalContent(juce::Rectangle<int> &r)
{
	if (curveUI != nullptr)
	{
		if (curveUI != nullptr) curveUI->setBounds(r);
		r.translate(0, curveUI->getHeight());
	}
	
	r.setHeight(0);
}
