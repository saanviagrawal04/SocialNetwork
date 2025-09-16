#include "network.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "post.h"

std::string trim(const std::string& str) {
    auto front = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto back = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    if (front >= back) return "";
    return std::string(front, back);
}

Network::Network() : users_() {}
Network::~Network() {
    for (User* user : users_) {
        delete user;
    }
    users_.clear();
}
void Network::addUser(User* user) {
    users_.push_back(user);
}

int Network::addConnection(std::string s1, std::string s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);
    if (id1 == -1 || id2 == -1 || id1 == id2) {  //check validity and not same person
        return -1;
    } //adds connection for both ends
    users_[id1]->addFriend(id2);
    users_[id2]->addFriend(id1);
    return 0;
}
int Network::deleteConnection(std::string s1, std::string s2) {
    int id1 = getId(s1); 
    int id2 = getId(s2);
    if (id1 == -1 || id2 == -1 || id1 == id2) { //check validity and not same person
        return -1;
    } //deletes on both ends
    users_[id1]->deleteFriend(id2);
    users_[id2]->deleteFriend(id1);
    return 0;
}

int Network::getId(std::string name) {
    std::cout<<name<<std::endl;
    std::cout<<users_.size();
    for (size_t i = 0; i < users_.size(); ++i) {
        std::cout<<users_[i]->getName()<<std::endl;
        if (users_[i]->getName() == name) {
            return i; 
        }
    }
    return -1;  
}
int Network::readUsers(const char* fname) {
    std::ifstream file(fname);
    if (!file) return -1;

    int numUsers;
    file >> numUsers;
    file.ignore(); // skip the newline after the number

    for (int i = 0; i < numUsers; ++i) {
        int id, birthYear, zip;
        std::string name;

        file >> id;
        file.ignore();               // consume newline
        std::getline(file, name);   // supports full names with spaces
        name = trim(name); 
        file >> birthYear >> zip;
        file.ignore();              // consume newline

        std::set<int> friends;
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        int friendId;
        while (iss >> friendId) {
            friends.insert(friendId);
        }

        User* user = new User(id, name, birthYear, zip, friends);
        addUser(user);
    }

    file.close();
    return 0;
}
int Network::writeUsers(char* fname) {
    std::ofstream file(fname);
    if (!file) return -1;

    file << users_.size() << std::endl;

    for (auto user : users_) {
        file << user->getId() << std::endl;
        file << user->getName() << std::endl;
        file << user->getYear() << std::endl;
        file << user->getZip() << std::endl;

        const std::set<int>& friends = user->getFriends();
        for (auto fid = friends.begin(); fid != friends.end(); ++fid) {
            file << *fid;
            if (std::next(fid) != friends.end()) file << " ";
        }
        file << std::endl;
    }

    file.close();
    return 0;
}

int Network::numUsers() {
    return users_.size();
}

User* Network::getUser(int id) {
    if (id >= 0 && id < users_.size()) {
        return users_[id];
    }
    return nullptr;  
}

std::vector<int> Network::shortestPath(int from, int to) {
    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> previous(users_.size(), -1); // to reconstruct path

    visited[from] = true;
    q.push(from);

    //goes through the queue and checks off the neighbors 
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : users_[current]->getFriends()) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                previous[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    //path if the to is not visited from any 'from'
    std::vector<int> path;
    if (!visited[to]) {
        return path; // return empty if no path
    }

    // Reconstruct path from `to` to `from`
    for (int i = to; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    //to output in the right order 
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> previous(users_.size(), -1);
    std::vector<int> level(users_.size(), -1);  // tracks BFS level (distance)

    visited[from] = true;
    level[from] = 0;
    q.push(from);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : users_[current]->getFriends()) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                level[neighbor] = level[current] + 1; //difference from before is that we are also counting levels now 
                previous[neighbor] = current;
                q.push(neighbor);

                if (level[neighbor] == distance) {
                    to = neighbor; // found someone at exact distance

                    // Reconstruct path
                    std::vector<int> path;
                    for (int at = to; at != -1; at = previous[at]) {
                        path.push_back(at);
                    }
                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    // No user found at the given distance
    to = -1;
    return {};
}

std::vector<int> Network::suggestFriends(int who, int& score) {
    std::vector<int> suggestions;
    score = 0;
    //initial check for valid user
    if (who < 0 || who >= users_.size()) {
        return suggestions;
    }
    //adding current friends to a set 
    const std::set<int>& userFriends = users_[who]->getFriends();
    std::set<int> alreadyKnown(userFriends);
    alreadyKnown.insert(who);  //avoid recommending self 

    std::map<int, int> mutualCounts;  // candidate ID is mutual friend count

    for (int friendId : userFriends) {
        const std::set<int>& friendsOfFriend = users_[friendId]->getFriends();
        for (int candidate : friendsOfFriend) {
            if (alreadyKnown.find(candidate) == alreadyKnown.end()) {
                mutualCounts[candidate]++;
            }
        }
    }

    // Find highest score and collect candidates with it
    for (const auto& entry : mutualCounts) {
        if (entry.second > score) {
            score = entry.second;
            suggestions.clear();
            suggestions.push_back(entry.first);
        } else if (entry.second == score) {
            suggestions.push_back(entry.first);
        }
    }

    return suggestions;
}

//helper function for groups 
void Network::dfs(int start, std::vector<bool>& visited, std::vector<int>& group) {
    std::stack<int> stack;
    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        group.push_back(current);
        //conducts dfs for each user to find connections in the group 
        for (int neighbor : users_[current]->getFriends()) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}
std::vector<std::vector<int> > Network::groups() {
    std::vector<std::vector<int> > allGroups;
    std::vector<bool> visited(users_.size(), false);

    for (int i = 0; i < users_.size(); ++i) {
        if (!visited[i]) {
            std::vector<int> group;
            //adds new group in allGroups with their connected group 
            dfs(i, visited, group);
            allGroups.push_back(group);
        }
    }

    return allGroups;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic) {
    int messageId = 0;
    // Determine the next available message ID
    for (auto user : users_) {
        for (auto post : user->getPosts()) {
            messageId = std::max(messageId, post->getMessageId() + 1);
        }
    }
    // Create the appropriate type of post  
    Post* newPost;
    if (isIncoming) {
        newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
    } else {
        newPost = new Post(messageId, ownerId, message, likes);
    }
    // Add the post to the specified user
    User* owner = getUser(ownerId);
    if (owner) {
        owner->addPost(newPost);
    }
}


// Returns a formatted string of a user’s most recent posts.
// Filters based on howMany and whether to include only public posts.
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) {
    User* user = getUser(ownerId);
    if (!user) return "";
    return user->getPostsString(howMany, showOnlyPublic);
}


// Writes all posts from all users to a file, sorted by messageId.
// File format supports both Post and IncomingPost objects.
int Network::writePosts(char* fname) {
    std::ofstream file(fname);
    if (!file) return -1;

    // Collect all posts from all users
    std::vector<Post*> allPosts;
    for (User* user : users_) {
        for (Post* post : user->getPosts()) {
            allPosts.push_back(post);
        }
    }

    // Sort posts by messageId
    std::sort(allPosts.begin(), allPosts.end(), [](Post* a, Post* b) {
        return a->getMessageId() < b->getMessageId();
    });

    file << allPosts.size() << "\n";

    for (Post* post : allPosts) {
        file << post->getMessageId() << "\n";
        file << post->getMessage() << "\n";
        file << post->getOwnerId() << "\n";
        file << post->getLikes() << "\n";

        IncomingPost* ip = dynamic_cast<IncomingPost*>(post);
        if (ip) {
            file << (ip->getIsPublic() ? "public" : "private") << "\n";
            file << ip->getAuthor() << "\n";
        } else {
            file << "\n\n";  // blank lines for regular posts
        }

        //  Write reactions
        std::map<std::string, std::vector<User*>> reactions = post->getReactionMap();
        for (const auto& [reactionType, usersVec] : reactions) {
            for (User* user : usersVec) {
                file << "REACT|" << post->getMessageId() << "|"
                     << user->getName() << "|" << reactionType << "\n";
            }
        }
    }

    file.close();
    return 0;
}

int Network::readPosts(char* fname) {
    std::ifstream file(fname);
    if (!file) return -1;

    int numPosts;
    file >> numPosts;
    file.ignore();

    std::map<int, Post*> postMap;  // messageId → Post pointer

    for (int i = 0; i < numPosts; ++i) {
        int messageId;
        std::string message;
        int ownerId;
        int likes;
        std::string visibility;
        std::string author;

        file >> messageId;
        file.ignore();
        std::getline(file, message);
        file >> ownerId;
        file >> likes;
        file.ignore();
        std::getline(file, visibility);
        std::getline(file, author);

        Post* post;
        if (visibility == "public" || visibility == "private") {
            bool isPublic = (visibility == "public");
            post = new IncomingPost(messageId, ownerId, message, likes, isPublic, author);
        } else {
            post = new Post(messageId, ownerId, message, likes);
        }

        User* owner = getUser(ownerId);
        if (owner) {
            owner->addPost(post);
        }

        postMap[messageId] = post;
    }

    // Now read reaction lines (REACT|...)
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("REACT|", 0) == 0) {
            std::stringstream ss(line);
            std::string tag, messageIdStr, username, type;

            std::getline(ss, tag, '|');
            std::getline(ss, messageIdStr, '|');
            std::getline(ss, username, '|');
            std::getline(ss, type);

            int messageId = std::stoi(messageIdStr);
            Post* post = postMap[messageId];
            User* user = getUser(getId(username));

            if (post && user) {
                post->addReaction(user, type);
            }
        }
    }

    file.close();
    return 0;
}
