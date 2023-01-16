#ifndef HARD_CODED
#define HARD_CODED

#include "all.hpp"
#include "position.hpp"
#include "board.hpp"

/* The hardcoded scores */
const std::map<position, double> SCORE_SHEET_0{
    {position(0,0), 1},
    {position(0,1), 1},
    {position(0,2), 1},
    {position(0,3), 1},
    {position(0,4), 1},
    {position(0,5), 1},
    {position(0,6), 1},
    {position(0,7), 1},

    {position(1,0), 1},
    {position(1,1), 1},
    {position(1,2), 1},
    {position(1,3), 1},
    {position(1,4), 1},
    {position(1,5), 1},
    {position(1,6), 1},
    {position(1,7), 1},

    {position(2,0), 1},
    {position(2,1), 1},
    {position(2,2), 1},
    {position(2,3), 1},
    {position(2,4), 1},
    {position(2,5), 1},
    {position(2,6), 1},
    {position(2,7), 1},

    {position(3,0), 1},
    {position(3,1), 1},
    {position(3,2), 1},
    {position(3,3), 1},
    {position(3,4), 1},
    {position(3,5), 1},
    {position(3,6), 1},
    {position(3,7), 1},

    {position(4,0), 1},
    {position(4,1), 1},
    {position(4,2), 1},
    {position(4,3), 1},
    {position(4,4), 1},
    {position(4,5), 1},
    {position(4,6), 1},
    {position(4,7), 1},

    {position(5,0), 1},
    {position(5,1), 1},
    {position(5,2), 1},
    {position(5,3), 1},
    {position(5,4), 1},
    {position(5,5), 1},
    {position(5,6), 1},
    {position(5,7), 1},

    {position(6,0), 1},
    {position(6,1), 1},
    {position(6,2), 1},
    {position(6,3), 1},
    {position(6,4), 1},
    {position(6,5), 1},
    {position(6,6), 1},
    {position(6,7), 1},

    {position(7,0), 1},
    {position(7,1), 1},
    {position(7,2), 1},
    {position(7,3), 1},
    {position(7,4), 1},
    {position(7,5), 1},
    {position(7,6), 1},
    {position(7,7), 1},
};

const std::map<position, double> SCORESHEETS[1] = {
    SCORE_SHEET_0
};


/**Expecting arguments:
 * Name             | About
 * score_sheet      | Number of scoresheet to use
*/
class hard_coded
{
private:
    const int scoresheet;
public:
    hard_coded(): scoresheet(0){}
    hard_coded(const std::map<string, std::any> &args): scoresheet(std::any_cast<int>(args.at("score_sheet"))) {};
    //~hard_coded();

    /**The evaluation method is as follows:
     * Let B be the sum of the score on each black tile.
     * Let W be the sum if the score on each white tile.
     * The score of the board S is given by
     * S = (W-B)/(1+|W-B|)
    */
    double evaluate(const board &b, const colour &clr) const;
};


#endif // HARD_CODED