/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "ExampleEngine.h"

//==============================================================================
class OrganicUIExampleApplication  : public OrganicApplication
{
public:
    //==============================================================================
    OrganicUIExampleApplication() : OrganicApplication("OrganicUI Example"){}

    //==============================================================================
	void initialiseInternal(const String& commandLine) override
	{
		//
		engine = new ExampleEngine();
		mainComponent = new MainComponent();
	}
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (OrganicUIExampleApplication)
