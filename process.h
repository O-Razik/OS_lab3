#ifndef PROCESS_H
#define PROCESS_H

#include <Windows.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <QString>
#include <psapi.h>
#include <tlhelp32.h>
#include <QTime>

class Process
{
public:
    Process(QString filepath, double x1, double x2, double step);
    Process(QString filepath);
    Process(QString filepath, int n, int m);
    ~Process();

    void suspend();
    void resume();
    void kill();
    void set_affinity(const bool arr[12]);
    void set_priority(DWORD priorityClass);

    int get_id();
    QString get_path();
    QString get_name();
    QString get_state();
    QString get_priority();
    int get_priority_int();
    QString get_affinity();
    QString get_cpu_time();

    QString get_virtual_memory_size();
    QString get_max_working_set_size();
    QString get_handle_count();
    QString get_thread_count();
    QString get_page_faults();
    QString get_user_object_count();

    bool is_suspended();


private:
    STARTUPINFO stInfo;
    PROCESS_INFORMATION pcInfo;
    PROCESS_MEMORY_COUNTERS pmc;
};

#endif // PROCESS_H
