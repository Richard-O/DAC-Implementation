#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <iostream>
#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QList>
#include <map>
#include <QDir>
#include "user.h"


#define COMPANY_NAME "YUDO"
#define APP_NAME "DACImplementation"

#define ACL_STRING "Access Control List"
#define USERS_STRING "Users"
#define CURRENT_DIRECTORY_KEY "current_directory"
#define FILE_OWNERS "FILE_OWNERS"

/*
 * list of users
 * list of files
 * user-to-file(path)-to-access-level
 *
 * */

struct FileAccessLevel{
    static const int LOCKED = 0;
    static const int READ = 1;
    static const int READ_WRITE = 2;
};


class SettingsManager{
public:

    SettingsManager();

    void saveUser(User *user);

    User* getUser(QString username);

    QList<User*> getAllUsers();

    void saveFileAccessLevel(QString filePath, QString userID, const int permissionLevel);

    int getFileAccessLevel(QString filePath, QString userID);

    void saveOwner(QString filePath, QString username);

    QString getOwner(QString filePath);

    QVariant getValue(QString ID, QVariant def = QVariant());

    void saveValue(QString key, QVariant value);



};

#endif // SETTINGSMANAGER_H
