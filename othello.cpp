#include "all.hpp"
#include "board.hpp"
#include "position.hpp"
#include "io.hpp"
#include "brain.hpp"
#include "hard_coded.hpp"
#include "minimax.hpp"

int main(int argc, char **argv)
{
    //position debug
    position a(2,3);
    position b = a.below();

    cout << sizeof(position) << "\n" << sizeof(board) << "\n";
    cout << unsigned(a.row) << unsigned(a.col) << '\n';
    cout << unsigned(b.row) << unsigned(b.col) << std::endl;

    // display debug
    board myboard;
    myboard.edit(position(3,3), WHITE);
    myboard.edit(position(4,4), WHITE);
    myboard.edit(position(3,4), BLACK);
    myboard.edit(position(4,3), BLACK);

    // myboard = myboard.place(position(5,4), BLACK);

    display(myboard);

    // myboard = myboard.place(position(5,5), WHITE);

    // display(myboard);

    // hard_coded evaluator debug
    hard_coded eval;
    double score = eval.evaluate(myboard, BLACK);
    cout << score << '\n';


    // Brain debug
    std::map<string, std::any> searcharg = {
        {"depth", 17}
    };

    std::map<string, std::any> evalarg = {
        {"score_sheet", 0}
    };

    brain<minimax<hard_coded>> mybrain(searcharg, evalarg);



    // position best = mybrain.think(myboard, WHITE);
    // myboard = myboard.place(best, WHITE);
    // display(myboard);

    // position pos = mybrain.think(myboard, BLACK);
    // myboard = myboard.place(pos, BLACK);
    // display(myboard);

    
    for (int i = 0; i < 30; i++)
    {
        position pos = mybrain.think(myboard, WHITE);
        myboard = myboard.place(pos, WHITE);
        display(myboard);

        pos = mybrain.think(myboard, BLACK);
        myboard = myboard.place(pos, BLACK);
        display(myboard);
    }
    
    

    return 0;
}