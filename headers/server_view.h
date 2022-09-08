#ifndef SERVER_VIEW_H
#define SERVER_VIEW_H
#include <QTableWidget>

class QPushButton;
class QLabel;
class ServerModel;
class ServerView : public QTableWidget{
        Q_OBJECT
    public:
        ServerView(QWidget *parent);
        ~ServerView();

    public slots:
        void updateTable();

    private:
        ServerModel *server;

        QPushButton *start, *set_config;
        QLabel *host_config;
};


#endif