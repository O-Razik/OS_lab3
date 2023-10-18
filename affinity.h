#ifndef AFFINITY_H
#define AFFINITY_H

#include "process.h"
#include <QDockWidget>

namespace Ui {
class Affinity;
}

class Affinity : public QDockWidget
{
    Q_OBJECT

public:
    explicit Affinity(QWidget *parent = nullptr);
    void get_pro(Process* pro);
    ~Affinity();

private slots:
    void on_change_accepted();

    void on_CPU_0_clicked();

    void on_CPU_1_clicked();

    void on_CPU_2_clicked();

    void on_CPU_3_clicked();

    void on_CPU_4_clicked();

    void on_CPU_5_clicked();

    void on_CPU_6_clicked();

    void on_CPU_7_clicked();

    void on_CPU_8_clicked();

    void on_CPU_9_clicked();

    void on_CPU_10_clicked();

    void on_CPU_11_clicked();

private:
    Ui::Affinity *ui;
    Process* pro;
    bool affinity[12] = {0};
};

#endif // AFFINITY_H
