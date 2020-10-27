#include <iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<csignal>
#include<sys/resource.h>
#include <chrono>

//main start count
int main(int argc, char *argv[])
{
    pid_t PID[8];
    double total_time[8];
    int CountProc;
    int lines = 1000;
    int lines_per_process;

    std::cout << "\nEnter amount of process: ";
    std::cin >> CountProc;

    lines_per_process = lines/CountProc;
    for(int i=0;i<CountProc;++i)
    {

        PID[i]=fork();
        switch(PID[i])
        {
            case 0:
                lines = lines -lines_per_process;
                execlp("/home/user/Desktop/trash/untitled6/kaka",
                       "/home/user/Desktop/trash/untitled6/kaka",
                       "/home/user/Desktop/trash/untitled6/matrix.txt", std::to_string(lines).c_str(),
                        std::to_string(lines_per_process).c_str(), NULL);
                break;
            case -1:
                perror("Fork");
                break;
            default:
            {
                kill(PID[i],SIGSTOP);
                std::cout<<"\nChild PID= "<<PID[i] << " Created, suspended";
            }
        }

    }
    pid_t wpid;
    int status = 0;
    while(1){
        int choice;
        std::cout<<"\n\nRun All [1] | Change Priority [2] | Run Individually [3]\n";
        std::cin >> choice;
        switch(choice){
            case 1:
            {
                const auto begin = std::chrono::high_resolution_clock::now();
                for(int i = 0; i < CountProc; ++i ){
                    kill(PID[i],SIGCONT);
                    //sleep(1);
                }

                while ((wpid = wait(&status)) > 0);
                auto time = std::chrono::high_resolution_clock::now() - begin;
                std::cout << "\n\n\nDuration: " << std::chrono::duration<double, std::milli>(time).count() << "ms\n";
                return 0;
            }
            case 2:
            {
                int num;
                int pr = 2;
                std::cout << "\nEnter proces number: ";
                std::cin >> num;
                num--;
                std::cout << "\nEnter new prority: ";
                std::cin >> pr;
                setpriority(PRIO_PROCESS,PID[num],pr);

                std::cout<<"\nNew priority is " <<
                         getpriority(PRIO_PROCESS,PID[num]);
                break;
            }
        }
    }
    wait(NULL);
    return 0;
}


