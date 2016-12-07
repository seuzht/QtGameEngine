#include "AbilityCell.h"
#include <QGraphicsPixmapItem>
#include "Panel.h"
#include "Ability.h"
#include "Sprite.h"

AbilityCell::AbilityCell(int width, int height, Ability *ability):
    background_(new Panel()),
    ability_(ability),
    picture_(new QGraphicsPixmapItem())
{
    picture_->setParentItem(background_->getGraphicsItem());
    background_->setWidth(width);
    background_->setHeight(height);
    connect(background_,&Panel::clicked,this,&AbilityCell::onClicked_);
    draw_();
}

/// Sets the Ability that the AbilityCell should be visualizing.
void AbilityCell::setAbility(Ability *ability)
{
    ability_ = ability;
}

/// Returns the Ability of the AbilityCell.
Ability *AbilityCell::ability()
{
    return ability_;
}

/// Sets the width and height of the AbilityCell.
void AbilityCell::setSize(int width, int height)
{
    background_->setWidth(width);
    background_->setHeight(height);
}

/// Sets the background color of the AbilityCell.
/// This works exactly the same as ItemCell::setBackgroundColor().
void AbilityCell::setBackgroundColor(const QColor &color)
{
    background_->setBackgroundColor(color);
}

/// Sets the background of the AbilityCell to a QPixmap.
/// @see setBackgroundColor()
void AbilityCell::setBackgroundPixmap(const QPixmap &pixmap)
{

}

QGraphicsItem *AbilityCell::getGraphicsItem()
{
    return background_->getGraphicsItem();
}

/// Executed when the AbilityCell is clicked.
/// Will simply emit clicked().
void AbilityCell::onClicked_(Panel *panel, QPointF pos, int button)
{
    emit clicked(this,button);
}

/// Draws the AbilityCell in its current state.
void AbilityCell::draw_()
{
    // draw ability's icon
    if (ability_ != nullptr){
        double width = background_->width();
        double height = background_->height();
        picture_->setPixmap(ability_->icon()->currentFrame().scaled(width-20,height-20));
        picture_->setPos(10,10);
    }
}
