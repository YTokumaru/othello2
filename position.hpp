#ifndef POSITION
#define POSITION

#include "all.hpp"

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

    position();
    position(const uint8_t &x, const uint8_t &y);
    position & operator=(const position &rhs);

    //~position();

    // check if the position is in bounds
    bool is_inbound();

    bool operator==(const position &rhs) const;
    bool operator!=(const position &rhs) const;
    bool operator<(const position &rhs) const;

    // The methods below return the positions relative to this
    //does not check for edges
    position above()       const {return position(row-1, col  );};
    position below()       const {return position(row+1, col  );};
    position left()        const {return position(row  , col-1);};
    position right()       const {return position(row  , col+1);};
    position upper_right() const {return position(row-1, col+1);};
    position lower_left()  const {return position(row+1, col-1);};
    position lower_right() const {return position(row+1, col+1);};
    position upper_left()  const {return position(row-1, col-1);};
};

#endif // POSITION