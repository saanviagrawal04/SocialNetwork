#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <iostream>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
    , loggedInUser(nullptr)
    , currentUser(nullptr)
{
    ui->setupUi(this);
    network.readUsers("/Users/saanviagrawal/Documents/CSCI62/HW1/SocialNetworkWindow/users.txt");
    network.readPosts("posts.txt");

    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::onLoginClicked);
    connect(ui->friendsTable, &QTableWidget::itemClicked, this, &SocialNetworkWindow::onFriendClicked);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddFriendClicked);
    connect(ui->addThisFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddThisFriendClicked);
    connect(ui->addPostButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddPostClicked);
    connect(ui->backToProfileButton, &QPushButton::clicked, this, &SocialNetworkWindow::goBackToProfile);

    ui->profileWidget->hide();
    ui->postsScrollArea->widget()->setLayout(ui->postsLayout);
}

SocialNetworkWindow::~SocialNetworkWindow() {
    delete ui;
}

void SocialNetworkWindow::onLoginClicked() {
    std::string name = ui->nameInput->toPlainText().toStdString();
    int id = network.getId(name);
    if (id == -1) {
        QMessageBox::warning(this, "Login Failed", "User not found. Please try again.");
    } else {
        loggedInUser = network.getUser(id);
        currentUser = loggedInUser;
        display();
    }
}

void SocialNetworkWindow::display() {
    if (!currentUser) return;

    ui->loginWidget->hide();
    ui->profileWidget->show();

    // ----- Update Profile Info -----
    if (currentUser == loggedInUser) {
        ui->profileLabel->setText("My Profile");
        ui->backToProfileButton->hide();

        ui->suggestionsTable->setColumnCount(1);
        ui->suggestionsTable->setHorizontalHeaderLabels(QStringList() << "Suggested Friends");
        ui->suggestionsTable->setRowCount(0);

        int score = 0;
        std::vector<int> suggestions = network.suggestFriends(loggedInUser->getId(), score);
        for (int id : suggestions) {
            User* u = network.getUser(id);
            if (!u) continue;
            int row = ui->suggestionsTable->rowCount();
            ui->suggestionsTable->insertRow(row);
            ui->suggestionsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(u->getName())));
        }

        ui->suggestionsTable->show();
        ui->addFriendButton->show();
        ui->addThisFriendButton->hide();
    } else {
        ui->profileLabel->setText(QString::fromStdString(currentUser->getName()) + "'s Profile");
        ui->backToProfileButton->show();
        ui->suggestionsTable->hide();
        ui->addFriendButton->hide();
        ui->addThisFriendButton->show();
    }

    // ----- Clear Previous Posts -----
    QLayoutItem* item;
    while ((item = ui->postsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    ui->postsLabel->setText("");

    // ----- Display Posts -----
    std::vector<Post*> posts = currentUser->getPosts();
    for (Post* post : posts) {
        // Post message
        QString postText = QString::fromStdString(post->getMessage());
        QLabel* postLabel = new QLabel(postText);
        postLabel->setStyleSheet("font-size: 14px; color: white; margin-bottom: 6px;");

        // Reactions
        QHBoxLayout* reactionLayout = new QHBoxLayout();
        QStringList reactionTypes = {"like", "dislike", "laugh"};
        QStringList emojis = {"👍", "👎", "😂"};
        auto reactionMap = post->getReactionMap();

        for (int i = 0; i < reactionTypes.size(); ++i) {
            QString type = reactionTypes[i];
            QPushButton* btn = new QPushButton(emojis[i]);
            btn->setFixedWidth(40);
            connect(btn, &QPushButton::clicked, [=]() {
                onReactionClicked(post, type.toStdString());
            });
            reactionLayout->addWidget(btn);

            int count = static_cast<int>(reactionMap[type.toStdString()].size());
            if (count > 0) {
                QLabel* countLabel = new QLabel(QString::number(count));
                countLabel->setStyleSheet("color: lightgray;");
                reactionLayout->addWidget(countLabel);
            }
        }

        // View Reactors Button
        QPushButton* viewReactorsBtn = new QPushButton("See who reacted");
        connect(viewReactorsBtn, &QPushButton::clicked, [=]() {
            onViewReactorsClicked(post, "like");
            onViewReactorsClicked(post, "dislike");
            onViewReactorsClicked(post, "laugh");
        });
        reactionLayout->addWidget(viewReactorsBtn);
        // Wrap post and reactions into one block
        QVBoxLayout* postBlock = new QVBoxLayout();
        postBlock->addWidget(postLabel);
        postBlock->addLayout(reactionLayout);

        QWidget* postWidget = new QWidget();
        postWidget->setLayout(postBlock);
        postWidget->setStyleSheet("background-color: #2b2b2b; border-radius: 8px; padding: 10px; margin-bottom: 12px;");

        ui->postsLayout->addWidget(postWidget);
    }

    // ----- Display Friends List -----
    ui->friendsTable->clearContents();
    ui->friendsTable->setRowCount(0);
    for (int friendId : currentUser->getFriends()) {
        User* friendUser = network.getUser(friendId);
        if (!friendUser) continue;
        int row = ui->friendsTable->rowCount();
        ui->friendsTable->insertRow(row);
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(friendUser->getName()));
        ui->friendsTable->setItem(row, 0, item);
    }
}
void SocialNetworkWindow::onFriendClicked(QTableWidgetItem* item) {
    std::string name = item->text().toStdString();
    int id = network.getId(name);
    if (id != -1) {
        currentUser = network.getUser(id);
        display();
    }
}

void SocialNetworkWindow::onAddFriendClicked() {
    if (!loggedInUser) return;
    QTableWidgetItem* selected = ui->suggestionsTable->currentItem();
    if (!selected) return;
    std::string name = selected->text().toStdString();
    network.addConnection(loggedInUser->getName(), name);
    network.writeUsers("/Users/saanviagrawal/Documents/CSCI62/HW1/SocialNetworkWindow/users.txt");
    display();
}

void SocialNetworkWindow::onAddThisFriendClicked() {
    if (!loggedInUser || !currentUser) return;
    network.addConnection(loggedInUser->getName(), currentUser->getName());
    network.writeUsers("/Users/saanviagrawal/Documents/CSCI62/HW1/SocialNetworkWindow/users.txt");
    display();
}

void SocialNetworkWindow::onAddPostClicked() {
    if (!loggedInUser || !currentUser) return;
    std::string text = ui->postInput->toPlainText().toStdString();
    if (text.empty()) return;

    if (currentUser == loggedInUser) {
        network.addPost(loggedInUser->getId(), text, 0, false, "", true);
    } else {
        network.addPost(currentUser->getId(), text, 0, true, loggedInUser->getName(), true);
    }
    network.writePosts("posts.txt");
    ui->postInput->clear();
    display();
}

void SocialNetworkWindow::goBackToProfile() {
    if (loggedInUser) {
        currentUser = loggedInUser;
        display();
    }
}

void SocialNetworkWindow::onReactionClicked(Post* post, const std::string& type) {
    if (!post || !loggedInUser) return;
    post->addReaction(loggedInUser, type);
    network.writePosts("posts.txt");
    display(); // refresh UI
}

void SocialNetworkWindow::onViewReactorsClicked(Post* post, const std::string& type) {
    if (!post) return;

    std::vector<User*> users = post->getUsersByReaction(type);
    std::set<std::string> uniqueNames;
    QString names;

    for (User* user : users) {
        std::string uname = user->getName();
        if (uniqueNames.count(uname)) continue;
        uniqueNames.insert(uname);
        names += QString::fromStdString(uname) + "\n";
    }

    if (names.isEmpty()) {
        names = "No users reacted with this emoji.";
    }

    QMessageBox::information(this, "Reactions", names);
}

