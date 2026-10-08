#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Carte.hpp"

#include <vector>


// liste -> deck
// list -> defause
class Joueur {
    private:
        std::vector<std::unique_ptr<Carte>> deck;
        std::vector<std::unique_ptr<Carte>> main;
        std::vector<std::unique_ptr<Carte>> defause;

    public:
        Joueur(const std::vector<std::unique_ptr<Carte>>& deck);
        ~Joueur();

        void piocher();
        void melanger();

        void ajouterCarte(std::unique_ptr<Carte> carte);
}; 

#endif 