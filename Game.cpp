#include "Game.hpp"
#include <iostream>

Game::Game(std::vector<Player> team1, std::string name_of_enemies, Date date, bool have_we_won)
    : players_(std::move(team1)), name_of_enemies_(std::move(name_of_enemies)), date_(date), have_we_won_(have_we_won) {}

void Game::PrintGame() const {
    std::cout << "Game date: " << date_.day << "." << date_.month << "." << date_.year << std::endl;
    for (const auto& player : players_) {
        std::cout << player.GetFullName() << std::endl;
    }
    std::cout << "Enemies: " << name_of_enemies_ << std::endl;
    std::cout << (have_we_won_ ? "We won" : "We lost") << std::endl;
}
