// Reaction.cpp
#include "reaction.h"

Reaction::Reaction(User* user, const std::string& type)
    : user_(user), type_(type) {}

User* Reaction::getUser() const {
    return user_;
}

std::string Reaction::getType() const {
    return type_;
}