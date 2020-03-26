#include "stdafx.h"
#include "application.h"
#include "device.h"

HWND Application::m_hwnd = nullptr;

int Application::Run(Device* pDevice, HINSTANCE hInstance, int nCmdShow)
{	
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"DX12";
	RegisterClassEx(&windowClass);

	RECT windowRect = { 0, 0, static_cast<LONG>(pDevice->GetWidth()), static_cast<LONG>(pDevice->GetHeight()) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindow(
		windowClass.lpszClassName,
		pDevice->GetWindowTitle().c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,        // We have no parent window.
		nullptr,        // We aren't using menus.
		hInstance,
		pDevice);

	//init device
	pDevice->OnInit();

	ShowWindow(m_hwnd, nCmdShow);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	pDevice->OnDestroy();

	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Device* pDevice = reinterpret_cast<Device*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLong(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
	}
	return 0;
	case WM_KEYDOWN:
		if (pDevice)
		{
			pDevice->OnKeyDown(static_cast<UINT8>(wParam));
		}
		return 0;
	case WM_KEYUP:
		if (pDevice)
		{
			pDevice->OnKeyUp(static_cast<UINT8>(wParam));
		}
		return 0;
	case WM_PAINT:
		if (pDevice)
		{
			pDevice->OnUpdate();
			pDevice->OnRender();
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}