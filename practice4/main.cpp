#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>
using namespace std;

vector<int> students, campus, car;

typedef struct
{
    double a;
    double b;
    double step;
} DATA;

typedef struct
{
    void (*func)(void* data);
    int choice;
    union
    {
        DATA data;
        int amountOfIterations;
    } param;
} PARAMS;

double functionToTabulate(double x);
void loopedOutput(void* data);
void tabulation(void* data);
unsigned int __stdcall myThread(void* data);
int getNewPriority();

CRITICAL_SECTION criticalSection;
HANDLE mutex;
HANDLE semaphore;
long resourceInUse = 0;
const double EPS = 0.001;

int main(int argc, char* argv[])
{
    for(int i =0; i<100; ++i)
        students.push_back(i);
    mutex = CreateMutexA(nullptr, FALSE, "mutex");
    semaphore = CreateSemaphoreA(nullptr, 1, 1, "semaphore");
    InitializeCriticalSection(&criticalSection);

    int algorithm, amountOfThreads, choice;

    cout << "Enter the amount of threads: ";
    cin >> amountOfThreads;

    cout << "Choose the way to synchronize threads: "
            "\n1 - interlocked functions"
            "\n2 - mutex"
            "\n3 - semaphore"
            "\n4 - critical section\n";
    cin >> choice;

    auto threads = new HANDLE[amountOfThreads];
    auto params = new PARAMS [amountOfThreads];

    for(int i = 0; i < amountOfThreads; i++)
    {
        params[i].choice = choice;
    }

        for(int i = 0; i < amountOfThreads; i++)
        {
            params[i].func = loopedOutput;
        }
        int amountOfIterations;
        cout << "Enter the amount of iterations: ";
        cin >> amountOfIterations;
        amountOfIterations = amountOfIterations/amountOfThreads;
        for(int i = 0; i < amountOfThreads; i++)
        {
            params[i].param.amountOfIterations = amountOfIterations;
        }

        while(!students.empty()) {
            for (int i = 0; i < amountOfThreads; i++) {
                threads[i] = (HANDLE) _beginthreadex(nullptr, 0, myThread, &params[i], 0, nullptr);
            }

            WaitForMultipleObjects(amountOfThreads, threads, TRUE, INFINITE);
        }
    for (int i = 0; i < amountOfThreads; i++)
    {
        CloseHandle(threads[i]);
    }

    DeleteCriticalSection(&criticalSection);
    CloseHandle(mutex);
    CloseHandle(semaphore);

    return 0;
}

unsigned int __stdcall myThread(void* data)
{
    auto params = (PARAMS*) data;
    void* args;
    if(params->func == loopedOutput)
    {
        args = &(params->param.amountOfIterations);
    }
    else
    {
        args = &(params->param.data);
    }
    cout << endl;
    switch (params->choice)
    {
        case 1:
        {
            while (InterlockedExchange(&resourceInUse, TRUE));
            params->func(args);
            InterlockedExchange(&resourceInUse, 0);
            break;
        }
        case 2:
        {
            WaitForSingleObject(mutex, INFINITE);
            params->func(args);
            ReleaseMutex(mutex);
            break;
        }
        case 3:
        {
            WaitForSingleObject(semaphore, INFINITE);
            params->func(args);
            ReleaseSemaphore(semaphore, 1, nullptr);
            break;
        }
        case 4:
        {
            EnterCriticalSection(&criticalSection);
            params->func(args);
            LeaveCriticalSection(&criticalSection);
            break;
        }
    }
    return 0;
}

void loopedOutput(void* data)
{
    for(int i = 0; i<4; ++i)
    {
        if(!students.empty())
        {
            int t =*(students.end()-1);
            students.pop_back();
            campus.push_back(t);
            std::cout<<t<<" at campus"<<endl;
        }
    }
}

void tabulation(void* data)
{
    DATA *params = (DATA *) data;
    double x = params->a;
    while (x <= params->b)
    {
        cout << "Thread " << GetCurrentThreadId() << ": x  = " << x << "\ty = " << functionToTabulate(x) << endl;
        x += params->step;
    }
}

double functionToTabulate(double x)
{
    int n=0, k=0;
    double  si=1, s=0;
    while (std::fabs(si) > 0.0001)
    {
        k+=2;
        si *= (-1.0 * x*x)/(k*(k-1));
        s += si;
        ++n;

    }
    return s;
}