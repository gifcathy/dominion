#ifndef ACTIONREACTION_HPP
#define ACTIONREACTION_HPP
#include "Carte.hpp"

class ActionReaction : public Carte {

public : 
    ActionReaction(const std::string& nom_carte, const std::string& type_carte, const int& cout_carte);
    virtual ~ActionReaction();

}; 

#endif 