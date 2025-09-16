#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "network.h"
#include "post.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

private slots:
    void onLoginClicked();
    void onFriendClicked(QTableWidgetItem* item);
    void onAddFriendClicked();
    void onAddPostClicked();
    void onAddThisFriendClicked();
    void goBackToProfile();
    void onReactionClicked(Post* post, const std::string& type);
    void onViewReactorsClicked(Post* post, const std::string& type);

private:
    Ui::SocialNetworkWindow *ui;

    Network network;
    User* loggedInUser;
    User* currentUser;
    void display(); // central display logic
    void loadUsers();
    void updateUsersFile();
    void updatePostsFile();
};

#endif // SOCIALNETWORKWINDOW_H
