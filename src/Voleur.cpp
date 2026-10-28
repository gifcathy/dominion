#include <iostream> 
#include <limits>
#include <utility>
#include "Voleur.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"

// constructeur 
Voleur::Voleur() : ActionPlateau("Voleur", "Action-Attaque", 4){}; 

// destructeur 
Voleur::~Voleur(){}; 

// méthode d'affichage 
void Voleur::afficher() const{
    std::cout << "Voleur - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : Tous vos adversaires dévoilent les deux premières cartes de leur deck. S'ils dévoilent des cartes Trésor, ils en écartent une de votre choix. Parmi ces cartes Trésor écartées, recevez celles de votre choix. Les autres cartes dévoilées sont défaussées." 
              << std::endl;
}

// joueur la carte 
void Voleur::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) {
        int nombreJoueurs = static_cast<int>(listeJoueurs.size()); 
        std::vector<std::unique_ptr<Carte>> cartesEcartees; 
        bool aCarteTresor = false; 
        // on parcourt tous les joueurs adversaires 
        for (int i=0; i<nombreJoueurs; i++){
            if(i != indiceJoueurActuel){
                if(!listeJoueurs[i].possedeDouveEnMain()){
                    std::cout << "le joueur " << i  << "révèle ses cartes" << std::endl; 
                    std::vector<std::unique_ptr<Carte>> cartesDeck; 

                    // on ajoute les deux premières cartes du deck dans un vecteur. 
                    for (int j = 0; j < 2; ++j) {
                        std::unique_ptr<Carte> carte =listeJoueurs[i].prendreCarteDessusDeck();
                        // Eviter de conserver un pointeur nul
                        if (carte != nullptr) {
                            cartesDeck.push_back(std::move(carte));
                        }
                    }
                    
                    // on cherche si il y a des cartes trésor
                    for (const auto& carte : cartesDeck) {
                        if (carte->getType() == "Tresor") {
                            aCarteTresor = true;
                        }
                    }

                    // si il y a une ou plusieurs cartes tresor, on demande laquelle il veut prendre
                    if(aCarteTresor){
                        // affichage des cartes écartées du joueur i 
                        std::cout << "Voici la ou les cartes du joueur " << i << std::endl; 
                        for(std::size_t k=0; k < cartesDeck.size(); k++){
                            std::cout << "[" << k << "]" << cartesDeck[k]->getNom(); 
                        }

                        int numCarteAEcarter; 
                        while(true){
                            std::cout << "Quelle carte voulez-vous écarter ?"; 
                            if (!(std::cin >> numCarteAEcarter)) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                std::cout << "Saisie invalide." << std::endl;
                                continue;
                            }

                            // quand on a choisi une carte tresor on sort de la boucle 
                            if (numCarteAEcarter >= 0 
                                && static_cast<std::size_t>(numCarteAEcarter) < cartesDeck.size()
                                && cartesDeck[numCarteAEcarter]->getType() == "Tresor") {
                                    break;
                            }

                            std::cout << "saisie invalide, veuillez choisir un trésor" << std::endl; 
                        }

                        // on déplace la carte vers les cartes écartées et on la supprime de cartesDeck
                        cartesEcartees.push_back(std::move(cartesDeck[numCarteAEcarter])); 
                        cartesDeck.erase(cartesDeck.begin() + numCarteAEcarter); 
                    }
                    else {
                        std::cout << "Le joueur n'a révélé aucune carte Trésor" << std::endl; 
                    }

                    // déplacer le reste des cartes dans la défausse du joueur concerné 
                    for (auto& carte : cartesDeck) {
                        listeJoueurs[i].ajouterCarte(std::move(carte));
                    }

                    cartesDeck.clear();
                }
                else{
                    std::cout << "Le joueur " << i << " est protégé par une douve"; 
                }
            }
            else{
                continue; 
            }
        }

    
        // quand on a regardé les mains de tout le monde 
        if(cartesEcartees.empty()){
            std::cout << "Aucun trésor n'a été écarté" << std::endl; 
            return; 
        }

        // on affiche les cartes que le joueur a choisi d'écarter 
        std::string reponse; 
        while(!cartesEcartees.empty()){
            std::cout << "Voici toutes les cartes que vous avez écartées :" << std::endl; 
            for(std::size_t i=0; i < cartesEcartees.size(); i++){
                std::cout << "[" << i << "]" << " " << cartesEcartees[i]->getNom() << std::endl; 
            }

            std::cout << "Voulez vous récupérer un trésor ? (oui/non)" << std::endl; 
            if (!(std::cin >> reponse)) {
                return;
            }

            // Verifier la reponse
            while (reponse != "oui" && reponse != "non") {
                std::cout << "Repondez par oui ou non : ";
                if (!(std::cin >> reponse)) {
                    return;
                }
            }

            // si le joueur ne veut plus récupérer de trésor 
            if (reponse == "non") {
                break;
            }

            int indiceCarte; 
            // Demander l'indice du Tresor a recuperer
            while (true) {
                std::cout << "Indice du Tresor a recuperer : ";
                if (!(std::cin >> indiceCarte)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Saisie invalide." << std::endl;
                    continue;
                }

                if (indiceCarte >= 0
                    && static_cast<std::size_t>(indiceCarte) < cartesEcartees.size()) {
                    break;
                }

                std::cout << "Indice invalide." << std::endl;
            }

            // Ajouter le Tresor a la defausse du joueur actif
            listeJoueurs[indiceJoueurActuel].ajouterCarte(std::move(cartesEcartees[indiceCarte]));

            // Retirer le Tresor du vecteur temporaire
            cartesEcartees.erase(cartesEcartees.begin() + indiceCarte);
        }

        // Les Tresors non recuperes sont detruits lorsque le vecteur
        // cartesEcartees est detruit a la fin de la methode.
    }; 





        
/*
        
        do{
            if(reponse != "oui" || reponse != "non"){
                std::cout << "saisie invalide" << std::endl; 
            }
            std::cout << "Voulez vous prendre une ou plusieurs des cartes écartées ? (oui/non)" << std::endl; 
            std::cin >> reponse; 
        }while(reponse != "oui" || reponse != "non"); 

        // tant qu'il veut récupérer des cartes 
        while(reponse == "oui"){
            // on lui demande l'indice de la carte à récupérer 
            int reponseIndiceCarte;
            std::cout << "Quel est l'indice de la carte que vous voulez prendre ?"; 
            std::cin >> reponseIndiceCarte; 
            // on ajoute la carte à sa défausse et on la supprime des cartesEcartees 
            if(reponseIndiceCarte >= 0 && 
                static_cast<std::size_t>(reponseIndiceCarte) < cartesEcartees.size()){
                    listeJoueurs[indiceJoueurActuel].defausserUneCarte(reponseIndiceCarte); 
                    auto it = cartesEcartees.begin() + reponseIndiceCarte;
                    cartesEcartees.erase(it); 
            }
            // on lui montre les cartes ecartées restantes et on lui demande si il veut en récupérer d'autres
            std::cout << "Voici les cartes écartées restantes :" << std::endl; 
            for(int i=0; i < cartesEcartees.size(); i++){
                std::cout << "[" << i << "]" << " " << cartesEcartees[i]->getNom() << std::endl; 
            }
            std::cout << "Voulez vous prendre une autre des cartes écartées ? (oui/non)" << std::endl; 
            std::cin >> reponse; 
            while(reponse != "oui" || reponse != "non"){
                std::cout << "saisie invalide" << std::endl;
                std::cout << "Voulez vous prendre une ou plusieurs des cartes écartées ? (oui/non)" << std::endl; 
                std::cin >> reponse; 
            }
        }

        // si il ne veut pas ou plus en récupérer on supprime les cartes restantes 
        if(reponse == "non"){
            for(int j=0; j < cartesEcartees.size(); j++){
                cartesEcartees.erase(cartesEcartees.begin() + j); 
            }
        }

    };

*/