#include "post.h"

Post::Post(): messageId_(0), ownerId_(0), message_(""), likes_(0){}
Post::Post(int messageId, int ownerId, std::string message, int likes): messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes){}
std::string Post::toString() {
    return message_ + " Liked by " + std::to_string(likes_) + " people.";
}
int Post::getMessageId(){
    return messageId_;
}
int Post::getOwnerId(){ return ownerId_;}
std::string Post::getMessage(){ return message_;}
int Post::getLikes(){ return likes_;}
std::string Post::getAuthor(){ return "";}
bool Post::getIsPublic(){ return true;}

void Post::addReaction(User* user, const std::string& type) {
    reactions_.push_back(new Reaction(user, type));
}
std::map<std::string, std::vector<User*>> Post::getReactionMap() const {
    std::map<std::string, std::vector<User*>> result;
    for (const auto& reaction : reactions_) {
        result[reaction->getType()].push_back(reaction->getUser());
    }
    return result;
}

std::vector<User*> Post::getUsersByReaction(const std::string& type) const {
    std::vector<User*> result;
    for (const auto& reaction : reactions_) {
        if (reaction->getType() == type) {
            result.push_back(reaction->getUser());
        }
    }
    return result;
}



//Incoming class method implementations
IncomingPost::IncomingPost(): Post(), author_(""), isPublic_(true){}
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic) {}
std::string IncomingPost::toString() {
    std::string prefix = author_ + " wrote";
    if (!isPublic_) {
        prefix += " (private)";
    }
    prefix += ": ";
    return prefix + Post::toString();
}
std::string IncomingPost::getAuthor(){ return author_;}
bool IncomingPost::getIsPublic(){ return isPublic_;}
