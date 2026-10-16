#include <iostream>
#include "Village.hpp"

// constructeur 
Village::Village() : ActionActionAttaque("Village", "Action", 3){}; 

// destructeur 
Village::~Village(){}; 

// méthode d'affichage 
void Village::afficher() const{
    std::cout << "Village - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 carte, + 2 actions" << std::endl;
}