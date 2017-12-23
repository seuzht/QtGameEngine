#ifndef INVENTORYCELL_H
#define INVENTORYCELL_H

#include "Gui.h"
#include <QPointer>
#include "Item.h"
#include <memory>
#include <QObject>

class Panel;
class QGraphicsItem;
class QGraphicsPixmapItem;
class QColor;
class QPixmap;

/// Represents a Gui that visualizes and allows mouse interaction with an Item.
/// When the Item in the ItemCell is clicked, ItemCell will emit a signal.
/// You can set the Item of the ItemCell via setItem(Item*) or by passing the Item
/// in the ItemCell constructor. There are several member functions provided
/// which allow you to modify the look/size of the ItemCell.
class ItemCell: public Gui
{
    Q_OBJECT
public:
    ItemCell(int width, int height, Item* item = nullptr);

    void setItem(Item* item);
    Item* item();

    void setSize(int width, int height);
    void setBackgroundColor(const QColor& color);
    void setBackgroundPixmap(const QPixmap& pixmap);

    QGraphicsItem* getGraphicsItem();

public slots:
    void onClicked_(Panel *panel, QPointF pos, int button);

signals:
    void clicked(ItemCell* itemCell, int button);

private:
    std::unique_ptr<QGraphicsPixmapItem> picture_;
    std::unique_ptr<Panel> background_;
    QPointer<Item> item_;

    void draw_();
};

#endif // INVENTORYCELL_H
