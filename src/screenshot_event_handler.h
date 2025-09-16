#pragma once

class CScreenshotEventHandler : public node_util::EventHandler
{
private:
	/* data */
public:
	CScreenshotEventHandler()
	{
	};
	~CScreenshotEventHandler()
	{
	};
	SINGLETON_DEFINE(CScreenshotEventHandler);

	static void OnCaptureCallback(const node_util::BaseCallbackPtr& bcb, bool ret, const std::wstring& file_path);

private:
	void Node_OnCaptureCallback(const node_util::BaseCallbackPtr& bcb, bool ret, const std::wstring& file_path);
};
