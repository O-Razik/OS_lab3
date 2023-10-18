#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "affinity.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::update_table);
    updateTimer->start(800);

    connect(ui->process_view, &QTableWidget::customContextMenuRequested, this, &MainWindow::context_menu_table);
    ui->process_view->setContextMenuPolicy(Qt::CustomContextMenu);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_func_tab_clicked()
{
    ftab = !ftab;
}


void MainWindow::on_discord_clicked()
{
    disc = !disc;
}


void MainWindow::on_msinfo32_clicked()
{
    msinf = !msinf;
}


void MainWindow::on_find_mfe_clicked()
{
    mfe = !mfe;
}


void MainWindow::on_run_button_clicked()
{
    if (ftab)
    {
        processes.push_back(new Process(
            "C:\\Users\\razik\\source\\repos\\Qt\\os_lab3\\apps_processes\\func_tab\\x64\\Debug\\func_tab.exe",
            ui->x1->value(), ui->x2->value(), ui->step->value())
                            );
    }
    if (disc)
    {
        processes.push_back(new Process(
            "C:\\Users\\razik\\AppData\\Local\\Discord\\app-1.0.9018\\Discord.exe")
                            );
    }
    if (msinf)
    {
        processes.push_back(new Process(
            "C:\\Windows\\system32\\msinfo32.exe")
                            );
    }
    if (mfe)
    {
        processes.push_back(new Process(
            "C:\\Users\\razik\\source\\repos\\Qt\\os_lab3\\find_mfe\\x64\\Debug\\find_mfe.exe",
            ui->n->value(), ui->m->value())
                            );
    }
    create_table();
}


void MainWindow::create_table()
{
    ui->process_view->setRowCount(processes.size());
    ui->process_view->setColumnCount(13);

    for (int i = 0; i < processes.size(); ++i)
    {
        QTableWidgetItem *item;

        item = new QTableWidgetItem(processes[i]->get_path());
        ui->process_view->setItem(i, 0, item);

        item = new QTableWidgetItem(QString::number(processes[i]->get_id()));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 1, item);

        item = new QTableWidgetItem(processes[i]->get_name());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 2, item);

        item = new QTableWidgetItem(processes[i]->get_state());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 3, item);
        ui->process_view->item(i, 3)->setBackground(Qt::green);

        item = new QTableWidgetItem(processes[i]->get_priority());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 4, item);

        item = new QTableWidgetItem(processes[i]->get_affinity());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 5, item);

        item = new QTableWidgetItem(processes[i]->get_cpu_time());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 6, item);

        item = new QTableWidgetItem(processes[i]->get_virtual_memory_size());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 7, item);

        item = new QTableWidgetItem(processes[i]->get_max_working_set_size());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 8, item);

        item = new QTableWidgetItem(processes[i]->get_handle_count());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 9, item);

        item = new QTableWidgetItem(processes[i]->get_thread_count());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 10, item);

        item = new QTableWidgetItem(processes[i]->get_page_faults());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 11, item);

        item = new QTableWidgetItem(processes[i]->get_user_object_count());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->process_view->setItem(i, 12, item);
    }
}


void MainWindow::update_table()
{
    QVector<int> rowsToRemove;

    for (int i = 0; i < processes.size(); ++i)
    {
        QString newState = processes[i]->get_state();

        if (newState != ui->process_view->item(i, 3)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 3);
            if (item)
                item->setText(newState);
            if(!processes[i]->is_suspended()) ui->process_view->item(i, 3)->setBackground(Qt::green);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        QString new_ = processes[i]->get_priority();
        if (new_ != ui->process_view->item(i, 4)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 4);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_affinity();
        if (new_ != ui->process_view->item(i, 5)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 5);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_cpu_time();
        if (new_ != ui->process_view->item(i, 6)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 6);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_virtual_memory_size();
        if (new_ != ui->process_view->item(i, 7)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 7);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_max_working_set_size();
        if (new_ != ui->process_view->item(i, 8)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 8);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_handle_count();
        if (new_ != ui->process_view->item(i, 9)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 9);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_thread_count();
        if (new_ != ui->process_view->item(i, 10)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 10);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_page_faults();
        if (new_ != ui->process_view->item(i, 11)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 11);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        new_ = processes[i]->get_user_object_count();
        if (new_ != ui->process_view->item(i, 12)->text())
        {
            QTableWidgetItem *item = ui->process_view->item(i, 12);
            if (item)
                item->setText(new_);
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        if (newState == "Exited")
        {
            for (int columnIndex = 0; columnIndex < ui->process_view->columnCount(); ++columnIndex) {
                ui->process_view->item(i, columnIndex)->setBackground(Qt::red);
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            rowsToRemove.append(i);
        }
    }

    QCoreApplication::processEvents();

    for (int i = rowsToRemove.size() - 1; i >= 0; --i)
    {
        int rowToRemove = rowsToRemove[i];

        processes.erase(processes.begin() + rowToRemove);
        ui->process_view->removeRow(rowToRemove);
    }
}


void MainWindow::context_menu_table(const QPoint &pos)
{
    if (ui->process_view->rowCount() != 0){
        QMenu contextMenu(this);

        QModelIndex box = ui->process_view->indexAt(pos);
        int row = box.row();

        if( row >= 0){
            QAction *action1 = contextMenu.addAction("Set Affinity");
            QAction *action2 = contextMenu.addAction("Set Priority");
            QAction *action3 = contextMenu.addAction("Kill");
            QAction *action4;
            if(!processes[row]->is_suspended())
                action4 =contextMenu.addAction("Suspend");
            else
                action4 =contextMenu.addAction("Resume");


            QAction *selectedAction = contextMenu.exec(ui->process_view->viewport()->mapToGlobal(pos));

            if (selectedAction == action1){
                Affinity* aff = new Affinity;
                aff->get_pro(processes[row]);
                aff->show();
            }
            else if (selectedAction == action2)
                context_menu_priority(pos,row);
            else if (selectedAction == action3){
                for (int columnIndex = 0; columnIndex < ui->process_view->columnCount(); ++columnIndex) {
                    ui->process_view->item(row, columnIndex)->setBackground(Qt::red);
                    if (columnIndex == 3) {
                        ui->process_view->item(row, columnIndex)->setText("Terminated");
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));

                processes[row]->kill();
            }
            else if (selectedAction == action4){
                if(!processes[row]->is_suspended()){
                    for (int columnIndex = 0; columnIndex < ui->process_view->columnCount(); ++columnIndex) {
                        ui->process_view->item(row, columnIndex)->setBackground(Qt::gray);
                    }

                    processes[row]->suspend();
                }
                else{
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    for (int columnIndex = 0; columnIndex < ui->process_view->columnCount(); ++columnIndex) {
                        ui->process_view->item(row, columnIndex)->setBackground(Qt::white);
                    }
                    ui->process_view->item(row, 3)->setBackground(Qt::green);

                }
            }
        }
    }
}


void MainWindow::context_menu_priority(const QPoint &pos, int row)
{
    QMenu contextMenu(this);

    QString priority[] = {
        "High",
        "Above Normal",
        "Normal",
        "Below Normal",
        "Idle",
        "Realtime"
    };

    bool pr_check[6] = {0};

    switch (processes[row]->get_priority_int())
    {
        case HIGH_PRIORITY_CLASS:
            pr_check[0] = 1;
            break;
        case ABOVE_NORMAL_PRIORITY_CLASS:
            pr_check[1] = 1;
            break;
        case NORMAL_PRIORITY_CLASS:
            pr_check[2] = 1;
            break;
        case BELOW_NORMAL_PRIORITY_CLASS:
            pr_check[3] = 1;
            break;
        case IDLE_PRIORITY_CLASS:
            pr_check[4] = 1;
            break;
        case REALTIME_PRIORITY_CLASS:
            pr_check[5] = 1;
            break;
    }

    QAction *actions[6];

    for (int i = 0; i < 6; ++i) {
            actions[i] = contextMenu.addAction(priority[i]);
            actions[i]->setCheckable(true);
            actions[i]->setChecked(pr_check[i]);
    }

    QAction *selectedAction = contextMenu.exec(ui->process_view->viewport()->mapToGlobal(pos));

    if (selectedAction == actions[0])
        processes[row]->set_priority(HIGH_PRIORITY_CLASS);
    else if (selectedAction == actions[1])
        processes[row]->set_priority(ABOVE_NORMAL_PRIORITY_CLASS);
    else if (selectedAction == actions[2])
        processes[row]->set_priority(NORMAL_PRIORITY_CLASS);
    else if (selectedAction == actions[3])
        processes[row]->set_priority(BELOW_NORMAL_PRIORITY_CLASS);
    else if (selectedAction == actions[4])
        processes[row]->set_priority(IDLE_PRIORITY_CLASS);
    else if (selectedAction == actions[5])
        processes[row]->set_priority(REALTIME_PRIORITY_CLASS);
}


