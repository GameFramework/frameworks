#include "main.h"
#include "SimulatorWin.h"
#include <shellapi.h>

int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	auto simulator = SimulatorWin::getInstance();
	int res = simulator->run();
	FreeConsole();
	return res;
}
