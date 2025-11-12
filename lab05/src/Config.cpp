#include "Config.h"
#include <iostream>
#include <string>
using namespace std;

//  @brief debugLevel is shared with another file and could be modified somewhere
int debugLevel = 0;
//  @brief verbose also could be shared and mpdofied somewhere
bool verbose = false;


//  @brief logMessage print a massage where LOG is debugerLevel, 
//  "[VERBOSE]" will be written only if verbose = true
//  and function count how many times the function was called
//  @param string with massege
void logMessage(string xd){
    static int count = 0;
    cout << "[LOG:" << debugLevel << (verbose?"] [VERBOSE] #":"] #") << ++count << " " << xd << endl;
}