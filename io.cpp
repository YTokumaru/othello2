#include "io.hpp"

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