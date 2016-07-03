#include "EquipableItem.h"
#include <QPointF>
#include <cassert>
#include "Inventory.h"
#include "Slot.h"
#include "DynamicEntity.h"

EquipableItem::EquipableItem():
    slotEquippedIn_(nullptr)
{

}

// Returns true if the EquipableItem is equipped, otherwise false.
bool EquipableItem::isEquipped()
{
    if (slotEquippedIn_ != nullptr){
        return true;
    } else {
        return false;
    }
}

/// Returns the Slot that the EquipableItem is equipped in.
/// Returns nullptr if not equipped in any slot.
Slot *EquipableItem::slotEquippedIn()
{
    return slotEquippedIn_;
}

/// Returns the EquipableItem's attachment point. The attachment point is the
/// position of the EquipableItem that is to be attached to the DynamicEntity.
QPointF EquipableItem::attachmentPoint()
{
    return attachmentPoint_;
}

/// Set the attachment point of the EquipableItem.
/// @see EquipableItem::attachmentPoint()
void EquipableItem::setAttachmentPoint(QPointF point)
{
    attachmentPoint_ = point;
}