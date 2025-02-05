#include "Field.h"


void Field::setSize(Size size) {
    fieldSize = size;
    grid.resize(size.height, std::vector<Cell>(size.width, Cell::Dead));
}

void Field::setCell(Coordinate coordinate, Cell cell) {
    grid[coordinate.y][coordinate.x] = cell;
}

Cell Field::getCell(Coordinate coordinate) const {
    return grid[coordinate.y][coordinate.x];
}

Size Field::getSize() const {
    return fieldSize;
}

const std::vector<std::vector<Cell>>& Field::getGrid() const {
    return grid;
}
