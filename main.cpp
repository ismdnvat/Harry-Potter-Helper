#include "Player.hpp"
#include "Training.hpp"
#include "Game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using Team = std::vector<Player>;

void PrintMenu() {
    const std::vector<std::string> options = {
        "Choose option:",
        "1. Add player.",
        "2. Edit player",
        "3. Add training.",
        "4. Add game.",
        "5. Assemble team.",
        "6. Show training history.",
        "7. Show game history.",
        "0. Exit."
    };
    for (const auto& option : options) {
        std::cout << option << std::endl;
    }
}

void CreateOrEditPlayer(Player& player, size_t id = 0) {
    std::string name, last_name;
    int status, position;
    CharDict characteristics;

    std::cout << "Enter player's first name: ";
    std::cin >> name;
    std::cout << "Enter player's last name: ";
    std::cin >> last_name;

    std::cout << "Choose position:\n0. CATCHER\n1. HUNTER\n2. GOALKEEPER\n3. BEATER\n";
    std::cin >> position;

    std::cout << "Choose status:\n0. HEALTHY\n1. SICK\n2. INJURED\n";
    std::cin >> status;

    const std::vector<std::string> chars_list = {
        "FAST", "STRONG", "ACCURATE", "NIMBLE", "STURDY"
    };
    for (size_t i = 0; i < chars_list.size(); ++i) {
        int value;
        std::cout << "Rate " << chars_list[i] << " (0-100): ";
        std::cin >> value;
        characteristics[static_cast<CharacteristicKey>(i)] = value;
    }

    player = Player(id, name, last_name, characteristics, static_cast<Status>(status), static_cast<Position>(position));
}

void AddTraining(Training& training, const Team& team) {
    Date date;
    std::cout << "Enter training date (dd mm yyyy): ";
    std::cin >> date.day >> date.month >> date.year;
    training = Training(team, date);
}

void AddGame(Game& game, const Team& team) {
    std::string enemies_name;
    Date date;
    int winner;

    std::cout << "Enter enemies' name: ";
    std::cin >> enemies_name;

    std::cout << "Enter game date (dd mm yyyy): ";
    std::cin >> date.day >> date.month >> date.year;

    std::cout << "Who won? (1 for us, 2 for them): ";
    std::cin >> winner;

    game = Game(team, enemies_name, date, winner == 1);
}

bool compare_strong(const Player& p1, const Player& p2) {
    return p1.GetChars().at(CharacteristicKey::STRONG) < p2.GetChars().at(CharacteristicKey::STRONG);
}

bool compare_nimble(const Player& p1, const Player& p2) {
    return p1.GetChars().at(CharacteristicKey::NIMBLE) < p2.GetChars().at(CharacteristicKey::NIMBLE);
}

bool compare_sturdy(const Player& p1, const Player& p2) {
    return p1.GetChars().at(CharacteristicKey::STURDY) < p2.GetChars().at(CharacteristicKey::STURDY);
}

void AssembleTeam(Team& players) {
    Team goalkeepers, catchers, beaters, hunters;
    for (const auto& player : players) {
        switch (player.GetPosition()) {
            case Position::GOALKEEPER:
                goalkeepers.push_back(player);
                break;
            case Position::CATCHER:
                catchers.push_back(player);
                break;
            case Position::BEATER:
                beaters.push_back(player);
                break;
            case Position::HUNTER:
                hunters.push_back(player);
                break;
            default:
                break;
        }
    }

    if (goalkeepers.size() < 1) {
        std::cout << "Not enough players for the goalkeeper position.\n";
        return;
    }
    if (catchers.size() < 1) {
        std::cout << "Not enough players for the catcher position.\n" ;
        return;
    }
    if (beaters.size() < 2) {
        std::cout << "Not enough players for the beater position.\n";
        return;
    }
    if (hunters.size() < 3) {
        std::cout << "Not enough players for the hunter position.\n";
        return;
    }


    std::sort(goalkeepers.begin(), goalkeepers.end(), compare_sturdy);
    std::sort(catchers.begin(), catchers.end(), compare_nimble);
    std::sort(beaters.begin(), beaters.end(), compare_strong);
    std::sort(hunters.begin(), hunters.end(), compare_strong);

    const Player* goalkeeper = &goalkeepers.back();
    const Player* catcher = &catchers.back();
    const Player* beater1 = &beaters.back();
    const Player* beater2 = &beaters[beaters.size() - 2];
    const Player* hunter1 = &hunters.back();
    const Player* hunter2 = &hunters[hunters.size() - 2];
    const Player* hunter3 = &hunters[hunters.size() - 3];

    std::cout << "Goalkeeper: " << goalkeeper->GetFullName() << "\n";
    std::cout << "Catcher: " << catcher->GetFullName() << "\n";
    std::cout << "Beaters: " << beater1->GetFullName() << ", " << beater2->GetFullName() << "\n";
    std::cout << "Hunters: " << hunter1->GetFullName() << ", " << hunter2->GetFullName() << ", " << hunter3->GetFullName() << "\n";
}

int main() {
    Team players;
    std::vector<Training> training_history;
    std::vector<Game> games_history;
    int option;

    while (true) {
        PrintMenu();
        std::cin >> option;

        switch (option) {
            case 1: {
                Player player;
                CreateOrEditPlayer(player, players.size());
                players.push_back(player);
                break;
            }
            case 2: {
                if (players.empty()) {
                    std::cout << "No players to edit.\n";
                    break;
                }
                std::cout << "Select a player to edit:\n";
                for (size_t i = 0; i < players.size(); ++i) {
                    std::cout << i << ". " << players[i].GetFullName() << "\n";
                }
                size_t id;
                std::cin >> id;
                CreateOrEditPlayer(players[id], players[id].GetId());
                break;
            }
            case 3: {
                if (players.empty()) {
                    std::cout << "No players for training.\n";
                    break;
                }
                Team players_for_training;
                std::cout << "Select players for training (enter -1 to stop):\n";
                for (size_t i = 0; i < players.size(); ++i) {
                    std::cout << i << ". " << players[i].GetFullName() << "\n";
                }
                int id;
                while (std::cin >> id && id != -1) {
                    if (id >= 0 && id < players.size()) {
                        players_for_training.push_back(players[id]);
                    }
                }
                Training training;
                AddTraining(training, players_for_training);
                training_history.push_back(training);
                break;
            }
            case 4: {
                if (players.empty()) {
                    std::cout << "No players for game.\n";
                    break;
                }
                Team players_for_game;
                std::cout << "Select players for game (enter -1 to stop):\n";
                for (size_t i = 0; i < players.size(); ++i) {
                    std::cout << i << ". " << players[i].GetFullName() << "\n";
                }
                int id;
                while (std::cin >> id && id != -1) {
                    if (id >= 0 && id < players.size()) {
                        players_for_game.push_back(players[id]);
                    }
                }
                Game game;
                AddGame(game, players_for_game);
                games_history.push_back(game);
                break;
            }
            case 5: {
                AssembleTeam(players);
                break;
            }
            case 6: {
                for (const auto& training : training_history) {
                    training.PrintTraining();
                }
                break;
            }
            case 7: {
                for (const auto& game : games_history) {
                    game.PrintGame();
                }
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                std::cout << "Unknown option.\n";
                break;
            }
        }
    }
}
