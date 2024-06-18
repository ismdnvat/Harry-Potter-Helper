#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Enums.hpp"
#include <map>
#include <string>

using CharDict = std::map<CharacteristicKey, int>;

class Player {
 public:
    Player() = default;
    Player(size_t id, std::string name, std::string last_name, CharDict characteristics, Status status, Position position);

    size_t GetId() const;
    std::string GetFullName() const;
    Status GetStatus() const;
    Position GetPosition() const;
    CharDict GetChars() const;

 private:
    size_t id_ = 0;
    std::string name_;
    std::string last_name_;
    CharDict characteristics_;
    Status status_ = Status::HEALTHY;
    Position position_ = Position::UNDEFINED;
};

#endif // PLAYER_HPP
