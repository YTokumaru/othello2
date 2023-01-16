#include "hard_coded.hpp"

double hard_coded::evaluate(const board &b, const colour &clr) const
{
    double b_total = 0;
    double w_total = 0;
    for (size_t row = 0; row < ROW; row++)
    {
        for (size_t col = 0; col < COL; col++)
        {
            switch (b.at(position(row,col)))
            {
            case BLACK:
                // b_total += SCORE_SHEET_0.at(position(row,col));
                b_total += std::any_cast<double>((SCORESHEETS[scoresheet]).at(position(row,col)));
                break;
            case WHITE:
                w_total += std::any_cast<double>((SCORESHEETS[scoresheet]).at(position(row,col)));
                break;
            
            default:
                break;
            }
        }
        
    }
    return (w_total-b_total)/(1+std::abs(w_total-b_total));
}