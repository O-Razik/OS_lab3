#include "save_result.h"
#include "ui_save_result.h"

#include <QFileDialog>
#include <QDir>
#include <codecvt>
#include <fstream>

save_result::save_result(MainWindow *mainwindow) :
    QDockWidget(mainwindow),
    ui(new Ui::save_result),
    mainwindow(mainwindow)
{
    ui->setupUi(this);

    QFile file("C:\\Users\\razik\\source\\repos\\Qt\\os_lab3\\archive\\archive.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Could not open file:" << file.errorString();
    }
    else {
        std::ifstream inFile(file.fileName().toStdString());

        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                QString filePath = QString::fromStdString(line).trimmed();

                if (!filePath.isEmpty()) {
                    ui->old_names->addItem(QDir::toNativeSeparators(filePath));
                }
            }

            inFile.close();
        } else {
            qDebug() << "Error opening file:" << file.errorString();
        }

        file.close();
    }
}

save_result::~save_result()
{
    delete ui;
}

void save_result::on_save_clicked()
{
    HANDLE hFile;
    std::string filename = "";

    if(ui->tabWidget->currentWidget() == ui->old_files && ui->old_names->count() > 0){
        filename = ui->old_names->currentText().toStdString();
        hFile = CreateFileA(
            filename.c_str(),
            GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_WRITE | FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
    }
    else if(ui->tabWidget->currentWidget() == ui->new_file){
        QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Select Folder", QDir::homePath());
        if (folderPath.isEmpty()) {
            return;
        }

        QDir::toNativeSeparators(folderPath);

        filename = (QDir::toNativeSeparators(folderPath)+"\\"+ui->new_file_name->text()+".txt").toStdString();
        hFile = CreateFileA(
            filename.c_str(),
            GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_WRITE | FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        QTableWidget* table = mainwindow->get_table();
        for (int i = 0; i < table->rowCount(); ++i) {
            QString row = "| ";
            for (int j = 0; j < table->columnCount(); ++j) {
                row += table->item(i,j)->text() + " | ";
            }

            DWORD bytesWritten;
            if (WriteFile(hFile, row.toStdString().c_str(), lstrlenA(row.toStdString().c_str()), &bytesWritten, NULL) == FALSE) {
                DWORD error = GetLastError();
                printf("Error writing to file. Error code: %lu\n", error);
            }
        }

        std::fstream arc("C:\\Users\\razik\\source\\repos\\Qt\\os_lab3\\archive\\archive.txt", std::ios::app);
        if (arc.is_open()) {
            arc << filename << '\n';
            arc.close();
        }
    }

    DWORD attributes = 0;

    if (only_read) {
        attributes |= FILE_ATTRIBUTE_READONLY;
    }

    if (hidden) {
        attributes |= FILE_ATTRIBUTE_HIDDEN;
    }

    if (archive) {
        attributes |= FILE_ATTRIBUTE_ARCHIVE;
    }


    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideFilename = converter.from_bytes(filename);
    if (!SetFileAttributes(wideFilename.c_str(), attributes)) {
        DWORD error = GetLastError();
        printf("Error setting file attributes. Error code: %lu\n", error);
    }
}


void save_result::on_only_read_clicked()
{
    only_read = !only_read;
}


void save_result::on_hidden_clicked()
{
    hidden = !hidden;
}


void save_result::on_normal_clicked()
{
    if (!normal)
    {
        ui->only_read->setDisabled(true);
        if(only_read) ui->only_read->setChecked(false);
        ui->hidden->setDisabled(true);
        if(hidden) ui->hidden->setChecked(false);
        ui->archive->setDisabled(true);
        if(archive) ui->archive->setChecked(false);
        ui->compresed->setDisabled(true);
        if(compresed) ui->compresed->setChecked(false);
        ui->directory->setDisabled(true);
        if(directory) ui->directory->setChecked(false);
    }
    else if (normal)
    {
        ui->only_read->setDisabled(false);
        ui->hidden->setDisabled(false);
        ui->archive->setDisabled(false);
        ui->directory->setDisabled(false);
        ui->compresed->setDisabled(false);
    }

    normal = !normal;
}


void save_result::on_archive_clicked()
{
    archive = !archive;
}


void save_result::on_directory_clicked()
{
    directory = !directory;
}


void save_result::on_compresed_clicked()
{
    compresed = !compresed;
}

