#ifndef FILESTUB_H
#define FILESTUB_H

#include "user.h"
#include "file.h"
#include "ui_permissionsdialog.h"


#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QEvent>
#include "settingsmanager.h"

class FileStub : public QWidget
{
    Q_OBJECT
public:
    explicit FileStub(File *file, User *user = 0, QWidget *parent = 0);
    QPixmap iconPixmap;
    QLabel *lblIcon;
    File *file;
    User *user;
    Ui::Dialog ui;


    bool event(QEvent * e);
    void setType(const int type);
    int getType();


private:
    SettingsManager sm;
    int type;

signals:

public slots:
    void savePermissions();
};

#endif // FILESTUB_H
