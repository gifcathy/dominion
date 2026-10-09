#include "Joueur.hpp"

#include <utility>
#include <algorithm> //contient std::shuffle
#include <random>

Joueur::Joueur(const std::vector<std::unique_ptr<Carte>>& deck) : deck(deck){}

void Joueur::piocher(){
    if (deck.empty()) {
        passerDefausseADeck();
    }

    if (deck.empty()) {
        return;
    }

    main.push_back(std::move(deck.back()));
    deck.pop_back();
}

/*  nouvelle main
for (int i = 0; i < 5; ++i) {
    piocher();
}
*/


void Joueur::melanger(){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(deck.begin(), deck.end(), gen);
}

void Joueur::passerDefausseADeck(){
    for (auto& carte : defausse) {
        deck.push_back(std::move(carte));
    }

    // Après les déplacements, le vecteur defause contient toujours ses anciens emplacements, mais leurs unique_ptr sont vides
    defausse.clear();

    melanger();
}

void Joueur::ajouterCarte(std::unique_ptr<Carte> carte){
    defausse.push_back(std::move(carte));
    std::cout << "carte ajouter a la defause" << std::endl;

    //Pour utiliser cette fonction, tu ferais par exemple :
    //joueur.ajouterCarte(std::make_unique<Cuivre>());
    //Cela crée un Cuivre et transfère directement sa propriété au joueur.
}

//mettre une carte a la defause
//defause.push_back(std::move(carte));