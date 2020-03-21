/*
  ==============================================================================

	Easing2DUI.h
	Created: 16 Dec 2016 7:13:11pm
	Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../Easing2D.h"

class Easing2DUI :
	public InspectableContentComponent,
	public ContainerAsyncListener
{
public:
	Easing2DUI(Easing2D* e);
	virtual ~Easing2DUI();

	WeakReference<Easing2D> easing;

	Path drawPath;
	Path hitPath;

	int hitPathPrecision = 10;

	Rectangle<float> valueBounds;

	void paint(Graphics& g) override;
	virtual void paintInternal(Graphics&) {}
	void resized() override;

	void generatePath();
	virtual void generatePathInternal();

	void autoGeneratePathWithPrecision(int precision = 100);

	void buildHitPath();

	bool hitTest(int tx, int ty) override;

	virtual void newMessage(const ContainerAsyncEvent& e) override;
	virtual void easingControllableFeedbackUpdate(Controllable*) {}

	void setValueBounds(const Rectangle<float> valueBounds);
	Point<int> getUIPosForValuePos(const Point<float>& valuePos) const;

	class Easing2DHandle :
		public Component
	{
	public:
		Easing2DHandle();
		void paint(Graphics& g) override;
	};

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Easing2DUI)
};

class LinearEasing2DUI :
	public Easing2DUI
{
public:
	LinearEasing2DUI(LinearEasing2D* e);
	void generatePathInternal() override;

	// Inherited via Easing2DUI
};


class CubicEasing2DUI :
	public Easing2DUI
{
public:
	CubicEasing2DUI(CubicEasing2D* e);

	Easing2DHandle h1;
	Easing2DHandle h2;


	bool hitTest(int tx, int ty) override;

	void resized() override;

	void generatePathInternal() override;
	void paintInternal(Graphics& g) override;

	void inspectableSelectionChanged(Inspectable*) override;
	void easingControllableFeedbackUpdate(Controllable*) override;

	void mouseDrag(const MouseEvent& e) override;
};