#include "network.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void displayMenu() {
    cout << "Menu Options:\n";
    cout << "1. Add a user.\n";
    cout << "2. Add a friend connection.\n";
    cout << "3. Delete a friend connection.\n";
    cout << "4. Write to file.\n";
    cout << "5. View posts.\n";
    cout << "6. Exit.\n";
    cout << "Please enter your choice: ";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./social_network users.txt posts.txt" << endl;
        return -1;
    }

    Network network;
    if (network.readUsers(argv[1]) != 0) {
        cerr << "Error: Could not read the users file." << endl;
        return -1;
    }
    if (network.readPosts(argv[2]) != 0) {
        cerr << "Error: Could not read the posts file." << endl;
        return -1;
    }


    int choice;
    string name1, name2;
    int year, zip, id;
    string firstName, lastName, firstName2, lastName2;
    set<int> friends;  
    string filename;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            id = network.numUsers() + 1;
            cout << "Enter the user's first name, last name, birth year, and zip code: ";
            cin >> firstName >> lastName >> year >> zip;
            User* newUser = new User(id, firstName + " " + lastName, year, zip, friends);
            network.addUser(newUser);
            cout << "User added: " << firstName << " " << lastName << endl;
        }
        else if (choice == 2) {
            cout << "Enter the first full name: ";
            getline(cin, name1);
            cout << "Enter the second full name: ";
            getline(cin, name2);
            if (network.addConnection(name1, name2) == 0) {
                cout << "Friend connection added between " << name1 << " and " << name2 << endl;
            } else {
                cout << "Error: One or both users do not exist." << endl;
            }
        }
        else if (choice == 3) {
            cout << "Enter the first full name: ";
            getline(cin, name1);
            cout << "Enter the second full name: ";
            getline(cin, name2);
            if (network.deleteConnection(name1, name2) == 0) {
                cout << "Friend connection removed between " << name1 << " and " << name2 << endl;
            } else {
                cout << "Error: One or both users do not exist or are not friends." << endl;
            }
        }
        else if (choice == 4) {
            cout << "Enter the filename to save the user data: ";
            cin >> filename;
            if (network.writeUsers(const_cast<char*>(filename.c_str())) == 0) {
                cout << "Users successfully written to " << filename << endl;
            } else {
                cout << "Error: Could not write to the file." << endl;
            }
        }
        else if (choice == 5) {
            std::string firstName, lastName;
            int howMany;

            cout << "Enter the user's first and last name followed by number of posts to view: ";
            cin >> firstName >> lastName >> howMany;

            std::string fullName = firstName + " " + lastName;
            int userId = network.getId(fullName);

            if (userId == -1) {
                cout << "Error: User not found." << endl;
            } else {
                cout << network.getPostsString(userId, howMany, false) << endl;
            }
        }
        else if (choice >= 6) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
