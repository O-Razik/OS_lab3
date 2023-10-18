#include "affinity.h"
#include "ui_affinity.h"

Affinity::Affinity(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Affinity)
{
    ui->setupUi(this);
}

Affinity::~Affinity()
{
    delete ui;
}

void Affinity::get_pro(Process *pro) {
    this->pro = pro;
};

void Affinity::on_change_accepted()
{
    pro->set_affinity(affinity);
    this->close();
}


void Affinity::on_CPU_0_clicked()
{
    affinity[0] = !affinity[0];
}


void Affinity::on_CPU_1_clicked()
{
    affinity[1] = !affinity[1];
}


void Affinity::on_CPU_2_clicked()
{
    affinity[2] = !affinity[2];
}


void Affinity::on_CPU_3_clicked()
{
    affinity[3] = !affinity[3];
}


void Affinity::on_CPU_4_clicked()
{
    affinity[4] = !affinity[4];
}


void Affinity::on_CPU_5_clicked()
{
    affinity[5] = !affinity[5];
}


void Affinity::on_CPU_6_clicked()
{
    affinity[6] = !affinity[6];
}


void Affinity::on_CPU_7_clicked()
{
    affinity[7] = !affinity[7];
}


void Affinity::on_CPU_8_clicked()
{
    affinity[8] = !affinity[8];
}


void Affinity::on_CPU_9_clicked()
{
    affinity[9] = !affinity[9];
}


void Affinity::on_CPU_10_clicked()
{
    affinity[10] = !affinity[10];
}


void Affinity::on_CPU_11_clicked()
{
    affinity[11] = !affinity[11];
}

