#ifndef TRAINING_HPP
#define TRAINING_HPP

#include "Player.hpp"
#include "Date.hpp"
#include <vector>

class Training {
 public:
    Training() = default;
    Training(std::vector<Player> players, Date date);

    void PrintTraining() const;

 private:
    std::vector<Player> players_;
    Date date_;
};

#endif // TRAINING_HPP
