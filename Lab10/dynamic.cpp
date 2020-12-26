#include <dlfcn.h>
#include <iostream>

using namespace std;

int main() {
    void *MyLib;
    typedef int(*func)();
    func MyApp;
    MyLib = dlopen("./lib.so", RTLD_LAZY | RTLD_GLOBAL);
    if(MyLib == 0)
        return -1;
    else
        cout << "lib.so is loaded!\n";
    MyApp = (func)dlsym(MyLib, "main_in_lib");
    if (!MyApp) {
        cout << "Function not found" << endl;
        return -1;
    }
    (*MyApp)();
    cout << "MyApp function is finished!\n";
    dlclose(MyLib);
    cout << "lib.so is closed!\n";
    return 0;
}