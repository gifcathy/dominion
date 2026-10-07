#ifndef CARTE_HPP
#define CARTE_HPP

class Carte{

private : 
    std::string nom; 
    int valeur; 
    std::string type; 
    int cout; 

public :
    Carte(const std::string& nom_carte, const int& valeur_carte, const std::string& type_carte, 
        const int& cout_carte); 
    ~Carte(); 

}; 

#endif 
