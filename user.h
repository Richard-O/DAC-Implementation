#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User: public QObject
{
    Q_OBJECT
public:
    explicit User(QString username);
    QString getUsername();
    QString getName();
    QString getPassword();
    void setUsername(QString username);
    void setName(QString name);
    void setPassword(QString password);

private:
    QString username;
    QString name;
    QString password;

};

#endif // USER_H
