#include "uincampus/statistiques.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {

std::string lire_ligne() {
    std::string ligne{};
    std::getline(std::cin, ligne);
    return ligne;
}

std::string lire_nom_ue() {
    std::string ue{};
    while (ue.empty()) {
        std::cout << "Nom de l'UE : ";
        ue = lire_ligne();
        if (ue.empty()) {
            std::cout << "Le nom ne doit pas être vide.\n";
        }
    }
    return ue;
}

int lire_effectif() {
    while (true) {
        std::cout << "Nombre d'étudiants (1-200) : ";
        const std::string ligne = lire_ligne();
        try {
            std::size_t pos = 0;
            const int valeur = std::stoi(ligne, &pos);
            if (pos != ligne.size()) {
                throw std::invalid_argument("texte en trop");
            }
            if (valeur >= uincampus::kEffectifMin &&
                valeur <= uincampus::kEffectifMax) {
                return valeur;
            }
            std::cout << "Entre 1 et 200 s'il vous plaît.\n";
        } catch (...) {
            std::cout << "Nombre invalide, réessayez.\n";
        }
    }
}

double lire_note(int numero) {
    while (true) {
        std::cout << "Note de l'étudiant " << numero << " (0-20) : ";
        std::string ligne = lire_ligne();
        std::replace(ligne.begin(), ligne.end(), ',', '.');
        try {
            std::size_t pos = 0;
            const double valeur = std::stod(ligne, &pos);
            if (pos != ligne.size()) {
                throw std::invalid_argument("texte en trop");
            }
            if (valeur >= uincampus::kNoteMin &&
                valeur <= uincampus::kNoteMax) {
                return valeur;
            }
            std::cout << "La note doit être entre 0 et 20.\n";
        } catch (...) {
            std::cout << "Note invalide, réessayez (ex : 12,5).\n";
        }
    }
}

} // namespace

int main() {
    const std::string ue = lire_nom_ue();
    const int effectif = lire_effectif();

    std::vector<double> notes{};
    notes.reserve(static_cast<std::size_t>(effectif));
    for (int i = 1; i <= effectif; ++i) {
        notes.push_back(lire_note(i));
    }

    const uincampus::Statistiques stats =
        uincampus::calculer_statistiques(notes);

    std::cout << "\nStatistiques - " << ue << " (" << notes.size()
              << " étudiants)\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Note minimale : " << stats.minimum << "\n";
    std::cout << "Note maximale : " << stats.maximum << "\n";
    std::cout << "Moyenne : " << stats.moyenne << "\n";
    std::cout << "Écart-type : " << stats.ecart_type << "\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Admis : " << stats.nb_admis << " ("
              << stats.pourcentage_admis << " %)\n";

    std::cout << "\nRépartition par mention\n";
    for (std::size_t i = 0; i < uincampus::kNbMentions; ++i) {
        const uincampus::Mention mention =
            static_cast<uincampus::Mention>(i);
        const int count = stats.repartition[i];
        std::cout << uincampus::nom_mention(mention) << " "
                  << std::string(static_cast<std::size_t>(count), '*')
                  << " (" << count << ")\n";
    }
    return 0;
}
