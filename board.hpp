#ifndef BOARD
#define BOARD

#include "all.hpp"

/**Class board is a class used to represent the game board.
 * The class has mainly 3 menbers that get used frequently
 * 1. board_data
 * 2. at(position)
 * 3. place(position, colour)
 * 4. edit(position, colour)
 * 
 * board_data is an array that contains the state of the board.
 * However it is not a array of ints representing each tile.
 * Ints, is usually 4 bytes in many systems, is redundant to 
 * express empty, black, white states of the board. To reduce
 * the amount of memory consumed (at the expense of computation time), 
 * we will map state of a row to 8 bit unsigned integer. 
 * If the position of whites in a
 * row are as below, the integer co-responding will be
 * |●|●| |●| | | |●|
 *  1 1 0 1 0 0 0 1  (2)
 * The same applies to black tiles as well.
 * Reading the colour of a specific tile can be done by
 * bitwise operations.
 * 
 * at(position) returns the colour of the tile at given position
 * 
 * place(position, colour) places a piece on an empty tile,
 * and changes surrounding tiles accordingly.
 * This method does not change the board itsself, but RETURNS 
 * A BOARD WITH CHANGED STATE
 * 
 * edit(position, colour) changes the colour of the position
 * to the specified one, regardless of the board state.
 */ 

class board
{
private:
    // These data are row-oriented
    uint8_t black[ROW];
    uint8_t white[ROW];
public:
    board();                                // default constructor, assigns all to 0
    board(const board &otherbord);          // copy constructor
    board & operator=(const board &rhs);    // assignment operator
    //~board();

    colour at(const position &pos);
    board place(const position &pos, colour colr);
    

    // functions for debugging
    void validate();                        // Checks that there is only one colour in a tile. Throws an error

};
#endif // BOARD