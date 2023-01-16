#include "brain.hpp"

template <class SEARCH>
position brain<SEARCH>::think(const board &b, const colour &clr) const
{
    return SEARCH::find(b,clr);
}

// Explicit template instantiation
template class brain<minimax<hard_coded>>;