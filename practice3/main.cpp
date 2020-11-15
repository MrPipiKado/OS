#include <iostream>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

typedef struct{
    double **dest;
    double **source;
    int start;
    int end;
} DATA;

double functionToTabulate(double x);
void loopedOutput(int amountOfIterations);
void tabulation(double a, double b, double step);
void printThreadPriorityInfo();

void* myThread(void* data) {
    DATA* args = (DATA*) data;
    for(int i = args->start;i<=args->end; ++i)
    {
        for(int j = 0; j<10; ++j)
        {
            args->dest[i][j]+=args->source[i][j];
        }
    }
    return 0;
}

void fill(double **A)
{
    for(int i= 0; i<10;++i)
        for(int j = 0; j<10;++j)
            A[i][j]=rand() % 10 + (rand() % 10) / 10.;
}
void print(double **A)
{
    for(int i= 0; i<10;++i)
    {
        for(int j = 0; j<10;++j)
        {
            cout.precision(3);
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(int argc, char* argv[]) {
    auto **A = new double*[10];
    for(int i = 0; i<10;++i)
        A[i] = new double [10];
    auto **B = new double*[10];
    for(int i = 0; i<10;++i)
        B[i] = new double [10];
    auto **C = new double*[10];
    for(int i = 0; i<10;++i)
        C[i] = new double [10];
    fill(A);fill(B);fill(C);

    print(A);cout<<endl<<endl;
    print(B);cout<<endl<<endl;
    print(C);cout<<endl<<endl;
    auto *threads = new pthread_t[4];
    auto *datas = new DATA[4];
    while(1){
        int choice;
        std::cout<<"\n\nRun All [1] | Change Priority [2]\n";
        std::cin >> choice;
        switch(choice){
            case 1:
            {
                DATA data;
                auto start = std::chrono::high_resolution_clock::now();
                datas[0].start = 0;datas[0].end=4;datas[0].source=A;datas[0].dest=C;
                pthread_create(&threads[0], NULL, &myThread, &datas[0]);
                datas[1].start = 5;datas[1].end=9;datas[1].source=A;datas[1].dest=C;
                pthread_create(&threads[1], NULL, myThread, &datas[1]);
                datas[2].start = 0;datas[2].end=4;datas[2].source=B;datas[2].dest=C;
                pthread_create(&threads[2], NULL, myThread, &datas[2]);
                datas[3].start = 5;datas[3].end=9;datas[3].source=B;datas[3].dest=C;
                pthread_create(&threads[3], NULL, myThread, &datas[3]);


                for(int i = 0; i < 4; i++){
                    pthread_join(threads[i], nullptr);
                }
                auto end = std::chrono::high_resolution_clock::now();
                cout << "The execution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
                print(C);
                return 0;
            }
        }
    }
}
