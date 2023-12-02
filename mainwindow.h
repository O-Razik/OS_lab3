#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include <chrono>

#include "process.h"
#include "qtablewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTableWidget *get_table();

private slots:
    void on_run_button_clicked();

    void on_func_tab_clicked();

    void on_discord_clicked();

    void on_msinfo32_clicked();

    void on_find_mfe_clicked();

    void create_table();

    void update_table();

    void context_menu_table(const QPoint &pos);
    void context_menu_priority(const QPoint &pos, int row);

    void on_actionManage_Results_triggered();

private:
    Ui::MainWindow *ui;

    std::vector<Process*> processes;
    bool ftab = 0, disc = 0, msinf = 0, mfe = 0;
};
#endif // MAINWINDOW_H
