#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H
#include <QTcpServer>
#include <QList>

struct package;
class QTcpSocket;
class QString;
class QHostAddress;
class ServerModel : public QTcpServer{
        Q_OBJECT
    public:
        ServerModel();
        ~ServerModel();

        void setHomeConfig();
        void setHostConfig(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
        void parseXMl();
        QList<package*> *getPackageData();

    private:
        QTcpSocket *connection;
        QString *req_data;
        QList<package*> *package_data;

    signals:
        void newData();
        void ParseProblem(QString msg);

    public slots:
        void setData();
        void handleNewConnection();
};  

#endif