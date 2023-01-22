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
bool log = false;
string log_file;
string prg_name("");

//TODO: Implement the usage
void usage()
{
    cout << "OTHELLO Program, version: " << version << "\n";
    cout << "Usage: " << prg_name << " [OPTIONS] file...\n\n";
    cout << "Brief explanation:\n\n";     //TODO
    cout << "\
Option      Long option     Meaning\n\
-h          --help          Display this usage\n\
-v          --verbose       Output more information to terminal\n\
-b          --blind         Disable the board output to terminal\n\
-c          --cpu           Enables a match against a CPU\n\
-l [FILE]   --log [FILE]    Specify the log outout\n";
}

// -c [level]  --cpu [level]   Enables a match against a CPU. Higher the level, the stronger\n";

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
        log = true;
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
        log = true;
        log_file = temp;
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


    /* Display the title screen and the options */
    title(verbose, cpu, blind, log, log_file);

    cout << "\nThe options can be changed at runtime. \"./othello -h\" for more information\n";
    cout << "Do you want to continue? [y/n]";
    char ans;
    std::cin >> ans;

    if (ans != 'y')
    {
        return 0;
    }
    


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

    cout << "CPU vs CPU\n" << "Depth=" << 5 << "\nScorescheet no: " << scoresheet_no << "\n";
    display(myboard);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 30; i++)
    {
        cout << "Starting calculations for white...\n";
        std::chrono::steady_clock::time_point w_start = std::chrono::steady_clock::now();
        position pos = mybrain.think(myboard, WHITE);
        myboard = myboard.place(pos, WHITE);
        display(myboard);
        std::chrono::steady_clock::time_point w_done = std::chrono::steady_clock::now();
        cout << "Elapsed time =       " << std::chrono::duration_cast<std::chrono::microseconds>(w_done - w_start).count() << "[µs]" << std::endl;
        cout << "Total elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(w_done - begin).count() << "[µs]" << std::endl;


        cout << "Starting calculations for black...\n";
        std::chrono::steady_clock::time_point b_start = std::chrono::steady_clock::now();
        pos = mybrain.think(myboard, BLACK);
        myboard = myboard.place(pos, BLACK);
        display(myboard);
        std::chrono::steady_clock::time_point b_done = std::chrono::steady_clock::now();
        cout << "Elapsed time =       " << std::chrono::duration_cast<std::chrono::microseconds>(b_done - b_start).count() << "[µs]" << std::endl;
        cout << "Total elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(b_done - begin).count() << "[µs]" << std::endl;
    }
    
    

    return 0;
}