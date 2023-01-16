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
    // position a(2,3);
    // position b = a.below();

    // cout << sizeof(position) << "\n" << sizeof(board) << "\n";
    // cout << unsigned(a.row) << unsigned(a.col) << '\n';
    // cout << unsigned(b.row) << unsigned(b.col) << std::endl;

    // display debug
    board myboard;
    myboard.edit(position(3,3), WHITE);
    myboard.edit(position(4,4), WHITE);
    myboard.edit(position(3,4), BLACK);
    myboard.edit(position(4,3), BLACK);

    // myboard = myboard.place(position(5,4), BLACK);


    // myboard = myboard.place(position(5,5), WHITE);

    // display(myboard);

    // hard_coded evaluator debug
    // hard_coded eval;
    // double score = eval.evaluate(myboard, BLACK);
    // cout << score << '\n';


    // Brain debug
    int depth = 9;
    std::map<string, std::any> searcharg = {
        {"depth",depth}
    };
    
    int scoresheet_no = 0;
    std::map<string, std::any> evalarg = {
        {"score_sheet", scoresheet_no}
    };

    brain<minimax<hard_coded>> mybrain(searcharg, evalarg);



    // position best = mybrain.think(myboard, WHITE);
    // myboard = myboard.place(best, WHITE);
    // display(myboard);

    // position pos = mybrain.think(myboard, BLACK);
    // myboard = myboard.place(pos, BLACK);
    // display(myboard);

    cout << "CPU vs CPU\n" << "Depth=" << depth << "\nScorescheet no: " << scoresheet_no << "\n";
    display(myboard);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 30; i++)
    {
        cout << "Starting calculations for white...\n";
        std::chrono::steady_clock::time_point w_start = std::chrono::steady_clock::now();
        position pos = mybrain.think(myboard, WHITE);
        myboard = myboard.place(pos, WHITE);
        display(myboard);
        std::chrono::steady_clock::time_point w_done = std::chrono::steady_clock::now();
        cout << "Elapsed time =       " << std::chrono::duration_cast<std::chrono::microseconds>(w_done - w_start).count() << "[µs]" << std::endl;
        cout << "Total elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(w_done - begin).count() << "[µs]" << std::endl;


        cout << "Starting calculations for black...\n";
        std::chrono::steady_clock::time_point b_start = std::chrono::steady_clock::now();
        pos = mybrain.think(myboard, BLACK);
        myboard = myboard.place(pos, BLACK);
        display(myboard);
        std::chrono::steady_clock::time_point b_done = std::chrono::steady_clock::now();
        cout << "Elapsed time =       " << std::chrono::duration_cast<std::chrono::microseconds>(b_done - b_start).count() << "[µs]" << std::endl;
        cout << "Total elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(b_done - begin).count() << "[µs]" << std::endl;
    }
    
    

    return 0;
}