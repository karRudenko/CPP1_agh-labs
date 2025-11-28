#include "Quest.h"
#include <iostream>

// print all parametrs in class
void Quest::print() const{
    std::cout<<"Quest: "<<q_name<<std::endl;
    std::cout<<"Opis: "<<q_opis<<std::endl;
    std::cout<<"Nagroda: "<<q_reward.expirience<<" punktów doświadczenia, "<<q_reward.salary<<" sztuk rudy, Otrzymane przedmioty: "<<(q_reward.recieved_thingth == ""?"brak":q_reward.recieved_thingth) << std::endl<<std::endl;
}
// change q_reward with new value
void Quest::changeReward(Reward const& reward){
    q_reward = reward;
}
//add new value to q_reward
void Quest::addReward(Reward const& reward) {
    q_reward.expirience += reward.expirience;
    q_reward.salary += reward.salary;
    if (!q_reward.recieved_thingth.empty() && !reward.recieved_thingth.empty()) {
        q_reward.recieved_thingth += "; ";
    }
    q_reward.recieved_thingth += reward.recieved_thingth;
}

// get class's name
std::string const& Quest::getName() const{
    return q_name;
}
// get class's description
std::string const& Quest::getDescription() const{
    return q_opis;
}
// get class's Reward
Reward const& Quest::getReward() const{
    return q_reward;
}

