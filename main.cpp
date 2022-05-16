#if __APPLE__
#include "Control.h"
#include <iostream>
#include <unistd.h>

#elif _WIN32
#include "WIN_Control.h"
#include <iostream>
#include <stdio.h>
#include <direct.h>
#endif

using namespace std;
int main()
{
    #ifdef __APPLE__
    cout << "\nApple; ";
    char pass [255];
    getcwd(pass, 255);
    cout << "Pass: " << pass << ".\n";
    Control(0);

    #elif _WIN32
    cout << "\nWindows; ";
    char pass [255];
    _getcwd(pass, 255);
    cout << "Pass: " << pass << ".\n";
    WIN_Control(0);
    #endif

    return 0;
}