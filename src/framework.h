#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容

// Windows 头文件
#include <windows.h>
#include <string>
#include <algorithm> 
#include <memory>
#include <atlbase.h>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <sdkddkver.h>

// v8 header
#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <uv.h>
using namespace v8;

//node util header
#include "node_util/include/node_async_queue.h"
#include "node_util/include/node_event_handler.h"
#include "node_util/include/node_helper.h"

//base header
#include "base/callback/callback.h"
#include "base/util/string_util.h"
#include "base/util/unicode.h"
#include "base/util/base64.h"
#include "base/util/string_number_conversions.h"
#include "base/memory/deleter.h"
#include "base/memory/singleton.h"
#include "base/win32/platform_string_util.h"
#include "base/win32/path_util.h"
#include "base/win32/win_util.h"
#include "base/thread/thread_manager.h"
#include "base/macros.h"
#include "base/base_types.h"
#include "base/file/file_util.h"
#include "base/time/time.h"
#include "base/framework/task.h"

//uilib
#include "duilib/UIlib.h"
// using namespace ui;

#include "define/sdk_define.h"
