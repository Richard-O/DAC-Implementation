#include "file.h"

File::File()
{

}


QString File::getName(){
    return name;
}

void File::setName(QString name){
    this->name = name;

}

QString File::getPath(){
    return path;
}

void File::setPath(QString path){
    this->path = path;
}

User* File::getOwner(){
    return owner;
}

void File::setOwner(User *user){
    this->owner = user;
}
