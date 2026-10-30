#include "InitialisationCartes.hpp"

#include <memory>
#include <utility>

void initialiserCatalogue(CatalogueCartes& catalogue) {
    catalogue.enregistrer("Argent", [] {
        //return std::make_unique<Cuivre>();
        return std::unique_ptr<Carte>(new Argent());
    });

    catalogue.enregistrer("Atelier", [] {
        //return std::make_unique<Atelier>();
        return std::unique_ptr<Carte>(new Atelier());
    });

    catalogue.enregistrer("Aventurier", []{
        return std::unique_ptr<Carte>(new Aventurier()); 
    }); 

    catalogue.enregistrer("Baron", []{
        return std::unique_ptr<Carte>(new Baron()); 
    }); 

    catalogue.enregistrer("Bibliotheque", []{
        return std::unique_ptr<Carte>(new Bibliotheque()); 
    }); 

    catalogue.enregistrer("Bucheron", [] {
        return std::unique_ptr<Carte>(new Bucheron());
    });

    catalogue.enregistrer("Bureaucrate", [] {
        return std::unique_ptr<Carte>(new Bureaucrate());
    });

    catalogue.enregistrer("Cave", [] {
        return std::unique_ptr<Carte>(new Cave());
    });

    catalogue.enregistrer("ChambreDuConseil", [] {
        return std::unique_ptr<Carte>(new ChambreDuConseil());
    });

    catalogue.enregistrer("Chancelier", [] {
        return std::unique_ptr<Carte>(new Chancelier());
    });

    catalogue.enregistrer("Chapelle", [] {
        return std::unique_ptr<Carte>(new Chapelle());
    });

    catalogue.enregistrer("Comptoir", []{
        return std::unique_ptr<Carte>(new Comptoir()); 
    }); 

    catalogue.enregistrer("Cour", []{
        return std::unique_ptr<Carte>(new Comptoir()); 
    }); 

    catalogue.enregistrer("Cuivre", [] {
        return std::unique_ptr<Carte>(new Cuivre());
    });

    catalogue.enregistrer("Domaine", [] {
        return std::unique_ptr<Carte>(new Domaine());
    });

    catalogue.enregistrer("Douves", [] {
        return std::unique_ptr<Carte>(new Douves());
    });
    
    catalogue.enregistrer("Duc", []{
        return std::unique_ptr<Carte>(new Duc()); 
    }); 

    catalogue.enregistrer("Duche", [] {
        return std::unique_ptr<Carte>(new Duche());
    });

    catalogue.enregistrer("Espion", [] {
        return std::unique_ptr<Carte>(new Espion());
    });

    catalogue.enregistrer("Festin", [] {
        return std::unique_ptr<Carte>(new Festin());
    });

    catalogue.enregistrer("Festival", [] {
        return std::unique_ptr<Carte>(new Festival());
    });

    catalogue.enregistrer("Fonderie", []{
        return std::unique_ptr<Carte>(new Fonderie()); 
    }); 

    catalogue.enregistrer("Forgeron", [] {
        return std::unique_ptr<Carte>(new Forgeron());
    });

    catalogue.enregistrer("Intendant", [] {
        return std::unique_ptr<Carte>(new Intendant()); 
    });

    catalogue.enregistrer("Jardin", [] {
        return std::unique_ptr<Carte>(new Jardin());
    });

    catalogue.enregistrer("Laboratoire", [] {
        return std::unique_ptr<Carte>(new Laboratoire());
    });

    catalogue.enregistrer("Larbin", [] {
        return std::unique_ptr<Carte>(new Larbin());
    });

    catalogue.enregistrer("Malediction", [] {
        return std::unique_ptr<Carte>(new Malediction());
    });

    catalogue.enregistrer("Marche", [] {
        return std::unique_ptr<Carte>(new Marche());
    });

    catalogue.enregistrer("Milice", []{
        return std::unique_ptr<Carte>(new Milice()); 
    }); 

    catalogue.enregistrer("Mine", [] {
        return std::unique_ptr<Carte>(new Mine());
    });

    catalogue.enregistrer("MiseANiveau", []{
        return std::unique_ptr<Carte>(new MiseANiveau()); 
    }); 

    catalogue.enregistrer("Or", [] {
        return std::unique_ptr<Carte>(new Or());
    });

    catalogue.enregistrer("Pion", []{
        return std::unique_ptr<Carte>(new Pion()); 
    }); 

    catalogue.enregistrer("PreteurSurGages", [] {
        return std::unique_ptr<Carte>(new PreteurSurGages());
    });

    catalogue.enregistrer("Province", [] {
        return std::unique_ptr<Carte>(new Province());
    });

    catalogue.enregistrer("PuitsAuxSouhaits", []{
        return std::unique_ptr<Carte>(new PuitsAuxSouhaits()); 
    }); 

    catalogue.enregistrer("Renovation", [] {
        return std::unique_ptr<Carte>(new Renovation());
    });

    catalogue.enregistrer("SalleDuTrone", [] {
        return std::unique_ptr<Carte>(new SalleDuTrone());
    });

    catalogue.enregistrer("Sorciere", [] {
        return std::unique_ptr<Carte>(new Sorciere());
    });

    catalogue.enregistrer("Village", [] {
        return std::unique_ptr<Carte>(new Village());
    });

    catalogue.enregistrer("VillageMinier", []{
        return std::unique_ptr<Carte>(new VillageMinier()); 
    }); 

    catalogue.enregistrer("Voleur", [] {
        return std::unique_ptr<Carte>(new Voleur());
    });

}