#ifndef BRAIN
#define BRAIN

#include "all.hpp"
#include "position.hpp"
#include "board.hpp"
#include "minimax.hpp"
#include "hard_coded.hpp"

/**Making your own searcher
 * A searcher class will be compatible with this program
 * as long as specs below are fullfilled:
 * 
 * 1. Has a evaluator template (it doesn't neccessarily have to use it)
 * 2. Has a method named "search" which takes arguments board and colour and 
 *    returns datatype position
*/

/**Making your own evaluator
 * An evaluator class will be compatible with this program
 * as long as specs below are fullfiilled
 * 
 * 1. Has a method named evaluate which takes arguments board and colour,
 *    and returns score in double between -1 and 1. The more favourable the
 *    state of the board is to black, the value should be closet to -1, and
 *    more favourble to white should the value be closet to 1.
*/



template <class SEARCH>
class brain : protected SEARCH
{
public:
    brain(const std::map<string, std::any> &searcharg, const std::map<string, std::any> &evalarg) : SEARCH(searcharg, evalarg) {}
    //~brain();

    // returns the optimal solution for a given board state and colour
    position think(const board &b, const colour &clr) const;
};


#endif // BRAIN