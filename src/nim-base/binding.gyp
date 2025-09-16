{
	"targets": [
	{
		'target_name': 'base',
		'type': 'static_library',
		'include_dirs': [
			'./',
			'./tool_kits/'
		],
		'win_delay_load_hook': 'false',
		'sources': [
			'<!@(list-file "tool_kits\\base\\*.h")',
			'<!@(list-file "tool_kits\\base\\callback\\*.h")',
			'<!@(list-file "tool_kits\\base\\encrypt\\*.h")',
			'<!@(list-file "tool_kits\\base\\encrypt\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\file\\*.h")',
			'<!@(list-file "tool_kits\\base\\file\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\framework\\*.h")',
			'<!@(list-file "tool_kits\\base\\framework\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\hardware\\*.h")',
			'<!@(list-file "tool_kits\\base\\hardware\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\memory\\*.h")',
			'<!@(list-file "tool_kits\\base\\memory\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\network\\*.h")',
			'<!@(list-file "tool_kits\\base\\network\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\synchronization\\*.h")',
			'<!@(list-file "tool_kits\\base\\synchronization\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\third_party\\convert_utf\\*.h")',
			'<!@(list-file "tool_kits\\base\\third_party\\convert_utf\\*.c")',
			'<!@(list-file "tool_kits\\base\\third_party\\modp_b64\\*.h")',
			'<!@(list-file "tool_kits\\base\\third_party\\modp_b64\\*.cc")',
			'<!@(list-file "tool_kits\\base\\thread\\*.h")',
			'<!@(list-file "tool_kits\\base\\thread\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\time\\*.h")',
			'<!@(list-file "tool_kits\\base\\time\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\util\\*.h")',
			'<!@(list-file "tool_kits\\base\\util\\*.cpp")',
			'<!@(list-file "tool_kits\\base\\win32\\*.h")',
			'<!@(list-file "tool_kits\\base\\win32\\*.cpp")',
		],
		'sources!': [
			'tool_kits\\base\\encrypt\\encrypt_unittest.cpp',
			'tool_kits\\base\\time\\timer.cpp',
			'tool_kits\\base\\time\\time_unittest.cpp',
			'tool_kits\\base\\time\\timer_unittest.cpp',
			'tool_kits\\base\\util\\base64_unittest.cpp',
			'tool_kits\\base\\util\\bind_unittest.cpp',
			'tool_kits\\base\\util\\callback_unittest.cpp',
			'tool_kits\\base\\util\\string_util_unittest.cpp',
			'tool_kits\\base\\util\\template_util_unittest.cpp',
			'tool_kits\\base\\util\\tuple_unittest.cpp',
			'tool_kits\\base\\util\\valuemap_unittest.cpp',
			'tool_kits\\base\\win32\\platform_string_util_unittest.cpp',
			'tool_kits\\base\\win32\\shared_memory_unittest.cpp',
		],
		'conditions': [
			[
				'OS=="win"',
				{
					'defines': [
						'WIN32',
						'_WINDOWS',
						'_UNICODE',
						'UNICODE',
						'_LIB',
						'NOMINMAX',
						'WITH_ENCRYPT',
						'CURL_STATICLIB',
					],
					'msvs_settings': {
						'VCCLCompilerTool': {
							'ExceptionHandling': '1', # /EHsc
							'AdditionalOptions': [
								# '/EHsc'
							]
						}
					},
					'configurations': {
						'Release': {
							'defines': [
								'NDEBUG'
							],
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '0',
									'Optimization': '2',
									'RuntimeTypeInfo': 'true',
									'DebugInformationFormat': '3',
								}
							},
						},
						'Debug': {
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '1',
								}
							},
						}
					}
				}
			]
		]
	},
	{
		'target_name': 'duilib',
		'type': 'static_library',
		'include_dirs': [
			'./',
			'./tool_kits/',
			'./tool_kits/duilib/',
			'./third_party/',
		],
		'win_delay_load_hook': 'false',
		'sources': [
			'<!@(list-file "tool_kits\\duilib\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Animation\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Box\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Control\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Core\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Render\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\Utils\\*.h")',
			'<!@(list-file "tool_kits\\duilib\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Animation\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Box\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Control\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Core\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Render\\*.cpp")',
			'<!@(list-file "tool_kits\\duilib\\Utils\\*.cpp")',
		],
		'sources!': [
		],
		'conditions': [
			[
				'OS=="win"',
				{
					'defines': [
						'WIN32',
						'_WINDOWS',
						'_UNICODE',
						'UNICODE',
						'_CRT_SECURE_NO_WARNINGS',
						'_CRT_SECURE_NO_DEPRECATE',
					],
					'defines!': [],
					'msvs_settings': {
						'VCCLCompilerTool': {
							'ExceptionHandling': '1', # /EHsc
							# 'WarningLevel': '3',
							# 'DisableSpecificWarnings': ['4819'],
							# 'WarnAsError': 'false',
							'AdditionalOptions': [
								# '/EHsc',
								# '/utf-8'
							]
						}
					},
					'link_settings': {
						'libraries': [
							'-lcomctl32.lib',
							'-lgdiplus.lib',
							'-lmsimg32.lib',
							'-lwinmm.lib',
							'-limm32.lib',
							'-lshlwapi.lib'
						]
					},
					'configurations': {
						'Release': {
							'defines': [
								'NDEBUG'
							],
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '0',
									'Optimization': '2',
									'FavorSizeOrSpeed': '0',
									'InlineFunctionExpansion': '0',
									'OmitFramePointers': 'false',
									'ExceptionHandling': '1',
									'EnableIntrinsicFunctions': 'true',
									'RuntimeTypeInfo': 'true',
									'DebugInformationFormat': '3',
								}
							},
						},
						'Debug': {
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '1',
								}
							},
						}
					}
				}
			]
		]
	},
	{
		'target_name': 'capture_image',
		'type': 'static_library',
		'include_dirs': [
			'./',
			'./tool_kits/',
			'./tool_kits/duilib/',
			'./tool_kits/capture_image/',
			'./third_party/',
		],
		'win_delay_load_hook': 'false',
		'sources': [
			'<!@(list-file "tool_kits\\capture_image\\*.h")',
			'<!@(list-file "tool_kits\\capture_image\\image_effects\\*.h")',
			'<!@(list-file "tool_kits\\capture_image\\modal_wnd\\*.h")',
			'<!@(list-file "tool_kits\\capture_image\\src\\*.h")',
			'<!@(list-file "tool_kits\\capture_image\\image_effects\\*.cpp")',
			'<!@(list-file "tool_kits\\capture_image\\modal_wnd\\*.cpp")',
			'<!@(list-file "tool_kits\\capture_image\\src\\*.cpp")',
		],
		'sources!': [
		],
		'conditions': [
			[
				'OS=="win"',
				{
					'defines': [
						'WIN32',
						'_WINDOWS',
						'_UNICODE',
						'UNICODE'
					],
					'msvs_settings': {
						'VCCLCompilerTool': {
							'ExceptionHandling': '1', # /EHsc
							'AdditionalOptions': [
								# '/EHsc'
							]
						}
					},
					'configurations': {
						'Release': {
							'defines': [
								'NDEBUG'
							],
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '0',
									'Optimization': '2',
									'DebugInformationFormat': '3',
									'RuntimeTypeInfo': 'true',
									'AdditionalOptions': []
								}
							},
						},
						'Debug': {
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '1',
									'AdditionalOptions': []
								}
							},
						}
					}
				}
			]
		]
	}],
}
