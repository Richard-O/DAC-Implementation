#include "filemanagerwindow.h"
#include "filestub.h"

#include <QScrollArea>
#include <QHBoxLayout>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QStringList>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

#define DEFAULT_DIRECTORY "/home/richard/Documents"
#define EXTENSION ".ric"

FileManagerWindow::FileManagerWindow(QWidget *parent) :
    QMainWindow(parent)
{


    this->setFixedSize(620, 480);
    QWidget *centralWidget = new QWidget();

    mainLayout = new QVBoxLayout();
    QHBoxLayout *hlay = new QHBoxLayout();
    QHBoxLayout *hlay2 = new QHBoxLayout();


    cbUsers = new QComboBox();
    QList<User*> users = sm.getAllUsers();
    for (int i = 0; i < users.size(); i++){
        User* user = users.at(i);
        cbUsers->addItem(user->getUsername(), QVariant::fromValue(user));
    }

    hlay->addWidget(cbUsers);
    btnNewUser = new QPushButton();
    QPixmap p1(":/images/new-user.png");
    btnNewUser->setIcon(QIcon(p1));
    btnNewUser->setFixedWidth(50);
    hlay->addWidget(btnNewUser);

    hlay2->addStretch(1);
    txtFileName = new QLineEdit();
    hlay2->addWidget(txtFileName);
    btnNewFile = new QPushButton();
    QPixmap p(":/images/new-file.png");
    btnNewFile->setIcon(QIcon(p));
    hlay2->addWidget(btnNewFile);


    QScrollArea *qa = new QScrollArea();
    mainLayout->addLayout(hlay);
    mainLayout->addLayout(hlay2);
    loadFiles();
    centralWidget->setLayout(mainLayout);
    centralWidget->setFixedSize(600, 480);

    qa->setWidget(centralWidget);
    this->setCentralWidget(qa);


    connect(btnNewUser, SIGNAL(clicked(bool)), this, SLOT(createUser()));
    connect(btnNewFile, SIGNAL(clicked(bool)), this, SLOT(createFile()));
    connect(cbUsers, SIGNAL(currentIndexChanged(int)), this, SLOT(loadFiles()));

}

void FileManagerWindow::saveUser(){

    if (ui.txtuname->text() != ""){
        User *user = new User(ui.txtuname->text());
        user->setName(ui.txtname->text());
        user->setPassword(ui.txtpass->text());
        sm.saveUser(user);

        cbUsers->clear();
        QList<User*> users = sm.getAllUsers();
        for (int i = 0; i < users.size(); i++){
            User* user = users.at(i);
            cbUsers->addItem(user->getUsername(), QVariant::fromValue(user));
        }
    }

}

void FileManagerWindow::createUser(){

    QDialog *widget = new QDialog;
    ui.setupUi(widget);
    connect(widget, SIGNAL(accepted()), this , SLOT(saveUser()));
    widget->show();
}

void FileManagerWindow::createFile(){
    QDir myDir(sm.getValue(CURRENT_DIRECTORY_KEY, DEFAULT_DIRECTORY).toString());

    QString path;
    if (txtFileName->text() != ""){
        path.append(myDir.absolutePath()).append("/").append(txtFileName->text().append(EXTENSION));
        QFile file(path);
        file.open(QFile::ReadWrite);
        sm.saveFileAccessLevel(path, cbUsers->currentText(), FileAccessLevel::READ_WRITE);
        sm.saveOwner(path, cbUsers->currentText());
        txtFileName->setText("");
        QDesktopServices::openUrl(QUrl(path));
        loadFiles();
    }else {
        QMessageBox msgBox;
        msgBox.setText("Error. Please enter a filename");
        msgBox.exec();
    }
}

void FileManagerWindow::clearLayout(QLayout *layout){
    if ( layout != NULL )
    {
        QLayoutItem* item;
        while ( ( item = layout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

void FileManagerWindow::loadFiles(){
    mainLayout->removeItem(layout);
    //clearLayout(layout);
    layout = new CustomGridLayout(this, 4);
    QDir myDir(sm.getValue(CURRENT_DIRECTORY_KEY, DEFAULT_DIRECTORY).toString());

    QStringList filters;
    QString type = QString("*").append(EXTENSION);
    filters << type;

    QFileInfoList list = myDir.entryInfoList(filters, QDir::Files);

    for (int i = 0; i < list.size(); i++){

        File *m = new File();
        m->setName(list.at(i).fileName());
        m->setPath(list.at(i).absoluteFilePath());

        User *user = new User(cbUsers->currentText());
        FileStub *fs = new FileStub(m, user);
        fs->setType(sm.getFileAccessLevel(m->getPath(), user->getUsername()));
        layout->addWidgetCustom(fs);

    }
    mainLayout->addLayout(layout);
}


FileManagerWindow::~FileManagerWindow()
{
}
