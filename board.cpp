#include "board.hpp"

/**Note that bitshifts do not work expectedly for uint_8,
 * because they get promoted into int.
 * This problem is worked around by changing 
 * data_in_uint_8 >> some_integer
 * into
 * data_in_uint8_t = data_in_uint_8 >> some_integer
 */


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

bool board::operator==(const board &rhs)
{
    if (this == &rhs)
    {
        return true;
    }
    
    for (size_t i = 0; i < ROW; i++)
    {
        if (white[i] != rhs.white[i]) {return false;}
        if (black[i] != rhs.black[i]) {return false;}
    }
    return true;
}

bool board::operator!=(const board &rhs)
{
    return !(board::operator==(rhs));
}

colour board::at(const position &pos) const
{
    #ifdef DEBUG
    validate();
    #endif //DEBUG

    uint8_t check = 0b10000000;
    check = check >> pos.col;

    if (black[pos.row] & check) {return BLACK;}
    else if (white[pos.row] & check) {return WHITE;}
    else {return EMPTY;}
}


void board::edit(const position &pos, const colour &clr)
{
    uint8_t modifier = 0b10000000;
    modifier = modifier >> pos.col;

    // MEMO: binary or
    if (clr == WHITE)
    {
        white[pos.row] = (white[pos.row] | modifier);
        black[pos.row] = (black[pos.row] & (~modifier));
    }
    else if (clr == BLACK)
    {
        black[pos.row] = (black[pos.row] | modifier);
        white[pos.row] = (white[pos.row] & (~modifier));
    }
    else
    {
        white[pos.row] = (white[pos.row] & (~modifier));
        black[pos.row] = (black[pos.row] & (~modifier));
    }

    #ifdef DEBUG
    validate();
    #endif //DEBUG
}

board board::place(const position &pos, const colour &clr)
{
    /**Returns the same board if it cannot be changed*/
    board retboard(*this);

    // if the position is not empty, it cannot be modified
    if (retboard.at(pos) != EMPTY)
    {
        return retboard;
    }


    if (retboard.at(pos.above()) == -clr)
    {
        for (position i = pos.above().above(); i.is_inbound(); i = i.above())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.below())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.below()) == -clr)
    {
        for (position i = pos.below().below(); i.is_inbound(); i = i.below())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.left())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.left()) == -clr)
    {
        for (position i = pos.left().left(); i.is_inbound(); i = i.left())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.right())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.right()) == -clr)
    {
        for (position i = pos.right().right(); i.is_inbound(); i = i.right())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.left())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.lower_left()) == -clr)
    {
        for (position i = pos.lower_left().lower_left(); i.is_inbound(); i = i.lower_left())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.lower_left())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.lower_left()) == -clr)
    {
        for (position i = pos.lower_left().lower_left(); i.is_inbound(); i = i.lower_left())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.upper_right())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.lower_right()) == -clr)
    {
        for (position i = pos.lower_right().lower_right(); i.is_inbound(); i = i.lower_right())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.upper_left())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }

    if (retboard.at(pos.upper_left()) == -clr)
    {
        for (position i = pos.upper_left().upper_left(); i.is_inbound(); i = i.upper_left())
        {
            if (!(i.is_inbound()))
            {
                break;
            }
            else if (retboard.at(i) == EMPTY)
            {
                break;
            }
            else if (retboard.at(i) == -clr)
            {
                continue;
            }
            else
            {
                retboard.edit(pos,clr);
                // going back to change the board
                for (position j = i; j != pos; j = j.lower_right())
                {
                    retboard.edit(j,clr);
                }
                break;
            }
        }
    }
    
    #ifdef DEBUG
    retboard.validate();
    #endif //DEBUG

    return retboard;
}

void board::validate() const
{
    for (size_t i = 0; i < ROW; i++)
    {
        if (black[i] & white[i])
        {
            throw illegal_board("Black tile and white tile on the same position");
        }
    }
}