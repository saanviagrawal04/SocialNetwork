#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>

class Post;

class User {
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_;

public:
    User();
    User(int id, std::string name, int year, int zip, std::set<int>f);

    //pre: user is an object with a friends_ set (no duplicates will be added)
    //post: user's set of friends has a new friend's id added in the correct place in order
    void addFriend(int id);

    //pre: user is an object with a friends_ vector with atleast one friend 
    //post: friend is deleted so the set has one less value 
    void deleteFriend(int id);

    //accessors 

    //pre: user exists and has an ID
    //post: returns an int id of user
    int getId() const;

    //pre: user has a year
    //post: a year int is returned
    int getYear() const;

    //pre: user has a zip code
    //post: returns users zip code
    int getZip() const;

    //pre: user has a name
    //post: returns the users name in string format
    std::string getName() const;

    //pre: 
    //post: returns the users friends which are stored in a set 
    std::set<int> & getFriends();

//HW3 new additions//

    //Pre: given a pointer to a post object
    //Post: the post object is now added to the messages vector of posts.
    void addPost(Post*);

    //Pre: there is a messages vector
    //Post: returns the messages vector of pointers to post objects
    std::vector<Post*> getPosts();

    //Pre: howMany is the number of posts user wants to return and is greater than or equal to 0. If it is greater than number of posts, return all
            //showOnlyPublic is a boolean specifying whether to show the publuc only posts or all
    //Post: returns a string with 'howMany' recent posts from messages vector, nicely formatted based on the showOnlyPublic boolean.
    std::string getPostsString(int howMany, bool showOnlyPublic);

};

#endif
