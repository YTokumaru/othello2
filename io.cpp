#include "io.hpp"

bool isOptPresent(char **start, char **end, const string option)
{
    return std::find(start, end, option) != end;
}

char *getOption(char **start, char **end, const string option)
{
    char **itr = std::find(start, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}

position userInput(const bool &cpu, const colour &clr, const board &b)
{

    // input sanitizing
    while (true)
    {
        // prompt
        if (cpu)
        {
            cout << "Player, please input position (white): row column: ";
        }
        else if (clr == WHITE)
        {
            cout << "Player 1, please input position (white): row column: ";
        }
        else
        {
            cout << "Player 2, please input position (black): row column: ";
        }

        int col, row;

        if (!(std::cin >> row >> col))
        {
            std::cin.clear();
            cout << "Unexpected input. Please try agin.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (row < 0 || col < 0 || row > ROW || col > COL)
        {
            cout << "Position out of bounds. Please try again\n";
        }
        else if (b.place(position(row,col), clr) == b)
        {
            cout << "Invalid move. Please try again.\n";
        }
        else
        {
            return position(row,col);
        }
    }
    
}

void title(bool verbose, bool cpu, bool blind, bool do_log, string log_file, string version)
{
    cout <<  "\
        THE STRATEGY GAME\n\
       █  ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄▄     ▄▄▄     ▄▄▄▄▄▄▄  ███████\n\
      ██ █       █       █  █ █  █       █   █   █   █   █       █ ██████\n\
     ███ █   ▄   █▄     ▄█  █▄█  █    ▄▄▄█   █   █   █   █   ▄   █ █████\n\
    ████ █  █ █  █ █   █ █       █   █▄▄▄█   █   █   █   █  █ █  █ ████\n\
   █████ █  █▄█  █ █   █ █   ▄   █    ▄▄▄█   █▄▄▄█   █▄▄▄█  █▄█  █ ███\n\
  ██████ █       █ █   █ █  █ █  █   █▄▄▄█       █       █       █ ██\n\
 ███████ █▄▄▄▄▄▄▄█ █▄▄▄█ █▄▄█ █▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█ █\n";

    cout << "Version " << version << "\n\n";

    cout << "Game settings:\n";
    if (verbose)
    {
        cout << "Verbose:   Enabled -   Displaying additional information to console\n";
    }
    else
    {
        cout << "Verbose:   Disabled -  No additional information to console\n";
    }

    if (cpu)
    {
        cout << "CPU:       Enabled -   A player vs CPU match\n";
    }
    else
    {
        cout << "CPU:       Disabled -  A player vs player match\n";
    }

    if (blind)
    {
        cout << "Blind:     Enabled -   Disabling board output to console\n";
    }
    else
    {
        cout << "Blind:     Disabled -  Board is output to console\n";
    }

    if (do_log)
    {
        cout << "log:       Enabled -   Output the match to file " << log_file << std::endl;
    }
    else
    {
        cout << "log:       Disabled -  The results are not recorded" << std::endl;
    }
    
    
    
}

void display(const board &b)
{
    string retstr   = "";

    const string top      = "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓";
    const string middle   = "┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫";
    const string bottom   = "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛";
    const string sep      = "┃";
    const string white    = "●";
    const string black    = "○";
    const int PADDLEN = 4;
    const string paddstr(PADDLEN, ' ');

    retstr += (paddstr + top + '\n');

    for (int row = 0; row < ROW; row++)
    {
        // add row number
        retstr += (string(PADDLEN-2, ' ') + to_string(row) + ' ');

        // add first separator
        retstr += sep;

        for (int col = 0; col < COL; col++)
        {
            retstr += ' ';
            
            switch (b.at(position(row,col)))
            {
            case WHITE:
                retstr += white;
                break;
            
            case BLACK:
                retstr += black;
                break;

            case EMPTY:
                retstr += ' ';
                break;
            }

            retstr += (' ' + sep);
        }
        retstr += '\n';
        
        if (row == ROW-1)
        {
            retstr += (paddstr + bottom + '\n');
        }
        else
        {
            retstr += (paddstr + middle + '\n');
        }
    }
    // add column number
    retstr += paddstr;
    for (int i = 0; i < COL; i++)
    {
        retstr += (string(2, ' ') + to_string(i) + ' ');
    }
    retstr += '\n';

    cout << retstr << std::endl;
}