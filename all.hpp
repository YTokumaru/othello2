#ifndef ALL
#define ALL

#include <iostream>
#include <stdint.h>
#include <map>
#include <string>
#include <any>

#define DEBUG


using std::string;
using std::cout;
using std::to_string;

//Colour Schemes:
typedef int8_t colour;
constexpr colour BLACK = -1;
constexpr colour WHITE = 1;
constexpr colour EMPTY = 0;

// These values are defied here to avid the usage of magic numbers
constexpr int ROW = 8;      // Number of rows in a board
constexpr int COL = 8;      // Number of columns in a board

// exception handling
//base class
class base_exception
{
public:
    const string msg;
    base_exception(const string &msg): msg(msg) {};
    //~base_exception();
};

// error raised when the board is at a state it shouldn't be
class illegal_board: base_exception
{
public:
    illegal_board(const string &mgs): base_exception(msg) {};
    //~illegal_board();
};


#endif // ALL