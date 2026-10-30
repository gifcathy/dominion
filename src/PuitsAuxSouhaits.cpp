#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "PuitsAuxSouhaits.hpp"
#include "Plateau.hpp"

// constructeur 
PuitsAuxSouhaits::PuitsAuxSouhaits() : ActionPlateau("PuitsAuxSouhaits", "Action", 3){}; 

// destructeur 
PuitsAuxSouhaits::~PuitsAuxSouhaits(){}; 

// méthode d'affichage 
void PuitsAuxSouhaits::afficher() const{
    std::cout << "PuitsAuxSouhaits - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 action, +1 carte. Nomme une carte, révèle la première carte de "
              << "ton deck. Si c'est la carte que tu as nommé, ajoute la à ta main."<< std::endl;
}

// jouer la carte 
void PuitsAuxSouhaits::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    std::cout << "\n========================================\n";
    std::cout << "        CARTE : PUITS AUX SOUHAITS\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 action, +1 carte. Nomme une carte, révèle la première carte de "
              << "ton deck. Si c'est la carte que tu as nommé, ajoute la à ta main.\n\n"; 
    
    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel]; 

    // piocher une carte 
    std::unique_ptr<Carte> carte = joueurActuel.prendreCarteDessusDeck(); 
    if (carte != nullptr) {
        std::cout << "Vous avez pioché : \n" ; 
        std::cout << carte->getNom() << std::endl;
        joueurActuel.ajouterCarteMain(std::move(carte));
    }
    else {
        std::cout << "Vous ne pouvez plus piocher de carte." << std::endl;
    }
    
    // ajouter une action 
    joueurActuel.ajouterActions(1); 


    // nommer la carte 
    // Afficher les cartes que le joueur peut nommer
    std::cout << "\nVoici les cartes que vous pouvez nommer :\n";

    const auto& piles = plateau.getPiles();

    // affichage des noms des cartes sur le plateau
    for (const auto& pile : piles) {
        std::cout << "- " << pile.first << std::endl;
    }

    // Demander au joueur de nommer une carte
    std::string nomCarte;
    bool choixValide = false;
    while (!choixValide) {
        std::cout << "\nQuelle carte souhaitez-vous nommer ? ";
        std::cin >> std::ws;
        std::getline(std::cin, nomCarte);

        // Vérifier que la carte existe sur le plateau
        if (piles.find(nomCarte) != piles.end()) {
            choixValide = true;
        }
        else {
            std::cout << "Cette carte n'existe pas sur le plateau."
                      << "\nVeuillez choisir une carte dans la liste." << std::endl;
        }
    }

    // Révéler la première carte du deck
    std::unique_ptr<Carte> carteSuivante = joueurActuel.prendreCarteDessusDeck();

    if (carteSuivante == nullptr) {
        std::cout << "\nVous n'avez plus de carte à révéler." << std::endl;
        return;
    }

    std::cout << "\nVous révélez : " << carteSuivante->getNom() << std::endl;

    // Comparer avec la carte nommée
    if (carteSuivante->getNom() == nomCarte) {
        std::cout << "Bravo ! C'est la bonne carte ! Elle est ajoutée à votre main"<< std::endl;
        joueurActuel.ajouterCarteMain(std::move(carteSuivante));

    }
    else {
        std::cout << "Dommage ! Ce n'est pas la carte annoncée."<< std::endl;
        joueurActuel.ajouterCarteDessusDeck(std::move(carteSuivante));
    }
}

