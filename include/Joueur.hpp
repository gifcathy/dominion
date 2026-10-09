#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include "Carte.hpp"

#include <iostream> 
#include <vector>
#include <memory>
#include <cstddef>


class Joueur {
    private:
        std::vector<std::unique_ptr<Carte>> deck;
        std::vector<std::unique_ptr<Carte>> main;
        std::vector<std::unique_ptr<Carte>> defausse;
        std::vector<std::unique_ptr<Carte>> carteJouer;
        int argent;
        int action;
        int achat;

    public:
        Joueur(std::vector<std::unique_ptr<Carte>> deckInitial);
        ~Joueur() = default;

        int getArgent() const;
        int getAction() const;
        int getAchat() const;

        void piocher();
        void piocherPlusieurCarte(int nb);
        void piocherNouvelleMain();

        void melanger();

        void passerDefausseADeck();

        void ajouterCarte(std::unique_ptr<Carte> carte);

        void defausserUneCarte(std::size_t indice);
        void ecarterCarte(std::size_t indice);

        void ajouterArgent(int montant);
        bool depenserArgent(int montant);

        void ajouterActions(int nb);
        bool depenserAction();

        void ajouterAchats(int nb);
        bool depenserAchat();

        void reinitialiserRessources();

        void jouerTresor(std::size_t indice);
        void jouerAction(std::size_t indice);

        void terminerTour();

}; 

#endif 