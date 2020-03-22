/*
  ==============================================================================

    Curve2DKey.h
    Created: 21 Mar 2020 4:06:25pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "easing/Easing2D.h"

class Curve2DKey :
    public BaseItem,
    public Inspectable::InspectableListener
{
public:
    Curve2DKey();
    ~Curve2DKey();

    EnumParameter* easingType;
    std::unique_ptr<Easing2D> easing;
    Curve2DKey* nextKey;

    Point2DParameter* position;
    float curvePosition; //position on the curve, calculated by the curve to distribute evenly the points

    void setEasing(Easing2D::Type type);
    void setNextKey(Curve2DKey* key);

    Point<float> getValueAt(const float &position);
    float getLength() const;

    void onContainerParameterChangedInternal(Parameter* p) override;
    void onExternalParameterValueChanged(Parameter* p) override;
    void onControllableFeedbackUpdateInternal(ControllableContainer* cc, Controllable* c) override;

    void inspectableSelectionChanged(Inspectable* i) override;
    void setSelectedInternal(bool) override;

    void inspectableDestroyed(Inspectable* i) override;

    bool isThisOrChildSelected();

    void updateEasingKeys();
    void notifyKeyUpdated();


    String getTypeString() const override { return "2DKey"; }


    class  Curve2DKeyEvent
    {
    public:
        enum Type {  KEY_UPDATED, SELECTION_CHANGED };

        Curve2DKeyEvent(Type t, Curve2DKey* key) : type(t), key(key) {}

        Type type;
        WeakReference<Curve2DKey> key;
    };

    QueuedNotifier<Curve2DKeyEvent> keyNotifier;
    typedef QueuedNotifier<Curve2DKeyEvent>::Listener AsyncListener;


    void addAsyncKeyListener(AsyncListener* newListener) { keyNotifier.addListener(newListener); }
    void addAsyncCoalescedKeyListener(AsyncListener* newListener) { keyNotifier.addAsyncCoalescedListener(newListener); }
    void removeAsyncKeyListener(AsyncListener* listener) { keyNotifier.removeListener(listener); }

private:
    WeakReference<Curve2DKey>::Master masterReference;
    friend class WeakReference<Curve2DKey>;
};