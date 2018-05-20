#pragma once

#include "Item.h"

namespace qge{

class Entity;
class EntityTargetAbility;

/// An abstract class that represents an Item that can be used on an Entity.
///
/// Implementation details
/// ----------------------
/// If the item has an ability assigned (via setAbility() or passed into the ctor)
/// then that ability will be used upon use(), other wise, the virtual use_() function will be
/// called. When the ability of an item is set, its icon will be changed to the icon of the ability.
/// @author Abdullah Aghazadah
/// @date 2/13/15
class EntityTargetItem : public Item
{
public:
    EntityTargetItem(EntityTargetAbility* ability=nullptr);

    void use(Entity* onEntity);
    void setAbility(EntityTargetAbility* ability);

protected:
    virtual void use_(Entity* onEntity) = 0;
private:
    EntityTargetAbility* ability_;
};

}
