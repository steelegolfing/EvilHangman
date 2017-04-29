#include <iostream>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

int main()
{
    PlaySound(TEXT("rip.wav"), NULL, SND_SYNC);
    cout << "Hello world!" << endl;
    return 0;
}
