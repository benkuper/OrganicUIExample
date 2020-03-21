/*
  ==============================================================================

    Curve2DUI.cpp
    Created: 21 Mar 2020 4:06:30pm
    Author:  bkupe

  ==============================================================================
*/

#include "Curve2DUI.h"

Curve2DUI::Curve2DUI(Curve2D* manager) :
    BaseManagerViewUI(manager->niceName, manager)
{
    useCheckersAsUnits = true;
    minZoom = .1f;
    maxZoom = 10;

    animateItemOnAdd = false;

    addExistingItems(false);
    setSize(100, 300);
}

Curve2DUI::~Curve2DUI()
{
}

void Curve2DUI::updateViewUIPosition(Curve2DKeyUI* ui)
{
    Point<int> p = getPosInView(ui->item->position->getPoint());
    Rectangle<int> pr = Rectangle<int>(0, 0, 20, 20).withCentre(p);
    if (ui->item->easing != nullptr) pr = pr.getUnion(getBoundsInView(ui->item->easing->getBounds()));
    pr.expand(5, 5);
    ui->setBounds(pr);
    ui->setValueBounds(getViewBounds(pr));
}

void Curve2DUI::mouseDoubleClick(const MouseEvent& e)
{
    if (e.eventComponent == this)
    {
        Point<float> p = getViewMousePosition();
        Curve2DKey* k = manager->createItem();
        k->position->setPoint(p);
        manager->addItem(k);
    }
}

void Curve2DUI::addItemUIInternal(Curve2DKeyUI* ui)
{
    ui->handle.addMouseListener(this, false);
    ui->item->addAsyncCoalescedKeyListener(this);
}

void Curve2DUI::removeItemUIInternal(Curve2DKeyUI* ui)
{
    ui->handle.removeMouseListener(this);
    if(!ui->inspectable.wasObjectDeleted()) ui->item->removeAsyncKeyListener(this);
}

void Curve2DUI::mouseDrag(const MouseEvent& e)
{
    if (Curve2DKeyHandle* handle = dynamic_cast<Curve2DKeyHandle*>(e.eventComponent))
    {
        handle->key->position->setPoint(getViewMousePosition());
    }
    else
    {
        BaseManagerViewUI::mouseDrag(e);
    }
}

void Curve2DUI::newMessage(const Curve2DKey::Curve2DKeyEvent& e)
{
    updateViewUIPosition(getUIForItem(e.key));
}

