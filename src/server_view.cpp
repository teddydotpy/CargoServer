#include "../headers/server_view.h"
#include "../headers/server_model.h"

#include <QStringList>
#include <QList>
#include <QInputDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

struct package{
    QString weight, pallete, code, container_type;
    QList<QString> dimensions;
};
ServerView::ServerView(QWidget *parent)
    :QGroupBox(parent){
    setupViews();
    server = new ServerModel();

    connect(start, SIGNAL(clicked()), this, SLOT(startServer()));
    connect(server, SIGNAL(newData()), this, SLOT(updateTable()));
    connect(set_config, SIGNAL(clicked()), this, SLOT(handleSetConfig()));
    connect(server, SIGNAL(ParseProblem(QString)), this, SLOT(updateclientStatus(QString)));
}

ServerView::~ServerView(){
    delete top_layout;
    delete server;
}   

void ServerView::startServer(){
    server->setHomeConfig();
    if (server->isListening()){
        updateLabel("Server is listening on port: " + QString::number(server->serverPort()));
    } else {
        updateLabel("There was a problem starting the server please call the support staff.");
    }
}

void ServerView::updateTable(){
    server->parseXMl();
    QList<package*> *packages = server->getPackageData();
    table_view->clear();
    table_view->setRowCount(0);
    table_view->update();
    for(auto container: *packages){
        table_view->insertRow(table_view->rowCount());
        table_view->setItem(table_view->rowCount()-1, 0, new QTableWidgetItem(container->pallete));
        table_view->setItem(table_view->rowCount()-1, 1, new QTableWidgetItem(container->container_type));
        table_view->setItem(table_view->rowCount()-1, 2, new QTableWidgetItem(container->code));
        table_view->setItem(table_view->rowCount()-1, 3, new QTableWidgetItem(container->dimensions[0]));
        if(container->container_type.toLower() == "box"){
            table_view->setItem(table_view->rowCount()-1, 4, new QTableWidgetItem(container->dimensions[1]));
            table_view->setItem(table_view->rowCount()-1, 6, new QTableWidgetItem(container->dimensions[2]));
        } else {
            table_view->setItem(table_view->rowCount()-1, 5, new QTableWidgetItem(container->dimensions[1]));
        }
        table_view->setItem(table_view->rowCount()-1, 7, new QTableWidgetItem(container->weight));
    }
    QStringList table_col = {"Pallet", "Container", "Code", "Height", "Breadth", "Diameter", "Length", "Weight"};
    table_view->setHorizontalHeaderLabels(table_col);
    table_view->update();
}

void ServerView::setupViews(){
    QStringList table_col = {"Pallet", "Container", "Code", "Height", "Breadth", "Diameter", "Length", "Weight"};
    start = new QPushButton(server_icon, "Start Server", this);
    set_config = new QPushButton("Set Configurations", this);
    host_config = new QLabel(this);

    table_view = new QTableWidget(this);
    table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_view->setColumnCount(8);
    table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_view->setHorizontalHeaderLabels(table_col);

    main_layout = new QVBoxLayout(this);
    top_layout = new QHBoxLayout();

    top_layout->addWidget(start);
    top_layout->addWidget(host_config);

    main_layout->addLayout(top_layout);
    main_layout->addWidget(table_view);
    main_layout->addWidget(set_config);

    this->setLayout(main_layout);
}

void ServerView::updateLabel(QString msg){
    host_config->setText(msg);
    host_config->update();
}

void ServerView::handleSetConfig(){
    QMessageBox::about(this, "Cargo App",
        tr("Due to unforseen circumstances this will be released in v2.\n"));
}

void ServerView::updateclientStatus(QString msg){
    emit updateStatus(msg);
}
