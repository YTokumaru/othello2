#include "all.hpp"
#include "board.hpp"
#include "position.hpp"
#include "io.hpp"
#include "brain.hpp"
#include "hard_coded.hpp"
#include "minimax.hpp"

string version = "alpha";

// Command line argumnets
bool verbose = false;
bool blind = false;
bool cpu = false;
bool do_log = false;
string log_file("");
string prg_name("");

// Usage
void usage()
{
    cout << "OTHELLO Program, version: " << version << "\n";
    cout << "Usage: " << prg_name << " [OPTIONS] file...\n\n";
    //cout << "Brief explanation:\n\n";     //TODO
    cout << "\
Option      Long option     Meaning\n\
-h          --help          Display this usage\n\
-v          --verbose       Output more information to terminal\n\
-b          --blind         Disable the board output to terminal\n\
-c          --cpu           Enables a match against a CPU\n\
-l [FILE]   --log [FILE]    Specify the log outout\n";
}

// TODO implement Deep Q network
// -c [level]  --cpu [level]   Enables a match against a CPU. Higher the level, the stronger\n";


/* The Othello game*/
int main(int argc, char *argv[])
{
    prg_name = argv[0];

    // Parsing arguments:
    if(isOptPresent(argv, argv+argc, "-h") || isOptPresent(argv, argv+argc, "--help"))
    {
        usage();
        return 0;
    }

    if (isOptPresent(argv, argv+argc, "-l"))
    {
        string temp = getOption(argv, argv+argc, "-l")? getOption(argv, argv+argc, "-l") : "";
        if (temp.empty() || temp.at(0) == '-')
        {
            std::cerr << "Expected a filename after the option \"-l / --log\"\n";
            return 1;
        }
        do_log = true;
        log_file = temp;

    }
    if (isOptPresent(argv, argv+argc, "--log"))
    {
        string temp = getOption(argv, argv+argc, "--log")? getOption(argv, argv+argc, "--log"): "";
        if (temp.empty() || temp.at(0) == '-')
        {
            std::cerr << "Expected a filename after the option \"-l / --log\"\n";
            return 1;
        }
        do_log = true;
        log_file = temp;
    }
    if (do_log)
    {
        std::filesystem::path log_path(log_file);
        if (std::filesystem::exists(log_path))
        {
            cout << "File named " << log_file << " already exists. Do you want to modify? [y/n]";
            char ans;
            std::cin >> ans;
            if (ans != 'y')
            {
                return 0;
            }
            cout << std::endl;
        }
    }
    
    

    if(isOptPresent(argv, argv+argc, "-v") || isOptPresent(argv, argv+argc, "--verbose"))
    {
        verbose = true;
    }

    if(isOptPresent(argv, argv+argc, "-b") || isOptPresent(argv, argv+argc, "--blind"))
    {
        blind = true;
    }

    if(isOptPresent(argv, argv+argc, "-c") || isOptPresent(argv, argv+argc, "--cpu"))
    {
        cpu = true;
    }

    std::ofstream logstrm(log_file);

    /* Display the title screen and the options */
    title(verbose, cpu, blind, do_log, log_file, version);

    cout << "\nThe options can be changed at runtime. \"./othello -h\" for more information\n";
    cout << "Do you want to continue? [y/n]";
    char ans;
    std::cin >> ans;

    if (ans != 'y')
    {
        return 0;
    }



    /* LET THE GAMES BEGIN!*/
    cout << "\nStarting game...\n" << std::endl;
    
    // Initialize board
    board myboard;
    myboard.edit(position(3,3), WHITE);
    myboard.edit(position(4,4), WHITE);
    myboard.edit(position(3,4), BLACK);
    myboard.edit(position(4,3), BLACK);

    // Brain args
    std::map<string, std::any> searcharg = {
        {"depth",5}         // the depth to read until     
    };
    
    int scoresheet_no = 0;
    std::map<string, std::any> evalarg = {
        {"score_sheet", scoresheet_no}
    };

    // initialize brain
    brain<minimax<hard_coded>> mybrain(searcharg, evalarg);

    if(blind) {display(myboard);}
    // vs CPU
    // Note that player always goes first and is white.
    std::chrono::steady_clock::time_point game_start = std::chrono::steady_clock::now();

    if (cpu)
    {
        while (mybrain.placable(myboard, WHITE) || mybrain.placable(myboard, BLACK))
        {
            // Player turn
            if (mybrain.placable(myboard, WHITE) == true)
            {
                if(!blind) {display(myboard);}
                std::chrono::steady_clock::time_point trurn_start = std::chrono::steady_clock::now();
                position input = userInput(cpu, WHITE, myboard);
                std::chrono::steady_clock::time_point turn_end = std::chrono::steady_clock::now();

                myboard = myboard.place(input, WHITE);
                cout << "White placed at " << int(input.row) <<" "<< int(input.col) << "\n";

                //Display time
                if (verbose)
                {
                    cout << "Turn time =       " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - trurn_start).count() << "[ms]" << std::endl;
                    cout << "Elapsed time =    " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - game_start).count() << "[ms]" << std::endl;
                }

                //log to file
                if(do_log) {logstrm << "WHITE" << ',' << int(input.row) << ',' << int(input.col) << std::endl;}
            }
            else
            {
                cout << "Player cannot place any pieces... Changing to CPU's turn.\n";
            }

            // cpu turn
            std::chrono::steady_clock::time_point trurn_start = std::chrono::steady_clock::now();
            position optimal = mybrain.think(myboard, BLACK);
            if (optimal.is_inbound())
            {
                if(!blind) {display(myboard);}
                cout << "CPU's turn\n";
                cout << "Black placed at " << int(optimal.row) <<" "<< int(optimal.col) << "\n";
                if(verbose) 
                {
                    std::chrono::steady_clock::time_point turn_end = std::chrono::steady_clock::now();
                    cout << "Turn time =       " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - trurn_start).count() << "[ms]" << std::endl;
                    cout << "Elapsed time =    " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - game_start).count() << "[ms]" << std::endl;
                }
                myboard = myboard.place(optimal, BLACK);
                if(do_log) {logstrm << "BLACK" << ',' << int(optimal.row) << ',' << int(optimal.col) << std::endl;}
            }
            else
            {
                cout << "CPU cannot place any pieces... Changing to player's turn.\n";
            }
        }

    }
    else
    // vs player
    {
        while (mybrain.placable(myboard, WHITE) || mybrain.placable(myboard, BLACK))
        {
            // Player turn
            if (mybrain.placable(myboard, WHITE) == true)
            {
                if(!blind) {display(myboard);}
                std::chrono::steady_clock::time_point trurn_start = std::chrono::steady_clock::now();
                position input = userInput(cpu, WHITE, myboard);
                std::chrono::steady_clock::time_point turn_end = std::chrono::steady_clock::now();

                myboard = myboard.place(input, WHITE);
                cout << "White placed at " << int(input.row) <<" "<< int(input.col) << "\n";

                //Display time
                if (verbose)
                {
                    cout << "Turn time =       " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - trurn_start).count() << "[ms]" << std::endl;
                    cout << "Elapsed time =    " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - game_start).count() << "[ms]" << std::endl;
                }

                //log to file
                if(do_log) {logstrm << "WHITE" << ',' << int(input.row) << ',' << int(input.col) << std::endl;}
            }
            else
            {
                cout << "Player1 cannot place any pieces... Changing to Player2's turn.\n";
            }

            // Player2 turn
            if (mybrain.placable(myboard, BLACK) == true)
            {
                if(!blind) {display(myboard);}
                std::chrono::steady_clock::time_point trurn_start = std::chrono::steady_clock::now();
                position input = userInput(cpu, BLACK, myboard);
                std::chrono::steady_clock::time_point turn_end = std::chrono::steady_clock::now();

                myboard = myboard.place(input, BLACK);
                cout << "White placed at " << int(input.row) <<" "<< int(input.col) << "\n";

                //Display time
                if (verbose)
                {
                    cout << "Turn time =       " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - trurn_start).count() << "[ms]" << std::endl;
                    cout << "Elapsed time =    " << std::chrono::duration_cast<std::chrono::milliseconds>(turn_end - game_start).count() << "[ms]" << std::endl;
                }

                //log to file
                if(do_log) {logstrm << "BLACK" << ',' << int(input.row) << ',' << int(input.col) << std::endl;}
            }
            else
            {
                cout << "Player2 cannot place any pieces... Changing to Player1's turn.\n";
            } 
        }
    }
    display(myboard);

    cout << "The game has ended. Counting pieces...\n" << std::endl;

    sleep(3);       // For some dramatic effect

    //count the scores:
    int white = 0;
    int black = 0;
    for (size_t row = 0; row < ROW; row++)
    {
        for (size_t col = 0; col < COL; col++)
        {
            switch (myboard.at(position(row,col)))
            {
            case WHITE:
                white ++;
                break;
            case BLACK:
                black ++;
                break;
            default:
                break;
            }
        }
    }
    cout << "White : Black = " << white << " : " << black << std::endl; 
    if (white > black)
    {
        cout << "White has won!" << std::endl;
    }
    if (white < black)
    {
        cout << "Black has won!" << std::endl;
    }
    if (white == black)
    {
        cout << "It's a draw!" << std::endl;
    }
    logstrm.close();

    return 0;
}