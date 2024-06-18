#include "Training.hpp"
#include <iostream>

Training::Training(std::vector<Player> players, Date date)
    : players_(std::move(players)), date_(date) {}

void Training::PrintTraining() const {
    std::cout << "Training date: " << date_.day << "." << date_.month << "." << date_.year << std::endl;
    for (const auto& player : players_) {
        std::cout << player.GetFullName() << std::endl;
    }
}
