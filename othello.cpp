#include "all.hpp"
#include "board.hpp"

int main(int argc, char **argv)
{
    position a(2,3);
    position b = a.below();

    cout << sizeof(position) << "\n" << sizeof(board) << "\n";
    cout << unsigned(a.row) << unsigned(a.col) << '\n';
    cout << unsigned(b.row) << unsigned(b.col) << std::endl;

    return 0;
}