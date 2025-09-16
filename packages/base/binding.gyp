{
	"targets": [
	{
		"target_name": "base",
		"type": "static_library",
		"include_dirs": [
			"./",
			"./tool_kits/"
		],
		"win_delay_load_hook": "false",
		"sources": [
			"<!@(list-file \"tool_kits\\base\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\callback\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\encrypt\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\encrypt\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\file\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\file\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\framework\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\framework\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\hardware\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\hardware\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\memory\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\memory\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\network\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\network\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\synchronization\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\synchronization\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\third_party\\convert_utf\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\third_party\\convert_utf\\*.c\")",
			"<!@(list-file \"tool_kits\\base\\third_party\\modp_b64\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\third_party\\modp_b64\\*.cc\")",
			"<!@(list-file \"tool_kits\\base\\thread\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\thread\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\time\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\time\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\util\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\util\\*.cpp\")",
			"<!@(list-file \"tool_kits\\base\\win32\\*.h\")",
			"<!@(list-file \"tool_kits\\base\\win32\\*.cpp\")"
		],
		"sources!": [
			"tool_kits\\base\\encrypt\\encrypt_unittest.cpp",
			"tool_kits\\base\\time\\timer.cpp",
			"tool_kits\\base\\time\\time_unittest.cpp",
			"tool_kits\\base\\time\\timer_unittest.cpp",
			"tool_kits\\base\\util\\base64_unittest.cpp",
			"tool_kits\\base\\util\\bind_unittest.cpp",
			"tool_kits\\base\\util\\callback_unittest.cpp",
			"tool_kits\\base\\util\\string_util_unittest.cpp",
			"tool_kits\\base\\util\\template_util_unittest.cpp",
			"tool_kits\\base\\util\\tuple_unittest.cpp",
			"tool_kits\\base\\util\\valuemap_unittest.cpp",
			"tool_kits\\base\\win32\\platform_string_util_unittest.cpp",
			"tool_kits\\base\\win32\\shared_memory_unittest.cpp"
		],
		"conditions": [
			[
				"OS==\"win\"",
				{
					"defines": [
						"WIN32",
						"_WINDOWS",
						"_UNICODE",
						"UNICODE",
						"_LIB",
						"NOMINMAX",
						"WITH_ENCRYPT",
						"CURL_STATICLIB"
					],
					"msvs_settings": {
						"VCCLCompilerTool": {
							"ExceptionHandling": "1"
						}
					},
					"configurations": {
						"Release": {
							"defines": ["NDEBUG"],
							"msvs_settings": {
								"VCCLCompilerTool": {
									"RuntimeLibrary": "0",
									"Optimization": "2",
									"RuntimeTypeInfo": "true",
									"DebugInformationFormat": "3"
								}
							}
						},
						"Debug": {
							"msvs_settings": {
								"VCCLCompilerTool": {
									"RuntimeLibrary": "1"
								}
							}
						}
					}
				}
			]
		]
	}
	]
}