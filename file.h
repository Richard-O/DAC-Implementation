#ifndef FILE_H
#define FILE_H

#include <QString>

#include "user.h"

class File
{
public:
    File();
    void setName(QString name);
    void setPath(QString path);
    void setOwner(User *user);
    QString getName();
    QString getPath();
    User* getOwner();

private:
    QString name;
    QString path;
    User *owner;



};

#endif // FILE_H
