#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Carte.hpp"

#include <iostream> 
#include <vector>
#include <memory>


class Joueur {
    private:
        std::vector<std::unique_ptr<Carte>> deck;
        std::vector<std::unique_ptr<Carte>> main;
        std::vector<std::unique_ptr<Carte>> defausse;

    public:
        Joueur(const std::vector<std::unique_ptr<Carte>>& deck);
        ~Joueur();

        void piocher();
        void melanger();
        void passerDefausseADeck();

        void ajouterCarte(std::unique_ptr<Carte> carte);
}; 

#endif 