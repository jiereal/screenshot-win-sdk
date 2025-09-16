#include "pch.h"

#include "screenshot_event_handler.h"

void CScreenshotEventHandler::OnCaptureCallback(const node_util::BaseCallbackPtr& bcb, bool ret, const std::wstring& file_path)
{
	node_util::node_async_call::async_call([=]() {
		CScreenshotEventHandler::GetInstance()->Node_OnCaptureCallback(bcb, ret, file_path);
	});
}

void CScreenshotEventHandler::Node_OnCaptureCallback(const node_util::BaseCallbackPtr& bcb, bool ret, const std::wstring& file_path)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	const unsigned argc = 2;
	std::string utf8_file_path = nbase::UTF16ToUTF8(file_path);
	Local<Value> argv[argc] = {
				node_util::nim_napi_new_bool(isolate, ret),
				node_util::nim_napi_new_utf8string(isolate, utf8_file_path.c_str())
	};
	bcb->callback_.Get(isolate)->Call(isolate->GetCurrentContext(), bcb->data_.Get(isolate), argc, argv);
}
