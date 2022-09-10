#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include <QMainWindow>
#include <QIcon>
class QAction;
class QMenu;
class QString;
class QToolBar;
class QTabWidget;
class QWidget;
class QTabBar;
class QPushButton;
class QMessageBox;
class QHBoxLayout;
class QVBoxLayout;
class QTextBlock;
class ServerView;
class MainClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainClient(QWidget *parent = nullptr);
    ~MainClient();

    void closeEvent(QCloseEvent *event);

public slots:
    void closeWindow();
    void updateStatus(QString msg);


private slots:
    void showAbout();
    void showHelp();

private:
    void setupActions();
    void setupMenus();
    void setupMainWidget();

    QString getInfoText(QString filepath);

    ServerView *server_view;

    QMessageBox *exit_dialog;
    QMessageBox *about_dialog;
    QMessageBox *help_dialog;

    QHBoxLayout *horizontal_alignment;
    QVBoxLayout *vertical_alignment;

    QTextBlock *info_box;
    // Add QAction items as required
    QAction *actAbout;
    QAction *actHelp;
    QAction *actExit;
    QAction *actBackup;
    QAction *actRestore;

    // Add QMenu items as required
    QMenu *mnuFile;
    QMenu *mnuHelp;

    //MainWindow widgets 
    QTabBar *bar_widget;
    QTabWidget *main_widget;

    // Push Buttons
    QPushButton *ok_button;
    QPushButton *cancel_button;
    QPushButton *button_button;

    // Icons
    QIcon info_icon = QIcon("icons/info.png");
    QIcon backup_icon = QIcon("icons/backup.png");
    QIcon restore_icon = QIcon("icons/restore.png");
    QIcon help_icon = QIcon("icons/help.png");
    QIcon exit_icon = QIcon("icons/exit.png");
};

#endif // MAINCLIENT_H
