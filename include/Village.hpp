#ifndef VILLAGE_HPP
#define VILLAGE_HPP
#include "ActionActionAttaque.hpp"

class Village : public ActionActionAttaque{

public :
    Village(); 
    ~Village(); 

    void afficher() const override; 
}; 

#endif 