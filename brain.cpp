#include "brain.hpp"

template <class SEARCH>
position brain<SEARCH>::think(const board &b, const colour &clr) const
{
    return SEARCH::find(b,clr);
}

template <class SEARCH>
bool brain<SEARCH>::placable(const board &b, const colour &clr) const
{
    position retpos(15,15);
    for (size_t row = 0; row < ROW; row++)
    {
        for (size_t col = 0; col < COL; col++)
        {
            if (b.place(position(row,col), clr) == b)
            {
                continue;
            }
            else
            {
                return true;
            }
            
        }
    }
    return false;
}

// Explicit template instantiation
template class brain<minimax<hard_coded>>;