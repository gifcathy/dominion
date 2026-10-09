#ifndef BUCHERON_HPP
#define BUCHERON_HPP
#include "ActionActionAttaque.hpp"

class Bucheron : public ActionActionAttaque{

public : 
    Bucheron(); 
    ~Bucheron(); // les destructeur héritent du destructeur virtuel de carte et donc saura dans 
    // quel ordre il faudra les appeler 
}; 

#endif