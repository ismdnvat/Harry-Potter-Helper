#include "Player.hpp"

Player::Player(size_t id, std::string name, std::string last_name, CharDict characteristics, Status status, Position position)
    : id_(id), name_(std::move(name)), last_name_(std::move(last_name)), characteristics_(std::move(characteristics)),
      status_(status), position_(position) {}

size_t Player::GetId() const { return id_; }
std::string Player::GetFullName() const { return last_name_ + " " + name_; }
Status Player::GetStatus() const { return status_; }
Position Player::GetPosition() const { return position_; }
CharDict Player::GetChars() const { return characteristics_; }
