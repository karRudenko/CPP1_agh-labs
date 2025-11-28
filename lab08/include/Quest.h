#ifndef QUEST_H
#define QUEST_H
#ifdef NDEBUG
#define DEBUG_PRINT(msg)
#else
#define DEBUG_PRINT(msg) std::cout << msg << std::endl;
#endif

#include <iostream>
#include "Reward.h"

// @brief class quest has 3 private variables which could be changed
// this class contain info about name, description and rewards
class Quest{
    private:
    std::string q_name;
    std::string q_opis;
    Reward q_reward;

    public:
    // the defaulte constructor was deleted
    Quest() = delete;
    // constructor work even if user doesnt indicate a reward
    Quest(std::string const& name, std::string const& opis, Reward const& reward = Reward()): q_name(name), q_opis(opis), q_reward(reward){}
    ~Quest() = default;

    //@brief print the variables in class
    void print() const;
    //@brief change variable "q_reward" with another parameters
    //@param variable from class Reward
    void changeReward(Reward const& reward);
    //@brief add variable reward to Q_reward from class
    //@param variable from class Reward
    void addReward(Reward const& reward);


    //@brief return the name of class
    std::string const& getName() const;
    //@brief return the description of class
    std::string const& getDescription() const;
    //@brief return the reward of class
    Reward const& getReward() const;
};

#endif // QUEST_H
