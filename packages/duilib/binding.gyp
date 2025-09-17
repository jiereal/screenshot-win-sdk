{
	"targets": [
	{
		"target_name": "duilib",
		"type": "static_library",
		"product_dir": "<(PRODUCT_DIR)/lib",
		"include_dirs": [
			"./",
			"./tool_kits/",
			"./tool_kits/duilib/",
			"./third_party/"
		],
		"win_delay_load_hook": "false",
		"sources": [
			"<!@(list-file \"tool_kits\\duilib\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Animation\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Box\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Control\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Core\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Render\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\Utils\\*.h\")",
			"<!@(list-file \"tool_kits\\duilib\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Animation\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Box\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Control\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Core\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Render\\*.cpp\")",
			"<!@(list-file \"tool_kits\\duilib\\Utils\\*.cpp\")"
		],
		"sources!": [],
		"conditions": [
			[
				"OS==\"win\"",
				{
					"defines": [
						"WIN32",
						"_WINDOWS",
						"_UNICODE",
						"UNICODE",
						"_CRT_SECURE_NO_WARNINGS",
						"_CRT_SECURE_NO_DEPRECATE"
					],
					"defines!": [],
					"msvs_settings": {
						"VCCLCompilerTool": {
							"ExceptionHandling": "1"
						}
					},
					"link_settings": {
						"libraries": [
							"-lcomctl32.lib",
							"-lgdiplus.lib",
							"-lmsimg32.lib",
							"-lwinmm.lib",
							"-limm32.lib",
							"-lshlwapi.lib"
						]
					},
					"configurations": {
						"Release": {
							"defines": ["NDEBUG"],
							"msvs_settings": {
								"VCCLCompilerTool": {
									"RuntimeLibrary": "0",
									"Optimization": "2",
									"FavorSizeOrSpeed": "0",
									"InlineFunctionExpansion": "0",
									"OmitFramePointers": "false",
									"ExceptionHandling": "1",
									"EnableIntrinsicFunctions": "true",
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