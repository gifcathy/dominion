#ifndef CARTE_HPP
#define CARTE_HPP
#include "Joueur.hpp"

#include <string> 


class Carte{

private : 
    std::string nom;
    std::string type; 
    int cout; 

public :
    Carte(const std::string& nom_carte, const std::string& type_carte, const int& cout_carte); 
    virtual ~Carte(); 

    const std::string& getNom() const; 
    const std::string& getType() const; 
    const int& getCout() const; 

    virtual void afficher() const = 0; 

    // applique les actions de la carte sur le joueur 
    virtual void jouer(Joueur& joueur);
}; 

#endif 
