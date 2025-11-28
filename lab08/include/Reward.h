#ifndef REWARD_H
#define REWARD_H
#include <iostream>

//@brief struct with 3 area, and 2 constructor
struct Reward{
    int expirience;
    int salary;
    std::string recieved_thingth;

    // first constructor is default
    Reward() = default;
    // second is specified
    Reward(int exp, int sal, std::string const& thingth) : expirience(exp), salary(sal), recieved_thingth(thingth) {}
};

#endif // REWARD_H
