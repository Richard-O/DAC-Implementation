#include "settingsmanager.h"

Q_DECLARE_METATYPE(FileAccessLevel)


SettingsManager::SettingsManager()
{

}


void SettingsManager::saveUser(User *user){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(USERS_STRING);
    settings.beginGroup(user->getUsername());
    settings.setValue("name", user->getName());
    settings.setValue("password", user->getPassword());
    settings.endGroup();
    settings.endGroup();
}

User* SettingsManager::getUser(QString username){
    User *user = new User(username);
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(USERS_STRING);
    if (settings.childGroups().contains(username)){
        settings.beginGroup(username);
        user->setName(settings.value("name", "").toString());
        user->setPassword(settings.value("password", "").toString());
        settings.endGroup();
        return user;
    }
    settings.endGroup();
    return 0;
}

QList<User*> SettingsManager::getAllUsers(){

    QList<User*> users = QList<User*>();

    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(USERS_STRING);
    for (int i = 0; i < settings.childGroups().size(); i++){
        User *user = getUser(settings.childGroups().at(i));
        if (user != 0){
            users.append(user);
        }
    }
    settings.endGroup();
    return users;
}

void SettingsManager::saveFileAccessLevel(QString filePath, QString userID, const int permissionLevel){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(ACL_STRING);
    settings.beginGroup(filePath);
    settings.setValue(userID, permissionLevel);
    settings.endGroup();
    settings.endGroup();
}

int SettingsManager::getFileAccessLevel(QString filePath, QString userID){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(ACL_STRING);
    settings.beginGroup(filePath);
    const int value = settings.value(userID, FileAccessLevel::LOCKED).toInt();
    settings.endGroup();
    settings.endGroup();
    return value;
}

QVariant SettingsManager::getValue(QString ID, QVariant def){
    QSettings settings(COMPANY_NAME, APP_NAME);
    return settings.value(ID, def);
}

void SettingsManager::saveValue(QString key, QVariant value){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.setValue(key, value);
}

void SettingsManager::saveOwner(QString filePath, QString username){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(FILE_OWNERS);
    settings.setValue(filePath, username);
    settings.endGroup();
}

QString SettingsManager::getOwner(QString filePath){
    QSettings settings(COMPANY_NAME, APP_NAME);
    settings.beginGroup(FILE_OWNERS);
    QString val = settings.value(filePath, "").toString();
    settings.endGroup();
    return val;
}
