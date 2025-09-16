{
	"targets": [
	{
		'target_name': 'screenshot_sdk',
		'dependencies': [
			'../node_util/binding.gyp',
			'./base/binding.gyp',
			'./duilib/binding.gyp',
			'./capture_image/binding.gyp',
		],
		'include_dirs': [
			'./src/'
		],
		'sources': [
			'define/sdk_define.h',
			'framework.h',
			'main_thread.h',
			'main_thread.cpp',
			'pch.h',
			'pch.cpp',
			'screenshot_event_handler.h',
			'screenshot_event_handler.cpp',
			'screenshot_sdk.cpp',
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
						'_USRDLL',
					],
					'defines!': [],
					'library_dirs': [
						'<(PRODUCT_DIR)'
					],
					'link_settings': {
						'libraries': [
							'-lnode_util.lib',
							'-lbase.lib',
							'-lduilib.lib',
							'-lcapture_image.lib',
							'-lcomctl32.lib',
							'-lgdiplus.lib',
							'-lmsimg32.lib',
							'-lwinmm.lib',
							'-limm32.lib',
							'-lshlwapi.lib'
						]
					},
					'msvs_settings': {
						'VCCLCompilerTool': {
							'ExceptionHandling': '1', # /EHsc
							'AdditionalOptions': [
								# '/EHsc',
							]
						}
					},
					'configurations': {
						'Release': {
							'defines': [
								'NDEBUG',
							],
							'msvs_settings': {
								'VCCLCompilerTool': {
									'RuntimeLibrary': '0',
									'Optimization': '2',
									'DebugInformationFormat': '3',
									'RuntimeTypeInfo': 'true',
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
	}]
}
