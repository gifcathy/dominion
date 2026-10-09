#ifndef ATELIER_HPP
#define ATELIER_HPP
#include "ActionActionAttaque.hpp"

class Atelier : public ActionActionAttaque{

public : 
    Atelier(); 
    ~Atelier(); 

    void afficher() const override;

}; 

#endif