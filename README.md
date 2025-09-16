# 👥 Friends Network & Posts (C++)  

A simple social network simulation built in **C++**.  
Users can connect with friends, create posts, and view incoming posts from their network.  

---

## 🚀 Features  
- Create and manage users  
- Add and manage friendships between users  
- Create posts with content (e.g., messages, IDs, or timestamps)  
- Each user can view their **incoming posts** based on friends in their network  
- Console-based program with object-oriented design  

---

## 📂 Project Structure  
```
FriendsNetwork/
│── main.cpp           # Entry point (menu / driver program)
│── user.h / user.cpp  # User class (manages user data and friends)
│── post.h / post.cpp  # Post class (represents content shared by users)
│── network.h / network.cpp # Network class (manages users, friendships, and posts)
│── Makefile           # Build file
```

---

## ⚙️ Requirements  
- **C++17** (or later)  
- Standard library (no external dependencies)  

---

## 🛠️ Build Instructions  
```bash
# Compile
g++ -std=c++17 main.cpp user.cpp post.cpp network.cpp -o friends_network

# Run
./friends_network
```

---

## 🎯 Example Usage  
1. Start the program.  
2. Add users to the network.  
3. Connect users as friends.  
4. Create posts from one user.  
5. Check incoming posts for another user to see what their friends shared.  


## 📜 License  
MIT License – free to use and modify.  

---

✨ Built as a learning project to practice **C++ object-oriented programming** and **data structures**.  
