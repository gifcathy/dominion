#ifndef PROVINCE_HPP
#define PROVINCE_HPP
#include "Victoire.hpp"

class Province : public Victoire {

public :
    Province(); 
    ~Province(); 

    void afficher() const override; 
}; 

#endif