#ifndef ALL
#define ALL

#include <iostream>
#include <stdint.h>
#define DEBUG

using std::string;
using std::cout;

//Colour Schemes:
typedef uint8_t colour;
constexpr colour BLACK = 2;
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



class position
{
    /**Coordinate values x and y only take values
     * from 0 to 7, which can be represented with 
     * 3 bits. Smalleset size C++ allows structs
     * to be is 1 byte.
    */
    public:
    // The data of this class is made pulic for flexibility
    uint8_t row : 4;
    uint8_t col : 4;

    position() {row = 0, col = 0;};
    position(const uint8_t &x, const uint8_t &y) {row = x, col = y;}
    position & operator=(const position &rhs)
    {
        if (this == &rhs) {return *this;}
        row = rhs.row;
        col = rhs.col;
        return *this;
    }
    //~position();

    // The methods below return the positions relative to this
    //does not check for edges
    position above()        {return position(row-1, col  );};
    position below()        {return position(row+1, col  );};
    position left()         {return position(row  , col-1);};
    position right()        {return position(row  , col+1);};
    position upper_right()  {return position(row-1, col+1);};
    position lower_left()   {return position(row+1, col-1);};
    position lower_right()  {return position(row+1, col+1);};
    position upper_left()   {return position(row-1, col-1);};
};


#endif // ALL