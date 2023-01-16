#include "minimax.hpp"

template <class EVAL>
double minimax<EVAL>::search_next(board b, colour clr, int depth) const
{
    if (depth == MAX_DEPTH)
    {
        return EVAL::evaluate(b, clr);
    }
    
    // if depth is odd, then minimize
    if (!(depth & 1))
    {
        double max = -1*clr;

        for (int row = 0; row < ROW; row++)
        {
            for (int col = 0; col < COL; col++)
            {
                board next_b = b.place(position(row,col),-clr); // Place the opposite colour on the next move

                // if the move was valid and the piece was placed
                if(b != next_b)
                {
                    double score = search_next(next_b, clr, depth+1);      

                    if (std::abs(clr-score) < std::abs(clr-max))
                    // Closer the score is to 1*clr, the better
                    {
                        max = score;
                    }
                }
            }
        }
        return max;
    }
    // if it is even, maximize
    else
    {
        double min = 1*clr;

        for (int row = 0; row < ROW; row++)
        {
            for (int col = 0; col < COL; col++)
            {
                board next_b = b.place(position(row,col),clr);  // Place the same colour on the next move

                // if the move was valid and the piece was placed
                if(b != next_b)
                {
                    double score = search_next(next_b, clr, depth+1);      

                    if (std::abs(clr-score) > std::abs(clr-min))
                    // Further the score is to col, the Worse
                    {
                        min = score;
                    }
                }
            }
        }
        return min;
    }
    
}

template <class EVAL>
position minimax<EVAL>::find(const board &b,const colour &clr) const
{
    double best_score = -clr;
    position optimal(15,15);
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            board next_b = b.place(position(row,col), clr);
            if (next_b != b)
            {
                double score = search_next(next_b, clr, 1);
                if (std::abs(clr-score) <= std::abs(clr-best_score))
                {
                    best_score = score;
                    optimal = position(row,col);
                }
            }
        }
        
    }
    return optimal;
}
    

// explicit instantiations
template class minimax<hard_coded>;