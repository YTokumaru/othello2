#include "board.hpp"

board::board()
{
    for (size_t i = 0; i < ROW; i++)
    {
        black[i] = 0;
        white[i] = 0;
    }
}

board::board(const board &otherboard)
{
    for (size_t i = 0; i < ROW; i++)
    {
        black[i] = otherboard.black[i];
        white[i] = otherboard.white[i];
    }
}

board & board::operator=(const board &rhs)
{
    // No need to copy if it is the same
    if (this == &rhs)
    {
        return *this;
    }


    for (size_t i = 0; i < ROW; i++)
    {
        black[i] = rhs.black[i];
        white[i] = rhs.white[i];
    }
    return *this;
}

colour board::at(const position &pos)
{
    #ifdef DEBUG
    validate();
    #endif //DEBUG

    uint8_t check = 0b10000000;
    check >> pos.col;

    if (black[pos.row] & check) {return BLACK;}
    if (white[pos.row] & check) {return WHITE;}
    return EMPTY;
}

board board::place(const position &pos, colour clr)
{
    // TODO
}

void board::validate()
{
    for (size_t i = 0; i < ROW; i++)
    {
        if (black[i] & white[i])
        {
            throw illegal_board("Black tile and white tile on the same position");
        }
    }
}