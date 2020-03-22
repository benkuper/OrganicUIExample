/*
  ==============================================================================

    Curve2DKeyUI.h
    Created: 21 Mar 2020 4:06:36pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../Curve2DKey.h"

class Curve2DKeyHandle :
    public InspectableContentComponent
{
public:
    Curve2DKeyHandle(Curve2DKey* key);
    ~Curve2DKeyHandle();

    Curve2DKey* key;
    
    void paint(Graphics& g) override;

    void inspectableSelectionChanged(Inspectable* i) override;
};

class Curve2DKeyUI :
    public BaseItemMinimalUI<Curve2DKey>,
    public Curve2DKey::AsyncListener
{
public:
    Curve2DKeyUI(Curve2DKey* key);
    ~Curve2DKeyUI();

    Curve2DKeyHandle handle;

    Rectangle<float> valueBounds;

    std::unique_ptr<Easing2DUI> easingUI;


    void resized() override;
    void paint(Graphics& g) override;

    void setShowEasingHandles(bool value);

    void updateEasingUI();

    bool hitTest(int x, int y) override;

    void setValueBounds(const Rectangle<float> valueBounds);
    Point<int> getUIPosForValuePos(const Point<float>& valuePos) const;

    void newMessage(const Curve2DKey::Curve2DKeyEvent& e) override;
    void inspectableSelectionChanged(Inspectable* i) override;

    void controllableFeedbackUpdateInternal(Controllable* c) override;

    class  Curve2DKeyUIEvent
    {
    public:
        enum Type { KEYUI_UPDATED };

        Curve2DKeyUIEvent(Type t, Curve2DKeyUI* keyUI) : type(t), keyUI(keyUI) {}

        Type type;
        Curve2DKeyUI* keyUI;
    };

    QueuedNotifier<Curve2DKeyUIEvent> keyUINotifier;
    typedef QueuedNotifier<Curve2DKeyUIEvent>::Listener AsyncListener;


    void addAsyncKeyListener(AsyncListener* newListener) { keyUINotifier.addListener(newListener); }
    void addAsyncCoalescedKeyListener(AsyncListener* newListener) { keyUINotifier.addAsyncCoalescedListener(newListener); }
    void removeAsyncKeyListener(AsyncListener* listener) { keyUINotifier.removeListener(listener); }
};