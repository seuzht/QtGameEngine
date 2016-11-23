#include "ECRotateToMouse.h"
#include <cassert>
#include <QTimer>
#include "ECRotater.h"
#include "Map.h"

ECRotateToMouse::ECRotateToMouse(Entity *entity):
    entity_(entity),
    rotateStepSize_(5),
    rotateFrequency_(45),
    rotateTimer_(new QTimer(this)),
    rotater_(new ECRotater(entity))
{
    // make sure passed in entity is not nullptr
    assert(entity != nullptr);

    connect(rotateTimer_,&QTimer::timeout,this,&ECRotateToMouse::rotateStep_);
}

/// Executed whenever the entity_ needs to rotate.
/// Will rotate it closer to the mouse.
void ECRotateToMouse::rotateStep_()
{
    rotater_->rotateTowards(entity_->map()->getMousePosition());
}
