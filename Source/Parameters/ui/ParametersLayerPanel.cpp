/*
  ==============================================================================

    ParametersLayerPanel.cpp
    Created: 8 Nov 2018 3:02:41pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerPanel.h"

ParametersLayerPanel::ParametersLayerPanel(ParametersLayer * layer) :
	SequenceLayerPanel(layer),
	parametersLayer(layer),
	managerUI(&parametersLayer->apcm)
{
	addAndMakeVisible(&managerUI);
}

ParametersLayerPanel::~ParametersLayerPanel()
{

}

void ParametersLayerPanel::resizedInternalContent(Rectangle<int>& r)
{
	managerUI.setBounds(r);
}

Rectangle<int> ParametersLayerPanel::getParameterBounds(AnimatedParameter * p)
{
	for (auto &cui : managerUI.itemsUI)
	{
		for (auto &pui : cui->parameterManagerUI.itemsUI)
		{
			if (pui->item == p)
			{
				return getLocalArea(pui, pui->getLocalBounds());
				break;
			}
		}
	}

	DBG("Error : parameter not found " << p->niceName);
	return Rectangle<int>(0, 0, 10, 10);
}

Rectangle<int> ParametersLayerPanel::getContainerBounds(AnimatedParameterContainer * c)
{
	for (auto &cui : managerUI.itemsUI)
	{
		if (cui->item == c)
		{
			return getLocalArea(cui, cui->getLocalBounds());
			break;
		}
		
	}

	DBG("Error : parameterContainer not found " << c->niceName);
	return Rectangle<int>(0, 0, 10, 10);
}
