{
  "targets": [
    {
      "target_name": "node_util",
      "type": "static_library",
      "product_dir": "<(PRODUCT_DIR)/lib",
      "sources": [
        "src/node_async_queue.cpp",
        "src/node_event_handler.cpp",
        "src/node_helper.cpp"
      ],
      "include_dirs": [
        "include",
        "<!(node -e \"require('node-addon-api').include\")"
      ],
      "conditions": [
        ["OS=='win'", {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          }
        }]
      ]
    }
  ]
}