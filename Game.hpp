#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Date.hpp"
#include <vector>
#include <string>

class Game {
 public:
    Game() = default;
    Game(std::vector<Player> team1, std::string name_of_enemies, Date date, bool have_we_won);

    void PrintGame() const;

 private:
    std::vector<Player> players_;
    Date date_;
    std::string name_of_enemies_;
    bool have_we_won_ = false;
};

#endif // GAME_HPP
