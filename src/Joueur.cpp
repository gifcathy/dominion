#include "Joueur.hpp"
#include "Carte.hpp"
#include "Tresor.hpp"
#include "Jardin.hpp"
#include "Victoire.hpp"
#include "Duc.hpp"

#include <utility>
#include <algorithm> //contient std::shuffle
#include <random>
#include <vector>
#include <memory>

Joueur::Joueur(std::vector<std::unique_ptr<Carte>> deckInitial) : deck(std::move(deckInitial)), argent(0), action(1), achat(1), ptsVictoire(0){
    
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

// Accéder à la main pour la modifier.
std::vector<std::unique_ptr<Carte>>& Joueur::getMain() {
    return main;
}

const std::unique_ptr<Carte>& Joueur::getCarte(std::size_t indice) const{
    return main.at(indice);  //main[indice]; avec at on a des execption qui sont lever si probleme dans indice
}

const std::vector<std::unique_ptr<Carte>>& Joueur::getCartesJouees() const{
    return carteJouer; 
}

// Retourne le nombre de cartes dans le deck
std::size_t Joueur::getNbrCarteDeck() const {
    return deck.size();
}

// Retourne le nombre de cartes dans la defausse
std::size_t Joueur::getNbrCarteDefausse() const {
    return defausse.size();
}

// Donne le nombre de cartes d'une certaine carte passée en paramètre
int Joueur::getNombreCarte(const std::string& nom) const {
    int nombre = 0;

    auto compter = [&](const std::vector<std::unique_ptr<Carte>>& cartes) {
        for (const auto& carte : cartes) {
            if (carte->getNom() == nom) {
                nombre++;
            }
        }
    };

    compter(deck);
    compter(main);
    compter(defausse);
    compter(carteJouer);

    return nombre;
}

const Carte* Joueur::getCarteDessusDeck() const {
    if (deck.empty()) {
        return nullptr;
    }

    return deck.back().get();
}

void Joueur::defausserCarteDessusDeck() {
    if (deck.empty()) {
        return;
    }

    defausse.push_back(std::move(deck.back()));
    deck.pop_back();
}

void Joueur::ajouterCarteDessusDeck(std::unique_ptr<Carte> carte) {
    if (carte != nullptr) {
        deck.push_back(std::move(carte));
    }
}

void Joueur::mettreCarteMainDessusDeck(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    deck.push_back(std::move(main[indice]));
    main.erase(main.begin() + indice);
}


void Joueur::afficherMain() {
    std::cout << "Votre main :" << std::endl;

    for (std::size_t j = 0; j < main.size(); j++) {
        std::cout << "[" << j << "] "
                  << main[j]->getNom() << std::endl;
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

std::vector<std::string> Joueur::piocherDesCartes(int nb) {
    std::vector<std::string> cartesPiochees;

    for (int i = 0; i < nb; ++i) {
        // Piocher une carte
        piocher();

        // Récupérer le nom de la carte qui vient d'être piochée
        if (!main.empty()) {
            cartesPiochees.push_back(main.back()->getNom());
        }
    }

    return cartesPiochees;
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
    std::cout << "carte ajoutée à la defausse" << std::endl;

    //Pour utiliser cette fonction, tu ferais par exemple :
    //joueur.ajouterCarte(std::make_unique<Cuivre>());
    //Cela crée un Cuivre et transfère directement sa propriété au joueur.
}

void Joueur::ajouterCarteMain(std::unique_ptr<Carte> carte){
    std::string nomCarte = carte->getNom(); 
    main.push_back(std::move(carte));
    std::cout << nomCarte << " a été ajouté à votre main" << std::endl;
}

void Joueur::defausserUneCarte(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    defausse.push_back(std::move(main[indice]));
    // supprime l'emplacement sélectionné (vide) et décale les éléments suivants
    main.erase(main.begin() + indice);
}

void Joueur::defausseDeck() {
    for (std::size_t i = 0; i < deck.size(); i++) {
        defausse.push_back(std::move(deck[i]));
    }
    deck.clear();
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

void Joueur::jouerActionDeuxFois(std::size_t indice) {
    if (indice >= main.size()) {
        return;
    }

    // Vérifier que la carte est une carte Action
    if (main[indice]->getType() == "Tresor" ||
        main[indice]->getType() == "Victoire") {
        return;
    }

    // Garder un pointeur vers la carte choisie
    Carte* carte = main[indice].get();

    // Déplacer la carte dans les cartes jouées
    carteJouer.push_back(std::move(main[indice]));
    main.erase(main.begin() + indice);

    // Jouer la carte deux fois
    carte->jouer(*this);
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


bool Joueur::possedeDouveEnMain() const {
    for (std::size_t i = 0; i < main.size(); i++) {
        if (main[i]->getNom() == "Douves") {
            return true;
        }
    }
    return false;
}


int Joueur::getNombreTotalCartes() const {
    return static_cast<int>(deck.size() + main.size() + defausse.size() + carteJouer.size());
}


// calculer le nombre total de point à la fin de la partie 
int Joueur::calculerPointsVictoire() const {
    int points = 0;
    // Nombre total de cartes possédées par le joueur
    int tailleDeck = getNombreTotalCartes();

    // Fonction qui calcule les points d'une carte
    // la fonction locale peut utiliser des les variables de la méthode extérieure par référence
    auto compterCarte = [&](const std::unique_ptr<Carte>& carte) {
        // Vérifier si la carte est un Jardin
        const Jardin* jardin = dynamic_cast<const Jardin*>(carte.get());
        // carte.get() permet d'obtenir le pointeur brut vers l'objet sans transferer sa propriété
        // convertit le pointeur de Carte vers un Jardin si ça en est un 

        // si la carte est bien un jardin 
        if (jardin != nullptr) {
            points += jardin->getNbPointVictoireJardin(tailleDeck);
        }
        else {
            // Sinon, vérifier si c'est une autre carte Victoire
            const Victoire* victoire = dynamic_cast<const Victoire*>(carte.get());
            // si c'est bien une victoire on ajoute les points 
            if (victoire != nullptr) {
                // on vérifie si c'est un duc 
                const Duc* duc = dynamic_cast<const Duc*>(carte.get());
                if(duc != nullptr){
                    points += duc->getNbPointVictoireDuc(*this); 
                }
                else{
                    // pour les autres cartes victoire
                    points += victoire->getValeurVictoire();
                }
            }
        }
    };

    // Compter les points des cartes dans chaque emplacement
    for (const auto& carte : deck) {
        compterCarte(carte);
    }

    for (const auto& carte : main) {
        compterCarte(carte);
    }

    for (const auto& carte : defausse) {
        compterCarte(carte);
    }

    for (const auto& carte : carteJouer) {
        compterCarte(carte);
    }

    return points;
}


std::unique_ptr<Carte> Joueur::prendreCarteDessusDeck(){
    if(deck.empty()){
        passerDefausseADeck(); 
    }
    // cas où le joueur n'aurait pas assez de cartes. 
    if(deck.empty()){
        return nullptr; 
    }
    std::unique_ptr<Carte> carte = std::move(deck.back()); 
    deck.pop_back(); 
    return carte; 
}