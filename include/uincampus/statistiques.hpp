#pragma once

#include <array>
#include <string>
#include <vector>

namespace uincampus {

inline constexpr double kNoteMin = 0.0;
inline constexpr double kNoteMax = 20.0;
inline constexpr int kEffectifMin = 1;
inline constexpr int kEffectifMax = 200;
inline constexpr double kSeuilAdmis = 10.0;
inline constexpr double kSeuilPassable = 12.0;
inline constexpr double kSeuilAssezBien = 14.0;
inline constexpr double kSeuilBien = 16.0;
inline constexpr std::size_t kNbMentions = 5;

enum class Mention {
    Ajourne = 0,
    Passable = 1,
    AssezBien = 2,
    Bien = 3,
    TresBien = 4
};

struct Statistiques {
    double minimum = 0.0;
    double maximum = 0.0;
    double moyenne = 0.0;
    double ecart_type = 0.0;
    int nb_admis = 0;
    double pourcentage_admis = 0.0;
    std::array<int, kNbMentions> repartition{};
};

Mention mention_de(double note);
Statistiques calculer_statistiques(const std::vector<double>& notes);
std::string nom_mention(Mention mention);

} // namespace uincampus
