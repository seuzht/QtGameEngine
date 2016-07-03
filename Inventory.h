#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_set>
#include <QObject>

class Item;
class DynamicEntity;
class EquipableItem;
class NoTargetItem;
class EntityTargetItem;
class PointTargetItem;

/// Represents a collection of Items that can belong to a DynamicEntity.
class Inventory: public QObject
{
    Q_OBJECT

    // DynamicEntity and Inventory reference each other. The association set up
    // code is in the Dynamic Entity, which needs private access to set the
    // pointer in Inventory.
    friend class DynamicEntity;
public:
    Inventory();

    DynamicEntity* entity();

    void addItem(Item* item);
    void removeItem(Item* item);
    bool contains(Item* item);

    std::unordered_set<EquipableItem*> getEquipableItems();
    std::unordered_set<NoTargetItem*> getNoTargetItems();
    std::unordered_set<EntityTargetItem*> getEntityTargetItems();
    std::unordered_set<PointTargetItem*> getPointTargetItems();
    std::unordered_set<Item*> getItems();

signals:
    void itemAdded(Item* item);
    void itemRemoved(Item* item);

private:
    DynamicEntity* entity_;
    std::unordered_set<Item*> items_;
};

#endif // INVENTORY_H