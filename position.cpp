#include "position.hpp"

position::position()  {row = 0, col = 0;}
position::position(const uint8_t &x, const uint8_t &y) {row = x, col = y;}

position & position::operator=(const position &rhs)
{
    if (this == &rhs) {return *this;}

    row = rhs.row;
    col = rhs.col;
    return *this;
}

bool position::is_inbound()
{
    if ((0 <= row) && (row <= 7) && (0 <= col) && (col <= 7))
    {
        return true;
    }
    return false;
}

bool position::operator==(const position &rhs) const
{
    if ((rhs.col == col) && (rhs.row == row))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool position::operator!=(const position &rhs) const
{
    return !(position::operator==(rhs));
}

bool position::operator<(const position &rhs) const
{
    return (row+ROW*col) < (rhs.row+ROW*rhs.col);
}