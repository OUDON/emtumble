#include "BoardItem.hpp"

QPixmap BoardItem::pixmap(BoardItem::ItemType item)
{
    return QPixmap(image_filename.at(item).c_str());
}
