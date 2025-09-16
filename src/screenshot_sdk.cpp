#include "pch.h"
#include "main_thread.h"
#include "screenshot_event_handler.h"

#include "capture_image/src/capture_manager.h"

// 基于nodejs 12.x； NODE_MODULE_VERSION = 80
// 参考文档 https://nodejs.org/dist/latest-v12.x/docs/api/addons.html

NAMESPACE_SCREENSHOTSDK_BEGIN

// 创建主线程
static CMainThread threadMain;
void InitCapture(const FunctionCallbackInfo<Value>& args)
{
	CHECK_ARGS_COUNT(2);

	auto status = napi_ok;
	node_util::UTF8String resource_path;
	GET_ARGS_VALUE(isolate, 0, UTF8String, resource_path);

	node_util::UTF8String lang_path;
	GET_ARGS_VALUE(isolate, 1, UTF8String, lang_path);

	// 执行主线程循环
	std::wstring wstr_resource_path = nbase::UTF8ToUTF16(resource_path.toUtf8String());
	std::wstring wstr_lang_path = nbase::UTF8ToUTF16(lang_path.toUtf8String());
	threadMain.SetPath(wstr_resource_path, wstr_lang_path);
	threadMain.StartWithLoop(nbase::MessageLoop::kUIMessageLoop, CWinMsgDispatcher::GetInstance());
}

void CleanupCapture(const FunctionCallbackInfo<Value>& args)
{
	if (!threadMain.IsRunning())
		return;

	CaptureManager::GetInstance()->EndCapture(L"");
	threadMain.Stop();
}

void StartCapture(const FunctionCallbackInfo<Value>& args)
{
	CHECK_ARGS_COUNT(3);

	auto status = napi_ok;
	node_util::UTF8String user_data_dir;
	GET_ARGS_VALUE(isolate, 0, UTF8String, user_data_dir);

	node_util::UTF8String send_info;
	GET_ARGS_VALUE(isolate, 1, UTF8String, send_info);

	Local<Function> cb = args[2].As<Function>();
	if (cb.IsEmpty())
		return;

	Persistent<Function> pcb;
	pcb.Reset(isolate, cb);
	Local<Object> obj = args.This();
	Persistent<Object> pdata;
	pdata.Reset(isolate, obj);
	node_util::BaseCallbackPtr bcb = node_util::BaseCallbackPtr(new node_util::BaseCallback());
	bcb->callback_.Reset(isolate, pcb);
	bcb->data_.Reset(isolate, pdata);

	auto callback = std::bind(&CScreenshotEventHandler::OnCaptureCallback, bcb, std::placeholders::_1, std::placeholders::_2);
	std::wstring wstr_user_data_dir = nbase::UTF8ToUTF16(user_data_dir.toUtf8String());
	std::wstring wstr_send_info = nbase::UTF8ToUTF16(send_info.toUtf8String());

	auto closure = [=]
	{
		CaptureManager::GetInstance()->StartCapture(callback, wstr_user_data_dir, wstr_send_info);
	};
	nbase::ThreadManager::PostTask(kThreadUI, closure);
}

void IsCaptureTracking(const FunctionCallbackInfo<Value>& args)
{
	CHECK_ARGS_COUNT(0);

	bool ret = CaptureManager::GetInstance()->IsCaptureTracking();
	args.GetReturnValue().Set(Boolean::New(isolate, ret));
}

NAMESPACE_SCREENSHOTSDK_END

void init(Local<Object> exports)
{
	NODE_SET_METHOD(exports, "initCapture", ScreenshotSdk::InitCapture);
	NODE_SET_METHOD(exports, "cleanupCapture", ScreenshotSdk::CleanupCapture);
	NODE_SET_METHOD(exports, "startCapture", ScreenshotSdk::StartCapture);
	NODE_SET_METHOD(exports, "isCaptureTracking", ScreenshotSdk::IsCaptureTracking);
}

// NODE_MODULE(screenshot_sdk, init)

// 以下是创建上下文感知插件
extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(Local<Object> exports,
    Local<Value> module,
    Local<Context> context) {
    /* Perform addon initialization steps here. */
    init(exports);
}

NODE_MODULE_CONTEXT_AWARE(NODE_GYP_MODULE_NAME, NODE_MODULE_INITIALIZER)