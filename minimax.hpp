#ifndef MINIMAX
#define MINIMAX

#include "all.hpp"
#include "board.hpp"
#include "hard_coded.hpp"

/**Minimax method
*/

/**Expecting arguments
 * Name         | Type      | About
 * depth        | int       | The depth you want to search to
*/
template <class EVAL>
class minimax : public EVAL
{
private:
    const int MAX_DEPTH;

    double search_next(board b, colour c, int depth) const;

public:
    minimax(std::map<string, std::any> args, std::map<string, std::any> evalargs): MAX_DEPTH(std::any_cast<int>(args.at("depth"))), EVAL(evalargs) {};
    //~minimax();
    position find(const board &b,const colour &clr) const;     // returns (-1,-1) when no moves can be made
};


#endif // MINIMAX