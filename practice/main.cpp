#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
int main(int argc, char* argv[])
{
    _PROCESS_INFORMATION PID[8];
    bool ps[8]={false,false,false,false,false,false,false,false};
    long long fac[8];
    int CountProc;
    int lines = 1000;
    int lines_per_process;

    std::cout << "\nEnter amount of process: ";
    std::cin >> CountProc;

    for(int i=0;i<CountProc;++i)
        std::cin>>fac[i];

    for(int i=0;i<CountProc;++i)
    {
                lines = lines -lines_per_process;
                STARTUPINFO si;
                PROCESS_INFORMATION pinfo;
                ZeroMemory(&si, sizeof(STARTUPINFO));
                ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));

                std::string cons = "D:\\Clion_projects\\practice\\cmake-build-debug\\kaka.exe " +
                std::to_string(fac[i]);
                CreateProcess("D:\\Clion_projects\\practice\\cmake-build-debug\\kaka.exe",
                              (LPSTR)cons.c_str() ,
                              nullptr,
                              nullptr,
                              FALSE,
                              CREATE_NEW_CONSOLE | CREATE_SUSPENDED,
                              nullptr,
                              nullptr,
                              &si,
                              &pinfo);
                PID[i] = pinfo;
                ps[i] = true;
    }
    int status = 0;
    while(1){
        int choice;
        std::cout<<"\n\nRun All [1] | Change Priority [2] | KILL [3]\n";
        std::cin >> choice;
        switch(choice){
            case 1:
            {
                int handleCounter = 0;
                HANDLE threadHandles[8];
                const auto begin = std::chrono::high_resolution_clock::now();
                for(int i = 0; i < CountProc; ++i ){
                    if(ps[i])
                    {
                        threadHandles[handleCounter++] = PID[i].hThread;
                        ResumeThread(PID[i].hThread);
                    }
                }

                WaitForMultipleObjects(handleCounter, threadHandles, TRUE, INFINITE);

                for(int i = 0; i < CountProc; ++i ){
                    if(ps[i])
                    {
                        CloseHandle(PID[i].hProcess);
                        CloseHandle(PID[i].hThread);
                    }
                }

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
                std::cout << "\nEnter new prority:\n 0 - Idle | 1 - Below normal | 2 - Normal | 3 - Above normal | 4 - High | 5 - Real time\n";
                std::cin >> pr;
                switch(pr) {
                    case 0: {
                        SetPriorityClass(PID[num].hProcess, IDLE_PRIORITY_CLASS);
                        std::cout<<"Idle";
                        break;
                    }
                    case 1: {
                        SetPriorityClass(PID[num].hProcess, BELOW_NORMAL_PRIORITY_CLASS);
                        std::cout<<"Below normal";
                        break;
                    }
                    case 2: {
                        SetPriorityClass(PID[num].hProcess, NORMAL_PRIORITY_CLASS);
                        std::cout<<"Normal";
                        break;
                    }
                    case 3: {
                        SetPriorityClass(PID[num].hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
                        std::cout<<"Above normal";
                        break;
                    }
                    case 4: {
                        SetPriorityClass(PID[num].hProcess, HIGH_PRIORITY_CLASS);
                        std::cout<<"High";
                        break;
                    }
                    case 5: {
                        SetPriorityClass(PID[num].hProcess, REALTIME_PRIORITY_CLASS);
                        std::cout<<"Real time";
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                int num;
                std::cout << "\nEnter process number to kill: ";
                std::cin >> num;
                num--;
                TerminateProcess(PID[num].hProcess,0);

                ps[num] = false;
                std::cout << "\nKILLED)";
                break;
            }
        }
    }
    return 0;
}