#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H
#include <QTcpServer>
#include <QList>

class QString;
class QHostAddress;
class ServerModel : public QTcpServer{

    public:
        ServerModel();
        ~ServerModel();

        void setHostConfig(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
        void parseXMl();

    private:
        struct package{
            int weight, pallete;
            QString code;
            QChar container_type;
            QList<int> dimensions;
        };
        QString *eq_data;
        QList<package*> *package_data;
};


#endif