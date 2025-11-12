#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>
using namespace std;

//  those variables will be initialized in cpp file
extern int debugLevel;
extern bool verbose;

//  @brief logMessage print a massage where LOG is debugerLevel, 
//  "[VERBOSE]" will be written only if verbose = true
//  and function count how many times the function was called
//  @param string with massege
void logMessage(string xd);

#endif // CONFIG_H
