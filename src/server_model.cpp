#include "../headers/server_model.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDomDocument>
#include <QDomAttr>
#include <QDomElement>
#include <QDomNode>
#include <QDomText>
#include <QDomEntity>
#include <QList>
#include <QString>
#include <QHostAddress>
#include <QByteArray>

struct package{
    QString weight, pallete, code, container_type;
    QList<QString> dimensions;
};

ServerModel::ServerModel()
    :QTcpServer(){
    package_data = new QList<package*>();
    connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
}

ServerModel::~ServerModel(){
    for(auto package: *package_data){
        delete package;
    }
    delete req_data;
    delete package_data;
    delete connection;
    this->close();
}


void ServerModel::setHomeConfig(){
    QHostAddress home = QHostAddress("127.0.0.1");
    this->listen(home, 3682);
    qDebug() << this->serverError();
}

void ServerModel::setHostConfig(const QHostAddress &address, quint16 port){
    this->listen(address, port);
    qDebug() << this->serverError();
}

void ServerModel::setData(){
    QByteArray totol_data, data_buffer;
    connection = dynamic_cast<QTcpSocket*>(sender());
    data_buffer = connection->readAll();
    totol_data.append(data_buffer);

    req_data = new QString(QString::fromUtf8(totol_data));
    emit newData();
}

void ServerModel::parseXMl(){
    QDomDocument req_doc;
    QString *error = new QString();
    package_data->clear();
    int *errline = new int, *errcol = new int;
    bool parsed = req_doc.setContent(req_data->mid(req_data->indexOf("<")), false, error, errline, errcol);

    if(parsed){
        QDomNodeList palettes = req_doc.childNodes().at(1).childNodes();
        for(int i = 0; i < palettes.length(); i++){
            QDomElement palette = palettes.at(i).toElement();
            QDomNodeList packages = palette.childNodes();
            for (int j = 0; j < packages.length(); j++){
                package *p_container = new package;
                if (packages.at(j).nodeName().toLower() == "box"){
                    QDomElement box = packages.at(j).toElement();
                    QDomNodeList values = box.childNodes();

                    p_container->code = values.at(0).toElement().text();
                    p_container->weight = values.at(1).toElement().text();
                    p_container->pallete = palettes.at(i).toElement().attribute("number");
                    p_container->container_type = "Box";
                    p_container->dimensions.append(values.at(2).toElement().text()); // Height
                    p_container->dimensions.append(values.at(3).toElement().text()); // Length
                    p_container->dimensions.append(values.at(4).toElement().text()); // Breadth
                } else {
                    QDomElement cylinder = packages.at(j).toElement();
                    QDomNodeList values = cylinder.childNodes();
                    
                    p_container->code = values.at(0).toElement().text();
                    p_container->weight = values.at(1).toElement().text();
                    p_container->pallete = palettes.at(i).toElement().attribute("number");
                    p_container->container_type = "Cylinder";
                    p_container->dimensions.append(values.at(2).toElement().text()); // Height
                    p_container->dimensions.append(values.at(3).toElement().text()); // Diameter 
                }

                package_data->append(p_container);
            }        
        }
    } else {
        qDebug() << "Error: " << *error;
        qDebug() << "No: " << *errline;
        qDebug() << "Col: " << *errcol;

        emit ParseProblem("There was a problem with the data please contact support.");
    }

    delete error;
    delete errline;
    delete errcol;

}

QList<package*> *ServerModel::getPackageData(){
    return package_data;
}

void ServerModel::handleNewConnection(){
    // need to grab the socket
    QTcpSocket *newSocket = this->nextPendingConnection();
    if(newSocket)
    {
        connect(newSocket, SIGNAL(readyRead()), this, SLOT(setData()));

        //Additionnal auto clean-up without keeping track of the pointer
        connect(newSocket, SIGNAL(disconnected()), newSocket, SLOT(deleteLater()));
    }
}