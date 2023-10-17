#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum status {
  HEALTHY,
  SICK,
  INJURED
};

enum position {
  CATCHER,
  HUNTER,
  GOALKEEPER,
  BEATER,
  UNDEFINED
};

enum characteristic_key {
  FAST,
  STRONG,
  ACCURATE,
  NIMBLE,
  STURDY
};

using CharDict = std::map<characteristic_key, int>;

class Player {
 public:
  Player() = default;
  Player(size_t id,
         std::string name,
         std::string last_name,
         CharDict characteristics,
         status status_,
         position position_) : id_(id),
                               name_(std::move(name)),
                               last_name_(std::move(last_name)),
                               characteristics_(std::move(characteristics)),
                               status_(status_),
                               position_(position_) {}
  size_t GetId() const { return this->id_; }
  std::string GetFullName() const { return last_name_ + name_; }
  status GetStatus() const { return status_; }
  position GetPosition() const { return position_; }
  CharDict GetChars() const { return characteristics_; }
 private:
  std::string name_;
  std::string last_name_;
  size_t id_ = 0;
  CharDict characteristics_;
  status status_ = HEALTHY;
  position position_ = UNDEFINED;
};

using Team = std::vector<Player>;

struct date {
  int year_;
  int month_;
  int day_;
};

class Training {
 public:
  Training() = default;
  Training(Team players, date date_) : players_(std::move(players)), date_(date_) {}
  void PrintTraining() const {
    std::cout << "Training date: " << date_.day_ << "." << date_.month_ << "." << date_.year_ << std::endl;
    for (const auto &i : players_) {
      std::cout << i.GetFullName() << std::endl;
    }
  }
 private:
  Team players_;
  date date_ = {0, 0, 0};
};

class Game {
 public:
  Game() = default;
  Game(Team team1, std::string name_of_enemies, date date_, bool have_we_won_)
      : players_(std::move(team1)),
        name_of_enemies(std::move(name_of_enemies)),
        date_(date_),
        have_we_won_(have_we_won_) {}
  void PrintGame() const {
    std::cout << "Game date: " << date_.day_ << "." << date_.month_ << "." << date_.year_ << std::endl;
    for (const auto &i : players_) {
      std::cout << i.GetFullName() << std::endl;
    }
    std::cout << "Enemies: " << name_of_enemies << std::endl;
    if (have_we_won_) {
      std::cout << "We won" << std::endl;
    } else {
      std::cout << "We lost" << std::endl;
    }
  }
 private:
  date date_ = {0, 0, 0};
  Team players_;
  std::string name_of_enemies;
  bool have_we_won_ = false;
};

void PrintMenu() {
  std::vector<std::string> Options =
      {"Choose option:", "1. Add player.", "2. Edit player", "3. Add training.", "4. Add game.", "5. Assemble team.",
       "6. Show training history.", "7. Show game history.", "0. Exit."};
  for (auto &item : Options) {
    std::cout << item << std::endl;
  }
}

void CreatePlayer(Player &player, size_t id) {
  std::string name, lastname;
  int st;
  int pos;
  CharDict chars;
  std::cout << "Write name of player:" << std::endl;
  std::cin >> name;
  std::cout << "Write lastname of player:" << std::endl;
  std::cin >> lastname;
  std::cout << "Choose position:" << std::endl;
  std::cout << "0. CATCHER" << std::endl;
  std::cout << "1. HUNTER" << std::endl;
  std::cout << "2. GOALKEEPER" << std::endl;
  std::cout << "3. BEATER" << std::endl;
  std::cin >> pos;
  std::cout << "Choose status:" << std::endl;
  std::cout << "0. HEALTHY" << std::endl;
  std::cout << "1. SICK" << std::endl;
  std::cout << "2. INJURED" << std::endl;
  std::cin >> st;
  std::vector<std::string> chars_list = {
      "FAST",
      "STRONG",
      "ACCURATE",
      "NIMBLE",
      "STURDY"
  };
  int chars_num;
  for (size_t i = 0; i < chars_list.size(); ++i) {
    std::cout << i << ". " << chars_list[i] << std::endl;
    std::cin >> chars_num;
    chars[static_cast<characteristic_key>(i)] = chars_num;
  }
  player = Player(id, name, lastname, chars, static_cast<status>(st), static_cast<position>(pos));
}

void EditPlayer(Player &player) {
  std::string name, lastname;
  int st;
  int pos;
  CharDict chars;
  std::cout << "Write name of player:" << std::endl;
  std::cin >> name;
  std::cout << "Write lastname of player:" << std::endl;
  std::cin >> lastname;
  std::cout << "Choose position:" << std::endl;
  std::cout << "0. CATCHER" << std::endl;
  std::cout << "1. HUNTER" << std::endl;
  std::cout << "2. GOALKEEPER" << std::endl;
  std::cout << "3. BEATER" << std::endl;
  std::cin >> pos;
  std::cout << "Choose status:" << std::endl;
  std::cout << "0. HEALTHY" << std::endl;
  std::cout << "1. SICK" << std::endl;
  std::cout << "2. INJURED" << std::endl;
  std::cin >> st;
  std::vector<std::string> chars_list = {
      "FAST",
      "STRONG",
      "ACCURATE",
      "NIMBLE",
      "STURDY"
  };
  int chars_num;
  for (size_t i = 0; i < chars_list.size(); ++i) {
    std::cout << i << ". " << chars_list[i] << std::endl;
    std::cin >> chars_num;
    chars[static_cast<characteristic_key>(i)] = chars_num;
  }
  player = Player(player.GetId(), name, lastname, chars, static_cast<status>(st), static_cast<position>(pos));
}

std::vector<Game> GamesHistory;
std::vector<Training> TrainingHistory;

void AddTraining(Training &training, Team &team) {
  std::cout << "Time of training in format dd mm yyyy:" << std::endl;
  date date_of_training{};
  std::cin >> date_of_training.day_ >> date_of_training.month_ >> date_of_training.year_;
  training = Training(team, date_of_training);
}

void AddGames(Game &game, Team &team1) {
  std::string name_of_enemies;
  std::cout << "Name of enemies:" << std::endl;
  std::cin >> name_of_enemies;
  std::cout << "Time of game in format dd mm yyyy:" << std::endl;
  date date_of_training{};
  std::cin >> date_of_training.day_ >> date_of_training.month_ >> date_of_training.year_;
  int winner;
  std::cout << "Who won 1 or 2?" << std::endl;
  std::cin >> winner;
  bool first_won = winner == 1;
  game = Game(team1, name_of_enemies, date_of_training, first_won);
}

void AssembleTeam(Team &players) {
  Team hunters;
  Team goalkeepers;
  Team beaters;
  Team catchers;
  for (auto &i : players) {
    if (i.GetStatus() == HEALTHY) {
      switch (i.GetPosition()) {
        case GOALKEEPER:goalkeepers.emplace_back(i);
          break;
        case HUNTER:hunters.emplace_back(i);
          break;
        case BEATER:beaters.emplace_back(i);
          break;
        case CATCHER:catchers.emplace_back(i);
          break;
        default:break;
      }
    }
  }
  if (goalkeepers.empty() || catchers.empty() || beaters.size() < 2 || hunters.size() < 3) {
    std::cout << "Cannot assemble team" << std::endl;
    return;
  }
  auto goalkeeper = std::max_element(goalkeepers.begin(), goalkeepers.end(),
                                     [](Player &a, Player &b) { return a.GetChars()[STURDY] > b.GetChars()[STURDY]; });
  auto catcher = std::max_element(catchers.begin(), catchers.end(),
                                     [](Player &a, Player &b) { return a.GetChars()[NIMBLE] > b.GetChars()[NIMBLE]; });

  auto beater1 = std::max_element(beaters.begin(), beaters.end(),
                                  [](Player &a, Player &b) { return a.GetChars()[STRONG] > b.GetChars()[STRONG]; });
  beaters.erase(beater1);

  auto beater2 = std::max_element(beaters.begin(), beaters.end(),
                                     [](Player &a, Player &b) { return a.GetChars()[STRONG] > b.GetChars()[NIMBLE]; });
  auto hunter1 = std::max_element(hunters.begin(), hunters.end(),
                                     [](Player &a, Player &b) { return a.GetChars()[ACCURATE] > b.GetChars()[ACCURATE]; });
  hunters.erase(hunter1);
  auto hunter2 = std::max_element(hunters.begin(), hunters.end(),
                                  [](Player &a, Player &b) { return a.GetChars()[ACCURATE] > b.GetChars()[ACCURATE]; });
  hunters.erase(hunter2);
  auto hunter3 = std::max_element(hunters.begin(), hunters.end(),
                                  [](Player &a, Player &b) { return a.GetChars()[ACCURATE] > b.GetChars()[ACCURATE]; });

  std::cout << "Final team: " << std::endl;
  std::cout << "Goalkeper: " << goalkeeper->GetFullName() << std::endl;
  std::cout << "Catcher: " << catcher->GetFullName() << std::endl;
  std::cout << "Beater: " << beater1->GetFullName() << std::endl;
  std::cout << "Beater: " << beater2->GetFullName() << std::endl;
  std::cout << "Hunter: " << hunter1->GetFullName() << std::endl;
  std::cout << "Hunter: " << hunter2->GetFullName() << std::endl;
  std::cout << "Hunter: " << hunter3->GetFullName() << std::endl;
}

int main() {
  int option = 0;
  Team players;
  std::vector<Training> trainings;
  std::vector<Game> games;
  Player player;
  Team players_for_train;
  Game game;
  Team players_for_game;
  Training training;
  int id;
  while (true) {
    PrintMenu();
    std::cin >> option;
    switch (option) {
      case 1:
        CreatePlayer(player, players.size());
        players.push_back(player);
        break;
      case 2:
        if (players.empty()) {
          std::cout << "No players to edit" << std::endl;
          break;
        }
        std::cout << "Which player you want to edit?" << std::endl;
        for (int i = 0; i < players.size(); ++i) {
          std::cout << i << ". " << players[i].GetFullName() << std::endl;
        }
        std::cin >> id;
        EditPlayer(players[id]);
        break;
      case 3:
        if (players.empty()) {
          std::cout << "No players for training" << std::endl;
        } else {
          std::cout << "Choose what players are training?" << std::endl;
          for (int i = 0; i < players.size(); ++i) {
            std::cout << i << ". " << players[i].GetFullName() << std::endl;
            std::cin >> id;
            if (id == 1) {
              players_for_train.push_back(players[i]);
            }
          }
          AddTraining(training, players_for_train);
          TrainingHistory.push_back(training);
        }
        break;
      case 4:
        if (players.empty()) {
          std::cout << "No players for game" << std::endl;
        } else {
          std::cout << "Choose what players are playing?" << std::endl;
          for (int i = 0; i < players.size(); ++i) {
            std::cout << i << ". " << players[i].GetFullName() << std::endl;
            std::cin >> id;
            if (id == 1) {
              players_for_game.push_back(players[i]);
            }
          }
          AddGames(game, players_for_game);
          GamesHistory.push_back(game);
        }
        break;
      case 5:
        AssembleTeam(players);
        break;
      case 6:
        for (auto &i : TrainingHistory) {
          i.PrintTraining();
        }
        break;
      case 7:
        for (auto &i : GamesHistory) {
          i.PrintGame();
        }
        break;
      case 0:exit(0);
      default:std::cout << "Unknown option";
        break;
    }
  }
  return 0;
}