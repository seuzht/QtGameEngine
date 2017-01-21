#include "ECMoveStraight.h"
#include <QTimer>
#include "Utilities.h"
#include <cassert>
#include <QLineF>

ECMoveStraight::ECMoveStraight(Entity& entity):
    speed_(entity.speed()),
    faceTarget_(false),
    isMoving_(false),
    entity_(&entity),
    moveTimer_(new QTimer(this)),
    stepSize_(25)
{
    // empty
}

void ECMoveStraight::setSpeed(int speed)
{
    speed_ = speed;
}

int ECMoveStraight::speed()
{
    return speed_;
}

/// Sets how big each step of the controlled entity will be.
/// The larger the stepSize value, the more "jumpy" the movement will appear (but it
/// should be faster to execute).
void ECMoveStraight::setStepSize(int stepSize)
{
    stepSize_ = stepSize;
}

int ECMoveStraight::stepSize()
{
    return stepSize_;
}

/// Starts moving the controlle entity towards the specified position.
void ECMoveStraight::moveTowards(QPointF pos)
{
    // guards
    assert(!entity_.isNull()); // make sure entity isn't dead
    Map* entitysMap = entity_->map();
    assert(entitysMap != nullptr); // make sure entity is in a map

    // stop moving if already moving
    stopMoving();

    // update internal variables
    isMoving_ = true;
    targetPos_ = pos;

    // store initial angle (so we know when the entity has past its target point)
    QLineF line(entity_->pointPos(),pos);
    initialAngle_ = line.angle();

    // face target position (if option enabled)
    if (faceTarget()){
        entity_->setFacingAngle(-1 * line.angle());
    }

    // start moving
    connect(moveTimer_,&QTimer::timeout,this,&ECMoveStraight::moveStep_);
    moveTimer_->start(secondsToMs(frequency(stepSize_,speed_)));
}

/// Stops the controlled entity right where its at.
void ECMoveStraight::stopMoving()
{
    moveTimer_->disconnect();
    isMoving_ = false;
}

/// If true i passed in, makes the controlled entity face the target position before
/// proceeding to move towards it. If false is passed in, the controlled entity
/// will move without changing its facing angle.
void ECMoveStraight::setFaceTarget(bool tf)
{
    faceTarget_ = tf;
}

/// Returns true if the controlled entity will face the target position before moving
/// towards it.
/// @see setFaceTarget()
bool ECMoveStraight::faceTarget()
{
    return faceTarget_;
}

/// Returns true if the controlled entity is currently being moved.
bool ECMoveStraight::isMoving()
{
    return isMoving_;
}

/// Executed periodically to move the controlled entity one step closer towards its target
/// position.
void ECMoveStraight::moveStep_()
{
    // if controlled entity has died, kill self :(
    if (entity_.isNull()){
        delete this;
        return;
    }

    // move
    QLineF line(entity_->pointPos(),targetPos_);
    line.setLength(stepSize_);
    double newX = entity_->pointX()+line.dx();
    double newY = entity_->pointY()+line.dy();
    entity_->setPointPos(QPointF(newX,newY));

    // if close enough, stop moving
    const double EPSILON = 50;
    if (distance(entity_->pointPos(),targetPos_) < EPSILON){
        stopMoving();
        return;
    }

    // if past (due to large step size) stop moving
    if (qAbs(line.angle() - initialAngle_) > 100){ // if we haven't passed, diff in angles should be tiny, surely under 100
        stopMoving();
        return;
    }

}