#include "Joueur.hpp"
#include "Carte.hpp"
#include "Tresor.hpp"

#include <utility>
#include <algorithm> //contient std::shuffle
#include <random>

Joueur::Joueur(std::vector<std::unique_ptr<Carte>> deckInitial) : deck(std::move(deckInitial)), argent(0), action(1), achat(1), ptsVictoire(3){
    
    melanger();
    piocherNouvelleMain();
}

int Joueur::getArgent() const{
    return argent;
}

int Joueur::getAction() const{
    return action;
}

int Joueur::getAchat() const{
    return achat;
}

const std::vector<std::unique_ptr<Carte>>& Joueur::getMain() const{
    return main;
}

const std::unique_ptr<Carte>& Joueur::getCarte(std::size_t indice) const{
    return main.at(indice);  //main[indice]; avec at on a des execption qui sont lever si probleme dans indice
}

const std::vector<std::unique_ptr<Carte>>& Joueur::getCartesJouees() const{
    return carteJouer; 
}

// permet d'afficher la main du joueur 
void Joueur::afficherMain(){
    //int nbCartesMainJoueur = static_cast<int>(main.size()); 
    std::cout << "votre main :" << std::endl; 
    for (std::size_t j = 0; j < main.size(); j++){
        std::cout << "[" << j << "]" << main[j]->getNom() << std::endl; 
    }
    
}

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

void Joueur::piocherPlusieurCarte(int nb){
    for (int i = 0; i < nb; ++i) {
        piocher();
    }
}

/*
Attention néanmoins : si tu appelles piocherNouvelleMain() alors que ta main contient encore des cartes, 
celles-ci restent dans la main. Il faudra donc gérer la fin du tour avant de piocher la nouvelle main.
*/
void Joueur::piocherNouvelleMain(){
    for (int i = 0; i < 5; ++i) {
        piocher();
    }
}

void Joueur::melanger(){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(deck.begin(), deck.end(), gen);
}

void Joueur::passerDefausseADeck(){
    for (auto& carte : defausse) {
        deck.push_back(std::move(carte));
    }

    // Après les déplacements, le vecteur defause contient toujours ses anciens emplacements, 
    // mais leurs unique_ptr sont vides
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

void Joueur::defausserUneCarte(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    defausse.push_back(std::move(main[indice]));
    // supprime l'emplacement sélectionné (vide) et décale les éléments suivants
    main.erase(main.begin() + indice);
}

void Joueur::ecarterCarte(std::size_t indice){
    if (indice >= main.size()) {
        return;
    }

    // supprime l'emplacement sélectionné (la carte) et décale les éléments suivants
    main.erase(main.begin() + indice);
}

void Joueur::ajouterArgent(int montant) {
    if (montant > 0) {
        argent += montant;
        //std::cout<<"ajouter argent"<<std::endl;
    }
}

void Joueur::ajouterPtsVictoire(int points){
    ptsVictoire += points; 
}

bool Joueur::depenserArgent(int montant) {
    if (montant < 0 || argent < montant) {
        return false;
    }

    argent -= montant;
    return true;
}

void Joueur::ajouterActions(int nb) {
    if (nb > 0) {
        action += nb;
    }
}

bool Joueur::depenserAction() {
    if (action <= 0) {
        return false;
    }

    --action;
    return true;
}

void Joueur::ajouterAchats(int nb) {
    if (nb > 0) {
        achat += nb;
    }
}

bool Joueur::depenserAchat() {
    if (achat <= 0) {
        return false;
    }

    --achat;
    return true;
}

void Joueur::reinitialiserRessources() {
    argent = 0;
    action = 1;
    achat = 1;
}

/* 
void Joueur::jouerTresor(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    // indique si c'est bien un tresor 
    Tresor* tresor = dynamic_cast<Tresor*>(main[indice].get());

    if (tresor == nullptr) {
        return;
    }

    int valeur = tresor->getValeurTresor();

    carteJouer.push_back(std::move(main[indice]));
    main.erase(main.begin() + indice);

    argent += valeur;
    }
*/
    /*
    Attention : si tu joues plusieurs cartes de ta main successivement, les indices changent après chaque déplacement. 
    Il faudra donc tenir compte de ce comportement dans l'interface du jeu
    */


void Joueur::jouerTresor(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    Tresor* tresor = dynamic_cast<Tresor*>(main[indice].get());

    if (tresor == nullptr) {
        return;
    }

    // Appliquer l'effet du Trésor
    tresor->jouer(*this);

    // Déplacer la carte vers les cartes jouées
    carteJouer.push_back(std::move(main[indice]));
    main.erase(main.begin() + indice);
}




void Joueur::terminerTour() {
    // Défausser les cartes encore en main.
    for (auto& carte : main) {
        defausse.push_back(std::move(carte));
    }
    main.clear();

    // Défausser les cartes jouées.
    for (auto& carte : carteJouer) {
        defausse.push_back(std::move(carte));
    }
    carteJouer.clear();

    // Préparer le nouveau tour.
    reinitialiserRessources();
    piocherNouvelleMain();
}



void Joueur::jouerAction(std::size_t indice) {
    // Vérifier que l'indice correspond à une carte de la main.
    if (indice >= main.size()) {
        return;
    }

    // Vérifier qu'il s'agit d'une carte Action.
    if (main[indice]->getType() == "Tresor" || main[indice]->getType() == "Victoire") {
        return;
    }

    // Vérifier que le joueur dispose d'une action.
    if (!depenserAction()) {
        return;
    }

    // Conserver un pointeur vers la carte avant de la déplacer.
    Carte* carte = main[indice].get();

    // Déplacer la carte de la main vers les cartes jouées.
    carteJouer.push_back(std::move(main[indice]));
    main.erase(main.begin() + indice);

    // Appliquer les effets de la carte.
    carte->jouer(*this);
}


// permet d'écarter du jeu une carte qui a été jouée et est dans carteJouer
void Joueur::ecarterCarteJouee(const Carte* carte) {
    for (std::size_t i = 0; i < carteJouer.size(); ++i) {
        if (carteJouer[i].get() == carte) {
            carteJouer.erase(carteJouer.begin() + i);
            return;
        }
    }
}