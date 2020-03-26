#include "stdafx.h"
#include "application.h"
#include "device.h"


_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	Device device(1280, 720, L"DrawTriangle");
	return Application::Run(&device, hInstance, nCmdShow);
}