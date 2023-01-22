#ifndef IO
#define IO

#include "all.hpp"
#include "board.hpp"

void title(bool verbose, bool cpu, bool blind, bool log, string log_file);
void display(const board &b);

#endif // IO