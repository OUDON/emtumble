#include "BoardItem.hpp"

QPixmap BoardItem::pixmap(BoardItem::ItemType item)
{
    if (qpixmap_memo.count(item)) return qpixmap_memo.at(item);
    QPixmap image = QPixmap(image_filename.at(item).c_str());
    return qpixmap_memo[item] = image;
}

QColor BoardItem::color(BoardItem::ItemType item)
{
    return item_to_color.at(item);
}

bool BoardItem::has_gear(BoardItem::ItemType item)
{
    return (item == BoardItem::ItemType::GEAR
            || item == BoardItem::ItemType::GEAR_BIT_POINTING_LEFT
            || item == BoardItem::ItemType::GEAR_BIT_POINTING_RIGHT);
}
