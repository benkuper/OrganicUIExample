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

    setSize(100, 300);
}

Curve2DUI::~Curve2DUI()
{
}

void Curve2DUI::updateViewUIPosition(Curve2DKeyUI* ui)
{
    Point<int> p = getPosInView(ui->item->position->getPoint());
    Rectangle<int> pr = Rectangle<int>(0, 0, 20, 20).withCentre(p);
    
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

