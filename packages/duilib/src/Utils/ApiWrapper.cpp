#include "StdAfx.h"
#include "ApiWrapper.h"

namespace ui
{

bool GetDpiForSystemWrapper(UINT& dpi)
{
	typedef UINT (WINAPI* GetDpiForSystemPtr)(VOID);

	static GetDpiForSystemPtr get_dpi_for_system_func = reinterpret_cast<GetDpiForSystemPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "GetDpiForSystem"));

	if (get_dpi_for_system_func) {
		dpi = get_dpi_for_system_func();
		return true;
	}

	return false;
}

bool GetDpiForMonitorWrapper(HMONITOR hMonitor, MONITOR_DPI_TYPE dpiType, UINT *dpiX, UINT *dpiY)
{
	typedef HRESULT(WINAPI *GetDpiForMonitorPtr)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);

	static GetDpiForMonitorPtr get_dpi_for_monitor_func = reinterpret_cast<GetDpiForMonitorPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "GetDpiForMonitorInternal"));

	if (get_dpi_for_monitor_func) {
		if (get_dpi_for_monitor_func(hMonitor, dpiType, dpiX, dpiY) != S_OK) {
			return true;
		}
	}

	return false;
}

bool SetProcessDpiAwarenessWrapper(PROCESS_DPI_AWARENESS value)
{
	typedef HRESULT(WINAPI *SetProcessDpiAwarenessPtr)(PROCESS_DPI_AWARENESS);

	static SetProcessDpiAwarenessPtr set_process_dpi_awareness_func = reinterpret_cast<SetProcessDpiAwarenessPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "SetProcessDpiAwarenessInternal"));

	if (set_process_dpi_awareness_func) {
		HRESULT hr = set_process_dpi_awareness_func(value);
		if (S_OK == hr) {
			return true;
		}
		else if (hr == E_ACCESSDENIED) {
			//"Access denied error from SetProcessDpiAwareness. Function called twice, or manifest was used.";
		}
	}

	return false;
}

bool SetProcessDPIAwareWrapper()
{
	typedef BOOL(WINAPI *SetProcessDPIAwarePtr)(VOID);

	static SetProcessDPIAwarePtr set_process_dpi_aware_func = reinterpret_cast<SetProcessDPIAwarePtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "SetProcessDPIAware"));

	return set_process_dpi_aware_func && set_process_dpi_aware_func();
}


bool GetProcessDpiAwarenessWrapper(PROCESS_DPI_AWARENESS& awareness)
{
	typedef HRESULT(WINAPI *GetProcessDpiAwarenessPtr)(HANDLE, PROCESS_DPI_AWARENESS*);

	static GetProcessDpiAwarenessPtr get_process_dpi_awareness_func = reinterpret_cast<GetProcessDpiAwarenessPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "GetProcessDpiAwarenessInternal"));

	if (get_process_dpi_awareness_func) {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId());
		get_process_dpi_awareness_func(hProcess, &awareness);
		return true;
	}

	return false;
}

bool IsProcessDPIAwareWrapper(bool& bAware)
{
	typedef BOOL(WINAPI *IsProcessDPIAwarePtr)();

	static IsProcessDPIAwarePtr is_process_dpi_aware_func = reinterpret_cast<IsProcessDPIAwarePtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "IsProcessDPIAware"));

	if (is_process_dpi_aware_func) {
		bAware = TRUE == is_process_dpi_aware_func();
		return true;
	}

	return false;
}

bool RegisterTouchWindowWrapper(HWND hwnd, ULONG ulFlags)
{
	typedef BOOL(WINAPI *RegisterTouchWindowPtr)(HWND, ULONG);

	static RegisterTouchWindowPtr register_touch_window_func = reinterpret_cast<RegisterTouchWindowPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "RegisterTouchWindow"));

	if (register_touch_window_func) {
		return (TRUE == register_touch_window_func(hwnd, ulFlags));
	}

	return false;
}


bool UnregisterTouchWindowWrapper(HWND hwnd)
{
	typedef BOOL(WINAPI *UnregisterTouchWindowPtr)(HWND);

	static UnregisterTouchWindowPtr unregister_touch_window_func = reinterpret_cast<UnregisterTouchWindowPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "UnregisterTouchWindow"));

	if (unregister_touch_window_func) {
		return (TRUE == unregister_touch_window_func(hwnd));
	}

	return false;
}

bool GetTouchInputInfoWrapper(HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize)
{
	typedef BOOL(WINAPI *GetTouchInputInfoPtr)(HTOUCHINPUT, UINT, PTOUCHINPUT, int);

	static GetTouchInputInfoPtr get_touch_input_info_func = reinterpret_cast<GetTouchInputInfoPtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "GetTouchInputInfo"));
	
	if (get_touch_input_info_func) {
		return (TRUE == get_touch_input_info_func(hTouchInput, cInputs, pInputs, cbSize));
	}

	return false;
}


bool CloseTouchInputHandleWrapper(HTOUCHINPUT hTouchInput)
{
	typedef BOOL(WINAPI *CloseTouchInputHandlePtr)(HTOUCHINPUT);

	static CloseTouchInputHandlePtr close_touch_input_handle_func = reinterpret_cast<CloseTouchInputHandlePtr>(GetProcAddress(GetModuleHandleA("user32.dll"), "CloseTouchInputHandle"));

	if (close_touch_input_handle_func) {
		return (TRUE == close_touch_input_handle_func(hTouchInput));
	}

	return false;
}

}