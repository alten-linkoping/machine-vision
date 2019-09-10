{

'variables': {
        'pkg-config': 'pkg-config' 
        },

  "targets": [
    {
      "target_name": "opticalFlow_addon",
      "include_dirs": [
        "../header",
        "/usr/local/opt/opencv\@3/include"
        #"pkg-config --cflags opencv"
      ],
      "libraries": [
        "/usr/local/opt/opencv\@3/lib/lib*.*"
        #"pkg-config --libs opencv"
      ],
      "sources": [
        "opticalFlow.cpp"
      ],
      "cflags!" : [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],

      "conditions": [
        [
          "OS==\"mac\"", {
            "xcode_settings": {
              "OTHER_CFLAGS": [
                "-mmacosx-version-min=10.7",
                "-std=c++14",
                "-stdlib=libc++"
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