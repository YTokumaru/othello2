#include "all.hpp"
#include "board.hpp"
#include "position.hpp"
#include "io.hpp"
#include "brain.hpp"
#include "hard_coded.hpp"

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

    myboard = myboard.place(position(5,4), BLACK);

    display(myboard);

    // myboard = myboard.place(position(5,5), WHITE);

    // display(myboard);

    // hard_coded evaluator debug
    hard_coded eval;
    double score = eval.evaluate(myboard, BLACK);
    cout << score << '\n';


    return 0;
}