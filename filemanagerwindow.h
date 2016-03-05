#ifndef FILEMANAGERWINDOW_H
#define FILEMANAGERWINDOW_H

#include "settingsmanager.h"
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "user.h"
#include "file.h"
#include "customgridlayout.h"

namespace Ui {
class FileManagerWindow;
}

class FileManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileManagerWindow(QWidget *parent = 0);
    SettingsManager sm;
    CustomGridLayout *layout;
    ~FileManagerWindow();

private:
    QComboBox *cbUsers;
    QPushButton *btnNewUser;
    QPushButton *btnNewFile;
    QLineEdit *txtFileName;
    QVBoxLayout *mainLayout;
    void clearLayout(QLayout *layout);

public slots:
    void loadFiles();
    void createUser();
    void createFile();



};

#endif // FILEMANAGERWINDOW_H
