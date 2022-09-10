#ifndef SERVER_VIEW_H
#define SERVER_VIEW_H
#include <QGroupBox>
#include <QList>

struct package;
class QPushButton;
class QLabel;
class QIcon;
class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class ServerModel;
class ServerView : public QGroupBox{
        Q_OBJECT
    public:
        ServerView(QWidget *parent);
        ~ServerView();
        void setupViews();
        void updateLabel(QString msg);

    signals:
        void updateStatus(QString msg);

    private slots:
        void updateclientStatus(QString msg);
        void updateTable();
        void startServer();
        void handleSetConfig();

    private:
        ServerModel *server;
        QPushButton *start, *set_config;
        QLabel *host_config;
        QTableWidget *table_view;
        QVBoxLayout *main_layout;
        QHBoxLayout *top_layout;

        QIcon server_icon = QIcon("./icons/server_icon.ico");
};


#endif