#include "BoardItem.hpp"

QPixmap BoardItem::pixmap(BoardItem::ItemType item)
{
    return QPixmap(image_filename.at(item).c_str());
}

QColor BoardItem::color(BoardItem::ItemType item)
{
    return item_to_color.at(item);
}
