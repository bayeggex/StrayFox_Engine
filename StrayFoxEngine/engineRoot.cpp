#include "engineRoot.h"
#include "Owindow.h"
#include "Windows.h"

engineRoot::engineRoot()
{
	display = new Owindow();
}

engineRoot::~engineRoot()
{
	delete display;
}

void engineRoot::Instantiate()
{
	MSG msg;
	while (isInstantiate)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
}

void engineRoot::Destroy()
{
	isInstantiate = false;
}
