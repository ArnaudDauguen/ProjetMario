#pragma once
#include <windows.h>

class Messager
{
public:
	static void ShowMessageAndExit(const char* message)
	{
		MessageBoxA(nullptr, message, "Error", MB_OK);
		exit(5);
	}
private:
	Messager();
};

