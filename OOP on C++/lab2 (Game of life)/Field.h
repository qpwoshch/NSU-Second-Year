#ifndef LAB2_FIELD_H
#define LAB2_FIELD_H
#include "Coordinate.h"
#include "Cell.h"
#include "Size.h"
#include <vector>
#include <cstddef>







class Field {
private:
    std::vector<std::vector<Cell>> grid;
    Size fieldSize;

public:
    void setSize(Size size);

    void setCell(Coordinate coordinate, Cell cell);

    Cell getCell(Coordinate coordinate) const;

    Size getSize() const;

    const std::vector<std::vector<Cell>>& getGrid() const;


};

#endif
