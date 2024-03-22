#include "Owindow.h"
#include <Windows.h>
#include <assert.h>

Owindow::Owindow()
{
	WNDCLASSEX wc = { };
	wc.lpszClassName = L"SRE~";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = DefWindowProc;

	assert(RegisterClassEx(&wc));

	RECT re = { 0,0,1024,768 };
	AdjustWindowRect(&re,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,false);

	handle = CreateWindowEx(NULL, L"SRE~", L"StrayRenderEngine~",
		WS_OVERLAPPED | WS_CAPTION |  WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,re.right-re.left,
		re.bottom-re.top, NULL,NULL,NULL,NULL);

	assert(handle);

	ShowWindow((HWND)handle,SW_SHOW);
	UpdateWindow((HWND)handle);
}

Owindow::~Owindow()
{
	DestroyWindow((HWND)handle);
}
