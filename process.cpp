#include "process.h"
#include "qdebug.h"

Process::Process(QString filepath, double x1, double x2, double step)
{
    std::wstring cmd = filepath.toStdWString();
    cmd += L" " + std::to_wstring(x1);
    cmd += L" " + std::to_wstring(x2);
    cmd += L" " + std::to_wstring(step);

    ZeroMemory(&stInfo, sizeof(stInfo));
    ZeroMemory(&pcInfo, sizeof(pcInfo));

    CreateProcess(NULL,
                  (LPWSTR)cmd.c_str(),
                   NULL,
                   NULL,
                   FALSE,
                   CREATE_NEW_CONSOLE,
                   NULL,
                   NULL,
                   &stInfo,
                   &pcInfo);
}

Process::Process(QString filepath, int n, int m)
{
    std::wstring cmd = filepath.toStdWString();
    cmd += L" " + std::to_wstring(n);
    cmd += L" " + std::to_wstring(m);

    ZeroMemory(&stInfo, sizeof(stInfo));
    ZeroMemory(&pcInfo, sizeof(pcInfo));

    CreateProcess(NULL,
                  (LPWSTR)cmd.c_str(),
                  NULL,
                  NULL,
                  FALSE,
                  CREATE_NEW_CONSOLE,
                  NULL,
                  NULL,
                  &stInfo,
                  &pcInfo);
}

Process::Process(QString filepath)
{
    std::wstring cmd = filepath.toStdWString();

    ZeroMemory(&stInfo, sizeof(stInfo));
    ZeroMemory(&pcInfo, sizeof(pcInfo));

    CreateProcess(NULL,
                  (LPWSTR)cmd.c_str(),
                  NULL,
                  NULL,
                  FALSE,
                  CREATE_NEW_CONSOLE,
                  NULL,
                  NULL,
                  &stInfo,
                  &pcInfo);
}

Process::~Process(){
    WaitForSingleObject(pcInfo.hProcess, INFINITE);

    CloseHandle(pcInfo.hProcess);
    CloseHandle(pcInfo.hThread);
}

void Process::suspend(){
    SuspendThread(pcInfo.hThread);
}

void Process::resume(){
    ResumeThread(pcInfo.hThread);
}

void Process::kill(){
    TerminateProcess(pcInfo.hProcess, 0);
}

void Process::set_affinity(const bool arr[12]) {
    DWORD_PTR affinityMask = 0;

    for (int i = 0; i < 12; ++i) {
        if (arr[i]) {
            affinityMask |= (1ULL << i);
        }
    }

    if (SetProcessAffinityMask(pcInfo.hProcess, affinityMask) == 0) {
        DWORD error = GetLastError();
        qDebug() << "Error code:" << error;
    }
}

void Process::set_priority(DWORD priorityClass) {

    if (SetPriorityClass(pcInfo.hProcess, priorityClass) == 0) {
        DWORD error = GetLastError();
        qDebug() << "Error code:" << error;
    }
}

int Process::get_id()
{
    return GetProcessId(pcInfo.hProcess);
}

QString Process::get_name()
{
    WCHAR processName[MAX_PATH];
    DWORD bufferSize = sizeof(processName) / sizeof(processName[0]);

    if (QueryFullProcessImageName(pcInfo.hProcess, 0, processName, &bufferSize))
    {
        wchar_t* fileName = wcsrchr(processName, L'\\');
        if (fileName)
        {
            ++fileName;
            return QString::fromWCharArray(fileName);
        }
    }

    return QString("N/A");
}


QString Process::get_path()
{
    WCHAR processName[MAX_PATH];
    DWORD bufferSize = sizeof(processName) / sizeof(processName[0]);

    if (QueryFullProcessImageName(pcInfo.hProcess, 0, processName, &bufferSize))
    {
        return QString::fromWCharArray(processName);
    }
    else
    {
        return QString("N/A");
    }
}

QString Process::get_state()
{
    DWORD exitCode;
    if (GetExitCodeProcess(pcInfo.hProcess, &exitCode))
    {
        if (exitCode == STILL_ACTIVE)
        {
            if (!is_suspended())
                return QString("Running");
            else
                return QString("Suspended");
        }
        else
            return QString("Exited");
    }
    return QString("N/A");
}

bool Process::is_suspended()
{
    DWORD suspendCount = SuspendThread(pcInfo.hThread);
    ResumeThread(pcInfo.hThread);

    return suspendCount > 0;
}

QString Process::get_priority()
{
    DWORD priority = GetPriorityClass(pcInfo.hProcess);
    switch (priority)
    {
    case HIGH_PRIORITY_CLASS:
        return QString("High");
    case ABOVE_NORMAL_PRIORITY_CLASS:
        return QString("Above Normal");
    case NORMAL_PRIORITY_CLASS:
        return QString("Normal");
    case BELOW_NORMAL_PRIORITY_CLASS:
        return QString("Below Normal");
    case IDLE_PRIORITY_CLASS:
        return QString("Idle");
    case REALTIME_PRIORITY_CLASS:
        return QString("Realtime");
    default:
        return QString("Unknown");
    }
}

int Process::get_priority_int()
{
    return GetPriorityClass(pcInfo.hProcess);
}

QString Process::get_affinity()
{
    DWORD_PTR processAffinity, systemAffinity;
    if (GetProcessAffinityMask(pcInfo.hProcess, &processAffinity, &systemAffinity))
    {
        QString affinityStr;

        for (int bit = 0; bit < sizeof(DWORD_PTR) * 8; ++bit)
        {
            if ((processAffinity & (1ULL << bit)) != 0)
            {
                if (!affinityStr.isEmpty())
                {
                    affinityStr += ", ";
                }
                affinityStr += QString::number(bit);
            }
        }

        return affinityStr.isEmpty() ? QString("N/A") : affinityStr;
    }
    else
    {
        return QString("N/A");
    }
}


QString Process::get_cpu_time()
{
    FILETIME createTime, exitTime, kernelTime, userTime;

    if (GetProcessTimes(pcInfo.hProcess, &createTime, &exitTime, &kernelTime, &userTime))
    {
        ULONGLONG kernelTimeMs = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
        ULONGLONG userTimeMs = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;
        QTime kernelTimeQTime = QTime::fromMSecsSinceStartOfDay(((kernelTimeMs+userTimeMs) / 10000));
        return kernelTimeQTime.toString("HH:mm:ss.zzz");
    }
    else
    {
        return QString("N/A");
    }
}

QString Process::get_virtual_memory_size()
{
    SIZE_T virtualMemorySize;
    if (GetProcessMemoryInfo(pcInfo.hProcess, &pmc, sizeof(pmc)))
    {
        virtualMemorySize = pmc.PagefileUsage;
        return QString::number(virtualMemorySize / 1024) + " KB";
    }
    else
    {
        return QString("N/A");
    }
}

QString Process::get_max_working_set_size()
{
    SIZE_T minWorkingSetSize = 0;
    SIZE_T maxWorkingSetSize = 0;

    if (GetProcessWorkingSetSize(pcInfo.hProcess, &minWorkingSetSize, &maxWorkingSetSize))
    {
        ULONGLONG sizeInMB = static_cast<ULONGLONG>(maxWorkingSetSize)/ 1024;
        return QString::number(sizeInMB) + " KB";
    }
    else
    {
        DWORD error = GetLastError();
        qDebug() << "Error code:" << error;
        return QString("N/A");
    }
}


QString Process::get_handle_count()
{
    DWORD handleCount;
    if (GetProcessHandleCount(pcInfo.hProcess, &handleCount))
    {
        return QString::number(handleCount);
    }
    else
    {
        return QString("N/A");
    }
}

QString Process::get_thread_count()
{
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
    {
        return QString("N/A");
    }

    DWORD processId = GetProcessId(pcInfo.hProcess);
    DWORD threadCount = 0;

    THREADENTRY32 te32;
    te32.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(hThreadSnap, &te32))
    {
        do
        {
            if (te32.th32OwnerProcessID == processId)
            {
                threadCount++;
            }
        } while (Thread32Next(hThreadSnap, &te32));
    }

    CloseHandle(hThreadSnap);

    return QString::number(threadCount);
}


QString Process::get_page_faults()
{
    SIZE_T pageFaultCount;
    if (GetProcessMemoryInfo(pcInfo.hProcess, &pmc, sizeof(pmc)))
    {
        pageFaultCount = pmc.PageFaultCount;
        return QString::number(pageFaultCount);
    }
    else
    {
        return QString("N/A");
    }
}

QString Process::get_user_object_count()
{
    DWORD userObjectCount = GetGuiResources(pcInfo.hProcess, GR_USEROBJECTS);

    if (userObjectCount != 0xFFFFFFFF)
    {
        return QString::number(userObjectCount);
    }
    else
    {
        return QString("N/A");
    }
}

