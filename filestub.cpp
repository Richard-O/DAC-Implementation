#include "filestub.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPlainTextEdit>


FileStub::FileStub(File *file, User *user, QWidget *parent)
    :QWidget(parent),
      iconPixmap(":/images/file-locked.png"),
      user(user),
      file(file),
      type(FileAccessLevel::LOCKED)
{
    this->setFixedSize(140, 160);

    lblIcon = new QLabel();
    lblIcon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    lblIcon->setStyleSheet("QLabel { background-color : #fff5cc; color : white; qproperty-alignment: 'AlignCenter'}");
    lblIcon->setPixmap(iconPixmap);

    if (sm.getOwner(file->getPath()) == user->getUsername()){
        QLabel *tag = new QLabel(lblIcon);
        tag->setText("O");
        tag->setStyleSheet("QLabel { background-color : #b35900; color : white; font: bold 12px Courier;}");
        tag->setFixedSize(20, 20);
        tag->setWindowFlags(Qt::FramelessWindowHint);
     }

    QLabel *lblName = new QLabel();
    lblName->setText(file->getName());
    lblName->setStyleSheet("QLabel { background-color : #b35900; color : white;font: bold 12px Courier; qproperty-alignment: 'AlignBottom'}");

    QVBoxLayout *lay = new QVBoxLayout();
    lay->addStretch(1);
    lay->addWidget(lblName);
    lblIcon->setLayout(lay);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(lblIcon);
    //vlayout->addWidget(lblName);

    this->setLayout(vlayout);


}

void FileStub::savePermissions(){
    sm.saveFileAccessLevel(file->getPath(), ui.cbUsers->currentText(), ui.cbPermissions->currentIndex());
    if (user->getUsername() == ui.cbUsers->currentText()){
        this->setType(ui.cbPermissions->currentIndex());
    }
}

bool FileStub::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::MouseButtonPress:
        if (dynamic_cast<QMouseEvent*>(e)->button() == Qt::RightButton){
            if (sm.getOwner(file->getPath()) == user->getUsername()){
                QDialog *widget = new QDialog;

                ui.setupUi(widget);
                QList<User*> users = sm.getAllUsers();
                for (int i = 0; i < users.size(); i++){
                    User* user = users.at(i);
                    ui.cbUsers->addItem(user->getUsername(), QVariant::fromValue(user));
                }
                ui.cbUsers->setCurrentText(user->getUsername());

                QStringList levels;
                levels << "Locked" << "Read" << "Read & Write";
                ui.cbPermissions->addItems(levels);
                ui.cbPermissions->setCurrentIndex(sm.getFileAccessLevel(file->getPath(), user->getUsername()));
                connect(widget, SIGNAL(accepted()), this , SLOT(savePermissions()));
                widget->show();
           }
        }else{
            if (type == FileAccessLevel::READ_WRITE){

                QDesktopServices::openUrl(QUrl::fromLocalFile(file->getPath()));
            }else if (type == FileAccessLevel::READ){
                QFile f(file->getPath());
                if (!f.open(QFile::ReadOnly | QFile::Text)) break;
                QTextStream in(&f);
                QString str(in.readAll());

                QPlainTextEdit *w = new QPlainTextEdit(str);
                w->setFixedSize(640, 480);
                w->setReadOnly(true);
                w->show();
            }else{
                QMessageBox msgBox;
                msgBox.setText("You do not have access to open this file!");
                msgBox.exec();
            }
        }
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void FileStub::setType(const int type){
    if (type == FileAccessLevel::LOCKED){
        this->type = type;
        lblIcon->setPixmap(QPixmap(":/images/file-locked.png"));
    }else if (type == FileAccessLevel::READ){
        this->type = type;
        lblIcon->setPixmap(QPixmap(":/images/file-read.png"));
    }else if (type == FileAccessLevel::READ_WRITE ){
        this->type = type;
        lblIcon->setPixmap(QPixmap(":/images/file-read-write.png"));
    }
}

int FileStub::getType(){
    return type;
}
