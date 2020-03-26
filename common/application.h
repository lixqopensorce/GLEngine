#pragma once
class Device;

class Application
{
public:
	static int Run(Device* pSample, HINSTANCE hInstance, int nCmdShow);
	static HWND GetHwnd() { return m_hwnd; }
protected:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	static HWND m_hwnd;
};
