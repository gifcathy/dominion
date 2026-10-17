#ifndef ACTION_HPP
#define ACTION_HPP
#include "Carte.hpp"

class Action : public Carte{

public : 
    Action(const std::string& nom_carte, const std::string& type_carte, const int& cout_carte);
    virtual ~Action();

};

#endif