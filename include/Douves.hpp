#ifndef DOUVES_HPP
#define DOUVES_HPP
#include "ActionReaction.hpp"

class Douves : public ActionReaction{

public : 
    Douves(); 
    ~Douves(); 

    void afficher() const override; 
}; 

#endif 