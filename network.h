#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "user.h"

class Network{
private:
    std::vector<User*> users_;
public:
    Network();
    ~Network(); // destructor
    //Pre: user is a pointer to a valid User object
    // Post: Adds the user to the network
    void addUser(User* user);

    //Pre: 's1' and 's2' are full names (first + last) of existing users in the network
    // Post: Adds each user to the other’s friend list, returns 0 on success, -1 on error 
    int addConnection(std::string s1, std::string s2);

    //Pre: 's1' and 's2' are full names of existing users
    // Post: Removes each user from the other’s friend list Returns 0 on success, -1 on error 
    int deleteConnection(std::string s1, std::string s2);

    //Pre: name is the full name of a user (first + last)
    // Post: Returns the index or id of the user in users_, or -1 if not found
    int getId(std::string name);

    //Pre: fname is a valid path to a file formatted with user and connection data
    //Post: loads users and their connections into the network. Returns 0 on success, -1 on error
    int readUsers(const char* fname);

    //Pre: fname is a valid file path to write to
    // Post: writes all users and their connections to the file. Returns 0 on success, -1 on error
    int writeUsers(char *fname);

    // Post: Returns the number of users currently in the network.
    int numUsers();

    //Pre: id is a valid index between 0 and size 
    //Post: returns a pointer to the user with that ID, or nullptr if invalid
    User* getUser(int id);

    //Pre: from and to are valid user ids 
    //Post: provides the shortest path from to the to parameter in order 
    std::vector<int> shortestPath(int from, int to);

    //Pre: from is a valid user ids and distance is a valid path from a from user to a to user
    //Post: returns vector of the IDs of the users on the path from the "from" user to a to user that matches the distance parameter. If none found, to ID is -1 and empty vector returned
    std::vector<int> distanceUser(int from, int& to, int distance);

    //Pre: score will be a call by ref which will hold the highest score, score of a new friends is common friends they would share with the specified user.
        //who is a valid user
    //Post: return a vector of suggestions of friends who are not current friends with a relational distance of 2 or less
    std::vector<int> suggestFriends(int who, int& score);

   // Pre: start is a valid user ID in the range [0, users_.size()), 
        //visited is a boolean vector of size users_.size(), where each element indicates whether a user has already been visited.
        // group is an empty vector that will be populated during this call thats why it is call by ref
   // Post: All users connected to start have been visited
        // Their IDs have been added to group
        // The visited vector has been updated to reflect the users visited during the traversal
    void dfs(int start, std::vector<bool>& visited, std::vector<int>& group);

    // Pre: Network has been initialized and may contain zero or more users. Each user may or may not have friend connections.
    // Post: Returns a vector of groups, where each group is a vector of user IDs that are all part of the same connected component 
        //Every user in the network appears in exactly one group
        //Users with no friends are returned as singleton groups
    std::vector<std::vector<int> > groups();

    //Pre: ownerId exists in network, message is a non-empty string and likes is greater than or eq. to 0 and is isIncoming is true, author name also has value
    //Post:post or incoming post is created and added to messages vector under ownerId
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);
    
    //Pre:ownerId exists in network, howMany is is greater than or eq. to 0 and showOnlyPublic tells if private ones r shown or not
    //Post:string with most recent 'howMany' posts from user and newest to oldest
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    //Pre: fname is representing a path to a valid posts file
    //Post: Parses the file and populates the appropriate users’ message vectors, returns -1 if cannot open, if everything works, returns 0
    int readPosts(char* fname);
    
    //Pre:fname is representing a path to a valid posts file
    //Post:All posts from all users are collected, sorted by messageId, and written to the file returns -1 if cannot open, if everything works, returns 0
    int writePosts(char* fname);
};

#endif