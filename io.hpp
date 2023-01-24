#ifndef IO
#define IO

#include "all.hpp"
#include "board.hpp"
#include "position.hpp"

bool isOptPresent(char **start, char **end, const string option);
char *getOption(char **start, char **end, const string option);

position userInput(const bool &cpu, const colour &col, const board &b);

void title(bool verbose, bool cpu, bool blind, bool do_log, string log_file, string version);
void display(const board &b);

#endif // IO