/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QWidget *profileWidget;
    QLabel *profileLabel;
    QTableWidget *friendsTable;
    QLabel *postsLabel;
    QPushButton *backToProfileButton;
    QTableWidget *suggestionsTable;
    QPushButton *addFriendButton;
    QPushButton *addThisFriendButton;
    QPushButton *addPostButton;
    QScrollArea *postsScrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *postsContainer;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *postsLayout;
    QTextEdit *postInput;
    QWidget *loginWidget;
    QVBoxLayout *verticalLayout;
    QLabel *loginPromptLabel;
    QTextEdit *nameInput;
    QPushButton *loginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->setEnabled(true);
        SocialNetworkWindow->resize(860, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        profileWidget = new QWidget(centralwidget);
        profileWidget->setObjectName("profileWidget");
        profileWidget->setGeometry(QRect(110, -40, 711, 551));
        profileLabel = new QLabel(profileWidget);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setGeometry(QRect(180, 410, 191, 101));
        friendsTable = new QTableWidget(profileWidget);
        if (friendsTable->columnCount() < 1)
            friendsTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        friendsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(65, 40, 381, 101));
        postsLabel = new QLabel(profileWidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(390, 410, 101, 31));
        postsLabel->setWordWrap(true);
        postsLabel->setTextInteractionFlags(Qt::TextInteractionFlag::LinksAccessibleByMouse|Qt::TextInteractionFlag::TextSelectableByMouse);
        backToProfileButton = new QPushButton(profileWidget);
        backToProfileButton->setObjectName("backToProfileButton");
        backToProfileButton->setGeometry(QRect(160, 170, 161, 32));
        suggestionsTable = new QTableWidget(profileWidget);
        if (suggestionsTable->columnCount() < 1)
            suggestionsTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        suggestionsTable->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        suggestionsTable->setObjectName("suggestionsTable");
        suggestionsTable->setGeometry(QRect(120, 200, 251, 141));
        addFriendButton = new QPushButton(profileWidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(190, 350, 101, 32));
        addThisFriendButton = new QPushButton(profileWidget);
        addThisFriendButton->setObjectName("addThisFriendButton");
        addThisFriendButton->setGeometry(QRect(180, 380, 131, 32));
        addPostButton = new QPushButton(profileWidget);
        addPostButton->setObjectName("addPostButton");
        addPostButton->setGeometry(QRect(190, 510, 101, 32));
        postsScrollArea = new QScrollArea(profileWidget);
        postsScrollArea->setObjectName("postsScrollArea");
        postsScrollArea->setGeometry(QRect(380, 170, 261, 201));
        postsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 259, 199));
        postsContainer = new QWidget(scrollAreaWidgetContents);
        postsContainer->setObjectName("postsContainer");
        postsContainer->setGeometry(QRect(0, -10, 361, 101));
        verticalLayoutWidget = new QWidget(postsContainer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 10, 301, 141));
        postsLayout = new QVBoxLayout(verticalLayoutWidget);
        postsLayout->setObjectName("postsLayout");
        postsLayout->setContentsMargins(0, 0, 0, 0);
        postsScrollArea->setWidget(scrollAreaWidgetContents);
        postInput = new QTextEdit(profileWidget);
        postInput->setObjectName("postInput");
        postInput->setGeometry(QRect(110, 410, 271, 101));
        loginWidget = new QWidget(centralwidget);
        loginWidget->setObjectName("loginWidget");
        loginWidget->setEnabled(true);
        loginWidget->setGeometry(QRect(10, 10, 258, 259));
        verticalLayout = new QVBoxLayout(loginWidget);
        verticalLayout->setObjectName("verticalLayout");
        loginPromptLabel = new QLabel(loginWidget);
        loginPromptLabel->setObjectName("loginPromptLabel");

        verticalLayout->addWidget(loginPromptLabel);

        nameInput = new QTextEdit(loginWidget);
        nameInput->setObjectName("nameInput");
        nameInput->setEnabled(true);

        verticalLayout->addWidget(nameInput);

        loginButton = new QPushButton(loginWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setEnabled(true);

        verticalLayout->addWidget(loginButton);

        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 860, 37));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        profileLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Profile", nullptr));
        QTableWidgetItem *___qtablewidgetitem = friendsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SocialNetworkWindow", "New Column", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        backToProfileButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Back To My Profile", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = suggestionsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SocialNetworkWindow", "New Column", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
        addThisFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add This Friend", nullptr));
        addPostButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Post", nullptr));
        loginPromptLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name.", nullptr));
        nameInput->setHtml(QCoreApplication::translate("SocialNetworkWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
