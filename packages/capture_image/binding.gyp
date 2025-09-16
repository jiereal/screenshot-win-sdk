{
	"targets": [
	{
		"target_name": "capture_image",
		"type": "static_library",
		"include_dirs": [
			"./",
			"./tool_kits/",
			"./tool_kits/duilib/",
			"./tool_kits/capture_image/",
			"./third_party/"
		],
		"win_delay_load_hook": "false",
		"sources": [
			"<!@(list-file \"tool_kits\\capture_image\\*.h\")",
			"<!@(list-file \"tool_kits\\capture_image\\image_effects\\*.h\")",
			"<!@(list-file \"tool_kits\\capture_image\\modal_wnd\\*.h\")",
			"<!@(list-file \"tool_kits\\capture_image\\src\\*.h\")",
			"<!@(list-file \"tool_kits\\capture_image\\image_effects\\*.cpp\")",
			"<!@(list-file \"tool_kits\\capture_image\\modal_wnd\\*.cpp\")",
			"<!@(list-file \"tool_kits\\capture_image\\src\\*.cpp\")"
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
						"UNICODE"
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
									"DebugInformationFormat": "3",
									"RuntimeTypeInfo": "true",
									"AdditionalOptions": []
								}
							}
						},
						"Debug": {
							"msvs_settings": {
								"VCCLCompilerTool": {
									"RuntimeLibrary": "1",
									"AdditionalOptions": []
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