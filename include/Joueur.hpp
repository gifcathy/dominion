#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <iostream> 
#include <vector>
#include <memory>
#include <cstddef>

class Carte;


class Joueur {
    private:
        std::vector<std::unique_ptr<Carte>> deck;
        std::vector<std::unique_ptr<Carte>> main;
        std::vector<std::unique_ptr<Carte>> defausse;
        std::vector<std::unique_ptr<Carte>> carteJouer;
        int argent;
        int action;
        int achat;
        int ptsVictoire; 

        //-- finalement pas utiliser on va juste verifier a chaque attauque les main des adverser avec une fonction
        //bool proteger;
        //bool verifierProtection;// verifier si elle existe  quand piocher carte verifier et quand ecarter remettre a

    public:
        Joueur(std::vector<std::unique_ptr<Carte>> deckInitial);
        Joueur(Joueur&&) = default;
        Joueur& operator=(Joueur&&) = default;
        ~Joueur() = default;

        int getArgent() const;
        int getAction() const;
        int getAchat() const;
        const std::vector<std::unique_ptr<Carte>>& getMain() const;
        const std::unique_ptr<Carte>& getCarte(std::size_t indice) const;
        const std::vector<std::unique_ptr<Carte>>& getCartesJouees() const; 

        void afficherMain(); 

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

        void ajouterPtsVictoire(int points); 

        void reinitialiserRessources();

        void jouerTresor(std::size_t indice);
        void jouerAction(std::size_t indice);

        void terminerTour();

        void ecarterCarteJouee(const Carte* carte); 

        bool possedeDouveEnMain() const;

}; 

#endif 