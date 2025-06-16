#ifndef SELECTION_H
#define SELECTION_H

class Selection {
public:
    void setStart(int row, int col);
    void setEnd(int row, int col);
    void clear();
    bool isActive() const;
    bool isSelected(int row, int col) const;

    int getStartRow() const;
    int getStartCol() const;
    int getEndRow() const;
    int getEndCol() const;

private:
    int startRow = -1;
    int startCol = -1;

    int endRow = -1;
    int endCol = -1;
};

#endif