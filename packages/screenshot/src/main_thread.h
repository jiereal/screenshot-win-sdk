#pragma once

NAMESPACE_SCREENSHOTSDK_BEGIN

/** @class MainThread
  * @brief 主线程（UI线程）类，继承nbase::FrameworkThread
  */
class CMainThread : public nbase::FrameworkThread
{
public:
	CMainThread();
	virtual ~CMainThread();

	void SetPath(const std::wstring& resource_path, const std::wstring& lang_path);

private:
	/**
	* 虚函数，初始化主线程
	* @return void	无返回值
	*/
	virtual void Init() override;

	/**
	* 虚函数，主线程退出时，做一些清理工作
	* @return void	无返回值
	*/
	virtual void Cleanup() override;

	/**
	* 主线程开始循环前，misc线程和db线程先开始循环
	* @return void	无返回值
	*/
	void PreMessageLoop();

	/**
	* 主线程结束循环前，misc线程和db线程先结束循环
	* @return void	无返回值
	*/
	void PostMessageLoop();

private:
	std::wstring resource_path_;
	std::wstring lang_path_;
};

class CWinMsgDispatcher : public nbase::Dispatcher
{
private:
	CWinMsgDispatcher(void)
	{
	};
	~CWinMsgDispatcher(void)
	{
	};

public:
	SINGLETON_DEFINE(CWinMsgDispatcher);

public:
	virtual bool Dispatch(const MSG &message);
};

NAMESPACE_SCREENSHOTSDK_END
