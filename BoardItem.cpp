#include "BoardItem.hpp"

// For support range-based for
// See: http://sanichi999.hateblo.jp/entry/2014/12/19/011820
BoardItem begin(BoardItem) { return BoardItem::EMPTY; }
BoardItem end(BoardItem)   { return BoardItem::LEVER_RED; }
BoardItem operator*(BoardItem item) { return item; }
BoardItem operator++(BoardItem &item) {
    return item = BoardItem(std::underlying_type<BoardItem>::type(item) + 1);
}
