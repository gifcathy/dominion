#ifndef ACTIONACTIONATTAQUE_HPP
#define ACTIONACTIONATTAQUE_HPP
#include "Carte.hpp"

class ActionActionAttaque : public Carte{

public : 
    ActionActionAttaque(const std::string& nom_carte, const std::string& type_carte, 
        const int& cout_carte);
    virtual ~ActionActionAttaque();

};

#endif