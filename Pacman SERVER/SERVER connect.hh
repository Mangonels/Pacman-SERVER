//TCP SERVER header file
//Note: You need to add "Ws2_32.lib" to the LINKER settings. Like so:
#pragma comment(lib, "Ws2_32.lib")

//STD console header files
#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>

//SOCKET header files
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#define SCK_VERSION2 0x0202