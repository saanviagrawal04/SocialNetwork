#include "user.h"
#include "post.h"

//constructors 
User::User(): id_(0), name_(""), year_(0), zip_(0), friends_() {}
User::User(int id, std::string name, int year, int zip, std::set<int>f): id_(id), name_(name), year_(year), zip_(zip), friends_(f) {}

void User::addFriend(int id){
    friends_.insert(id);
}
void User::deleteFriend(int id){
    friends_.erase(id);
} 
//accessors 
int User::getId() const{ return id_;}
int User::getYear() const{ return year_;}
int User::getZip() const{return zip_;}
std::string User::getName() const {return name_;}
std::set<int> & User::getFriends(){return friends_;}

//HW3///************* 
void User::addPost(Post* post){
    messages_.push_back(post);
}

std::vector<Post*> User::getPosts(){
    return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic) {
    std::string ret;
    int count = 0;

    for (int i = messages_.size() - 1; i >= 0 && count < howMany; --i) { // include i == 0
        Post* curr = messages_[i];

        // Skip if it's an IncomingPost and not public
        if (showOnlyPublic && !curr->getIsPublic()) {
            continue;
        }

        ret += curr->toString();
        ret += "\n\n";
        count++;
    }

    return ret;
}
