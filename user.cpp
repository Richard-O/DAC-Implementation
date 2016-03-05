#include "user.h"


User::User(QString username)
    :username(username)
{

}



QString User::getUsername(){
    return username;
}

QString User::getName(){
    return name;
}

QString User::getPassword(){
    return password;
}


void User::setName(QString name){
    this->name = name;
}

void User::setUsername(QString username){
    this->username = username;
}

void User::setPassword(QString password){
    this->password = password;
}



