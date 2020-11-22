#include <chrono>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <cmath>

using namespace std;
using namespace std::chrono;
static bool time_to_die = false;
static int ready_to_go = 1;
static pthread_mutex_t suspend_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t suspend_cond = PTHREAD_COND_INITIALIZER;

const double EPS = 0.001;

typedef struct{
    int threadNum;
    int amountOfIterations;
    double a;
    double b;
    double step;
} DATA;

void* myThread(void* param){
    pthread_mutex_unlock(&suspend_mutex);
    DATA* args = (DATA*) param;
    string name = "Marki";
    string surname = "Andreiko";
    long id = 123456789;
    for(int i = 0; i < args->amountOfIterations; i++){
        if(time_to_die)
            pthread_exit(nullptr);
        cout << "Thread" + to_string(args->threadNum) + ": " + to_string(i)
             + ") Name is: " + name + "\n" + "Surname is: " + surname +
             "Student ticket id is: " + to_string(id) + "\n";
    }
    double x = args->a;
    while(x <= args->b){
        if(time_to_die)
            pthread_exit(nullptr);
        int n=0, k=0;
        double  si=1, s=0;
        while (fabs(si) > 0.0001)
        {
            if(time_to_die)
                pthread_exit(nullptr);
            k+=2;
            si *= (-1.0 * x*x)/(k*(k-1));
            s += si;
            ++n;

        }
        cout.flush() << "x  = " + to_string(x) + "\ty = " + to_string(s) + "\n";
        x +=args->step;
    }
    cout << "Thread " << args->threadNum << " is ended" << endl;
    pthread_exit(nullptr);
}

int main()
{
    int amountOfIterations;
    double a, b, step;
    cout << "Enter the amount of iterations to run the loop: ";
    cin >> amountOfIterations;
    cout << "Enter the edges of tabulation: ";
    cin >> a >> b;
    cout << "Enter the step of tabulation: ";
    cin >> step;

    cout << "Enter amount of threads: ";
    int amountOfThreads;
    cin >> amountOfThreads;
    auto datas = new DATA[amountOfThreads];
    char ch;
    double h = (b-a) / amountOfThreads;
    auto threads = new pthread_t[amountOfThreads];
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amountOfThreads; i++){
        datas[i].threadNum = i;
        datas[i].amountOfIterations = amountOfIterations/amountOfThreads;
        datas[i].a = a;
        datas[i].b = a+h;
        datas[i].step = step;
        a += h;
        pthread_create (&threads[i], nullptr, myThread, &datas[i]);
    }

    cin>>ch;
    time_to_die = true;
    for(int i= 0; i<amountOfThreads; ++i)
        pthread_join(threads[i], nullptr);
    auto end = std::chrono::high_resolution_clock::now();
    cout << "The execution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    return EXIT_SUCCESS;
}

