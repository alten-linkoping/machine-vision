{

'variables': {
        'pkg-config': 'pkg-config' 
        },

  "targets": [
    {
      "target_name": "opticalFlow_addon",
      "include_dirs": [
        "../header",
        #"/usr/local/opt/opencv\@3/include",
        #"<!@(<(pkg-config) opencv)",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        #"/usr/local/opt/opencv\@3/lib/lib*.*"
        '<!@(<(pkg-config) --libs opencv)'
      ],
      'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "sources": [
        "HOGDetection.cpp",
        "opticalFlow.cpp", 
        "main.cpp"
      ],
      "cflags!" : [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],
      "cflags" : [
        "<!@(<(pkg-config) --cflags opencv)"
      ],

      "conditions": [
        [
          "OS==\"mac\"", {
            "xcode_settings": {
              "OTHER_CFLAGS": [
                "-mmacosx-version-min=10.7",
                "-std=c++14",
                "-stdlib=libc++",
                "<!@(<(pkg-config) --cflags opencv)"
              ],
              "GCC_ENABLE_CPP_RTTI": "YES",
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
            }
          }
        ]
      ]
    }
  ]
}