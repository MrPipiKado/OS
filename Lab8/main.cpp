#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cmath>
using namespace std;

typedef struct{
    double a;
    double b;
    double step;
} DATA;

typedef struct {
    void (*func)(void* data);
    union {
        DATA data;
        int amountOfIterations;
    } param;
} PARAMS;

double functionToTabulate(double x);
void loopedOutput(void* data);
void tabulation(void* data);
void* myThread(void* data);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t suspendMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t suspendCond = PTHREAD_COND_INITIALIZER;
sem_t semaphore;
pthread_rwlock_t rwLock = PTHREAD_RWLOCK_INITIALIZER;
const double EPS = 0.001;
bool resourseInUse = false;
int readyToGo = 1;

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);
    sem_init(&semaphore, 0, 1);
    pthread_rwlock_init(&rwLock, nullptr);

    int algorithm, amountOfThreads, choice;

    cout << "Choose the algorithm (1 - loop, 2 - tabulation): ";
    cin >> algorithm;

    cout << "Enter the amount of threads: ";
    cin >> amountOfThreads;

    auto threads = new pthread_t[amountOfThreads];
    auto params = new PARAMS [amountOfThreads];

    if (algorithm == 1){
        for(int i = 0; i < amountOfThreads; i++){
            params[i].func = loopedOutput;
        }
        int amountOfIterations;
        cout << "Enter the amount of iterations: ";
        cin >> amountOfIterations;
        amountOfIterations = amountOfIterations/amountOfThreads;
        for(int i = 0; i < amountOfThreads; i++){
            params[i].param.amountOfIterations = amountOfIterations;
        }
    } else {
        for(int i = 0; i < amountOfThreads; i++){
            params[i].func = tabulation;
        }
        double a, b, step;
        cout << "Enter the edges of tabulation: ";
        cin >> a >> b;
        cout << "Enter the step of tabulation: ";
        cin >> step;
        double h = (b-a) / amountOfThreads;
        DATA data;
        for(int i = 0; i < amountOfThreads; i++){
            data.a = a;
            data.b = a + h;
            data.step = step;
            a += h;
            params[i].param.data = data;
        }
    }

    for(int i = 0; i < amountOfThreads; i++){
            cout << "Thread " << i << " is terminated" << endl;
            readyToGo = 0;
            pthread_attr_t tattr;
            sched_param param;
            pthread_attr_init (&tattr);
            pthread_attr_getschedparam (&tattr, &param);
            pthread_attr_setschedparam (&tattr, &param);
            pthread_create (&threads[i], &tattr, myThread, &params[i]);
            pthread_mutex_lock(&suspendMutex);
            readyToGo = 1;
            pthread_mutex_unlock(&suspendMutex);
            pthread_cond_signal(&suspendCond);
        pthread_create(&threads[i], nullptr, myThread, &params[i]);
        pthread_join(threads[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    sem_destroy(&semaphore);
    pthread_rwlock_destroy(&rwLock);
    return 0;
}

void* myThread(void* data){
    pthread_mutex_lock(&suspendMutex);
    while (readyToGo == 0) {
        pthread_cond_wait(&suspendCond, &suspendMutex);
    }
    pthread_mutex_unlock(&suspendMutex);


    auto params = (PARAMS*) data;
    void* args;
    if(params->func == loopedOutput){
        args = &(params->param.amountOfIterations);
    } else {
        args = &(params->param.data);
    }
    cout << endl;
            params->func(args);
    return 0;
}

void loopedOutput(void* data){
    int* amountOfIterations = (int*) data;
    string name = "Markiian";
    string surname = "Andreiko";
    long id = 123456789;
    for(int i = 0; i < *amountOfIterations; i++){
        pthread_mutex_lock(&mutex);
        cout << "Thread " << pthread_self() << ": " << name << " " << surname << " " << id << endl;
        pthread_mutex_unlock(&mutex);
    }
}

void tabulation(void* data) {
    DATA *params = (DATA *) data;
    double x = params->a;
    while (x <= params->b) {
        pthread_rwlock_wrlock(&rwLock);
        cout << "Thread " << pthread_self() << ": x  = " << x << "\ty = " << functionToTabulate(x) << endl;
        pthread_rwlock_unlock(&rwLock);
        x += params->step;
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