#ifndef CARTE_HPP
#define CARTE_HPP
#include "Joueur.hpp"
//#include "Plateau.hpp"

#include <string> 

class Joueur;
class Plateau; 

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

    // permet de jouer la carte pour les cartes ayant des actions plus complexes en interraction
    // avec le plateau 
    virtual void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau); 
}; 

#endif 
