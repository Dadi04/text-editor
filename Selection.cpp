#include "Selection.h"
#include <algorithm>
#include <climits>

void Selection::setStart(int row, int col) {
    startRow = row;
    startCol = col;
}

void Selection::setEnd(int row, int col) {
    endRow = row;
    endCol = col;
}

void Selection::clear() {
    startRow = startCol = endRow = endCol = -1;
}

bool Selection::isActive() const {
    return startRow != -1 && endRow != -1;
}

bool Selection::isSelected(int row, int col) const {
    if (!isActive()) return false;

    int sRow = std::min(startRow, endRow);
    int eRow = std::max(startRow, endRow);
    int sCol = (row == sRow) ? std::min(startCol, endCol) : 0;
    int eCol = (row == eRow) ? std::max(startCol, endCol) : INT_MAX;

    return row >= sRow && row <= eRow && col >= sCol && col <= eCol;
}

int Selection::getStartRow() const {
    return startRow;
}

int Selection::getStartCol() const {
    return startCol;
}

int Selection::getEndRow() const {
    return endRow;
}

int Selection::getEndCol() const {
    return endCol;
}
