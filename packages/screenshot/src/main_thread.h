#pragma once

NAMESPACE_SCREENSHOTSDK_BEGIN

/** @class MainThread
  * @brief ���̣߳�UI�̣߳��࣬�̳�nbase::FrameworkThread
  */
class CMainThread : public nbase::FrameworkThread
{
public:
	CMainThread();
	virtual ~CMainThread();

	void SetPath(const std::wstring& resource_path, const std::wstring& lang_path);

private:
	/**
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

	/**
	* ���߳̿�ʼѭ��ǰ��misc�̺߳�db�߳��ȿ�ʼѭ��
	* @return void	�޷���ֵ
	*/
	void PreMessageLoop();

	/**
	* ���߳̽���ѭ��ǰ��misc�̺߳�db�߳��Ƚ���ѭ��
	* @return void	�޷���ֵ
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
