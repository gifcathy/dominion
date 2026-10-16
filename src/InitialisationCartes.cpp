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

    catalogue.enregistrer("Bucheron", [] {
        //return std::make_unique<Bucheron>();
        return std::unique_ptr<Carte>(new Bucheron());
    });

    catalogue.enregistrer("Chapelle", [] {
        return std::unique_ptr<Carte>(new Chapelle());
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

    catalogue.enregistrer("Festin", [] {
        return std::unique_ptr<Carte>(new Festin());
    });

    catalogue.enregistrer("Jardin", [] {
        return std::unique_ptr<Carte>(new Jardin());
    });

    catalogue.enregistrer("Laboratoire", [] {
        return std::unique_ptr<Carte>(new Laboratoire());
    });

    catalogue.enregistrer("Malediction", [] {
        return std::unique_ptr<Carte>(new Malediction());
    });

    catalogue.enregistrer("Or", [] {
        return std::unique_ptr<Carte>(new Or());
    });

    catalogue.enregistrer("Province", [] {
        return std::unique_ptr<Carte>(new Province());
    });

    catalogue.enregistrer("Sorciere", [] {
        return std::unique_ptr<Carte>(new Sorciere());
    });

    catalogue.enregistrer("Village", [] {
        return std::unique_ptr<Carte>(new Village());
    });

    catalogue.enregistrer("Voleur", [] {
        return std::unique_ptr<Carte>(new Voleur());
    });

}