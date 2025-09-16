#ifndef POST_H
#define POST_H

#include <string>
#include <map>
#include <vector>
#include "user.h" 
#include "reaction.h"

class Post{
private: 
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
    std::vector<Reaction*> reactions_;

public:
    //constructors
    Post();
    Post(int messageId, int ownerId, std::string message, int likes);

    //Pre: no parameters
    //Post: returns the message and how many likes 
    std::string toString();

    //getters
    int getMessageId();
    int getOwnerId();
    std::string getMessage();
    int getLikes();


    //Post: returns an empty string
    virtual std::string getAuthor();

    //returns true, virtual function
    virtual bool getIsPublic();

    void addReaction(User* user, const std::string& type);
    std::map<std::string, std::vector<User*>> getReactionMap() const;
    std::vector<User*> getUsersByReaction(const std::string& type) const;
};


//Incoming class that inherits from Post
class IncomingPost: public Post{
private: 
    std::string author_;
    bool isPublic_;

public: 

    //constructors
    IncomingPost();
    //constructor but also has Post private methods 
    IncomingPost(int messageId, int OwnerId, std::string message, int likes, bool isPublic, std::string author);
    //returns the author and private or public message
    std::string toString();
    std::string getAuthor();
    //whether message is public or not 
    bool getIsPublic();
};

#endif
