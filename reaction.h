#ifndef REACTION_H
#define REACTION_H

#include <string>


class User;
class Reaction {
private:
    User* user_;
    std::string type_;  // e.g., "like", "dislike", "laugh"

public:
    Reaction(User* user, const std::string& type);
    User* getUser() const;
    std::string getType() const;
};

#endif
