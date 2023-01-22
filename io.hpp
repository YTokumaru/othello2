#ifndef IO
#define IO

#include "all.hpp"
#include "board.hpp"

void title(bool verbose, bool cpu, bool blind, bool do_log, string log_file, string version);
void display(const board &b);

#endif // IO