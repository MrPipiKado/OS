#include <iostream>
#include <windows.h>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

typedef struct{
    int threadNum;
    int amountOfIterations;
    double a;
    double b;
    double step;
} DATA;

double functionToTabulate(double x);
void loopedOutput(int amountOfIterations);
void tabulation(double a, double b, double step);
unsigned int __stdcall myThread(void* data);
void printThreadPriorityInfo();

unsigned int __stdcall myThread(void* data) {
    DATA* args = (DATA*) data;
    cout << "---------\n"
    << "THREAD " << args->threadNum << endl
    << "---------" << endl << std::flush;
    loopedOutput(args->amountOfIterations);
    tabulation(args->a, args->b, args->step);
    cout << "Thread " << args->threadNum << " is ended" << endl << std::flush;
    return 0;
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    int amountOfIterations;
    double a, b, step;
    cout << "Enter the amount of iterations to run the loop: ";
    cin >> amountOfIterations;
    cout << "Enter the edges of tabulation: ";
    cin >> a >> b;
    cout << "Enter the step of tabulation: ";
    cin >> step;
    DATA data = {0, amountOfIterations, a, b, step};

    cout << "Enter amount of threads: ";
    int amountOfThreads;
    cin >> amountOfThreads;
    data.amountOfIterations = amountOfIterations/amountOfThreads;
    double h = (b-a) / amountOfThreads;
    auto *threads = new HANDLE[amountOfThreads];
    auto *datas = new DATA[amountOfThreads];
    while(1){
        int choice;
        std::cout<<"\n\nRun All [1] | Change Priority [2]\n";
        std::cin >> choice;
        switch(choice){
            case 1:
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < amountOfThreads; i++){
                    datas[i].threadNum = i;
                    datas[i].amountOfIterations = amountOfIterations/amountOfThreads;
                    datas[i].a = a;
                    datas[i].b = a+h;
                    datas[i].step = step;
                    a += h;
                    threads[i] = (HANDLE)_beginthreadex(nullptr, 0, myThread, &datas[i], CREATE_SUSPENDED, nullptr);
                }


                for(int i = 0; i < amountOfThreads; i++){
                    ResumeThread(threads[i]);
                }
                WaitForMultipleObjects(amountOfThreads, threads, TRUE, INFINITE);
                auto end = std::chrono::high_resolution_clock::now();
                cout << "The execution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
                for (int i = 0; i < amountOfThreads; i++){
                    CloseHandle(threads[i]);
                }
                return 0;
            }
            case 2:
            {
                int num;
                int pr = 2;
                std::cout << "\nEnter proces number: ";
                std::cin >> num;
                num--;
                printThreadPriorityInfo();
                cin >> pr;
                SetThreadPriority(threads[num], pr);

                break;
            }
        }
    }
}

void loopedOutput(int amountOfIterations){
    string name = "Markiian";
    string surname = "Andreiko";
    long id = 12345678;
    for(int i = 0; i < amountOfIterations; i++){
        cout.flush();
        cout.flush() << i << ") Name is: " << name << endl << "Surname is: " << surname << endl
             << "Student ticket id is: " << id << endl <<std::flush;
    }
}

void tabulation(double a, double b, double step){
    cout << "----------" << endl
    << "TABULATION " << endl
    << "----------" << endl
    << "a = " << a << endl
         << "b = " << b << endl
         << "step = " << step << endl << endl<<std::flush;
    double x = a;
    while(x <= b){
        cout.flush();
        cout << "x  = " << x << "\ty = " << functionToTabulate(x) << endl<<std::flush;
        cout.flush();
        x +=step;
    }
}

double functionToTabulate(double x){
    int n=0, k=0;
    double  si=1, s=0;
    while (fabs(si) > 0.0001)
    {
        k+=2;
        si *= (-1.0 * x*x)/(k*(k-1));
        s += si;
        ++n;

    }
    return s;
}

void printThreadPriorityInfo(){
    cout << "THREAD_PRIORITY_IDLE " << THREAD_PRIORITY_IDLE << endl;
    cout << "THREAD_PRIORITY_LOWEST " << THREAD_PRIORITY_LOWEST << endl;
    cout << "THREAD_PRIORITY_BELOW_NORMAL " << THREAD_PRIORITY_BELOW_NORMAL << endl;
    cout << "THREAD_PRIORITY_NORMAL " << THREAD_PRIORITY_NORMAL << endl;
    cout << "THREAD_PRIORITY_ABOVE_NORMAL " << THREAD_PRIORITY_ABOVE_NORMAL << endl;
    cout << "THREAD_PRIORITY_HIGHEST " << THREAD_PRIORITY_HIGHEST << endl;
}
