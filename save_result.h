#ifndef SAVE_RESULT_H
#define SAVE_RESULT_H

#include <QDockWidget>
#include <QFile>
#include "mainwindow.h"

namespace Ui {
class save_result;
}

class save_result : public QDockWidget
{
    Q_OBJECT

public:
    explicit save_result(MainWindow* mainwindow);
    ~save_result();

private slots:
    void on_save_clicked();

    void on_only_read_clicked();

    void on_hidden_clicked();

    void on_normal_clicked();

    void on_archive_clicked();

    void on_directory_clicked();

    void on_compresed_clicked();

private:
    Ui::save_result *ui;
    MainWindow* mainwindow;
    QStringList old_names;

    bool normal = false;
    bool only_read = false;
    bool hidden = false;
    bool archive = false;
    bool directory = false;
    bool compresed = false;

};

#endif // SAVE_RESULT_H
