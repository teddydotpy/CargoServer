#include "../headers/mainclient.h"

#include <QAction>
#include <QMenu>
#include <QSize>
#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTabWidget>
#include <QTabBar>
#include <QTextBlock>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QFile>

MainClient::MainClient(QWidget *parent)
    : QMainWindow(parent){

    // Setup actions
    setupActions();

    // Setup menu
    setupMenus();

    //Setup main widget
    setupMainWidget();

    // Connect Signals and Slots
    // Connect Signals and Slots as required
    connect(actAbout, &QAction::triggered, this, &MainClient::showAbout);
    connect(actHelp, &QAction::triggered, this, &MainClient::showHelp);
    connect(actExit, SIGNAL(triggered()), this, SLOT(closeWindow()));

    // Initialize window
    setWindowTitle("Server");
    setMinimumSize(1024, 550);
    statusBar()->showMessage("Ready...");
}

MainClient::~MainClient(){
    // Tidy up pointers, if required

}

void MainClient::showAbout(){
    // Display 'About' information here
    about_dialog = new QMessageBox(this);
    about_dialog->setWindowTitle("About");
    about_dialog->setMaximumSize(512, 256);
    about_dialog->setText(getInfoText("config/about_server.txt"));
    about_dialog->exec();
}

void MainClient::showHelp(){
    // Display 'Help' information here
    help_dialog = new QMessageBox(this);
    help_dialog->setWindowTitle("Help");
    help_dialog->setMaximumSize(512, 256);
    help_dialog->setText(getInfoText("config/help_server.txt"));
    help_dialog->exec();
}

QString MainClient::getInfoText(QString filepath){
    QFile file = QFile(filepath);
    if (!file.open(QIODeviceBase::ReadOnly)){
        return "";
    }

    QString about = file.readAll();
    file.close();
    return about;
}

void MainClient::setupActions(){
    // Set up QActions as required
    // Create resource file for images in sub-directory 'icons'.

    actAbout = new QAction(info_icon, "About");
    actBackup = new QAction(backup_icon, "Backup");
    actRestore = new QAction(restore_icon, "Restore");
    actHelp = new QAction(help_icon, "Help");
    actExit = new QAction(exit_icon, "Exit");
}

void MainClient::setupMenus(){
    // Set up QMenus as required
    
    mnuFile = menuBar()->addMenu("File");
    mnuFile->addSeparator();
    mnuFile->addAction(actBackup);
    mnuFile->addAction(actRestore);
    mnuFile->addAction(actExit);

    // Add items to Save and Restore containers

    mnuHelp = menuBar()->addMenu("Help");
    mnuHelp->addAction(actAbout);
    mnuHelp->addAction(actHelp);
}


void MainClient::setupMainWidget(){

}

void MainClient::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Server",
                                                                tr("Are you really sure you want to leave?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainClient::closeWindow(){
    // Confirm that user wants to close the application
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Server",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes) {
        this->close();
    }
}

void MainClient::updateStatus(QString msg){
    statusBar()->showMessage(msg);
    statusBar()->update();
}
