#include "pch.h"

#include "main_thread.h"

NAMESPACE_SCREENSHOTSDK_BEGIN

//////////////////////////////////////////////////////////////////////////
/* MainThread */
CMainThread::CMainThread()
	: nbase::FrameworkThread("MainThread")
	, resource_path_(L"")
	, lang_path_(L"")
{

}

CMainThread::~CMainThread()
{

}
void CMainThread::SetPath(const std::wstring& resource_path, const std::wstring& lang_path)
{
	resource_path_ = resource_path;
	lang_path_ = lang_path;
}

void CMainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);
	PreMessageLoop();

	std::wstring language = L"zh_CN";
	ui::GlobalManager::Startup(resource_path_, ui::CreateControlCallback(), true, lang_path_, language);
}

void CMainThread::Cleanup()
{
	ui::GlobalManager::Shutdown();

	PostMessageLoop();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}

void CMainThread::PreMessageLoop()
{

}

void CMainThread::PostMessageLoop()
{

}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/* CWinMsgDispatcher */
bool CWinMsgDispatcher::Dispatch(const MSG &message)
{
	if (!ui::GlobalManager::TranslateMessage((LPMSG)&message))
	{
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}

	if (WM_QUIT == message.message)
	{
		return false;
	}
	else
	{
		return true;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

NAMESPACE_SCREENSHOTSDK_END
