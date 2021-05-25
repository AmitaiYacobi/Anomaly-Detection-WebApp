{
  "targets": [
    {
      "target_name": "algorithm",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/index.cpp",
        "./src/anomaly_detection_util.cpp",
        "./src/AnomalyReportDLL.cpp",
        "./src/HybridAnomalyDetector.cpp",
        "./src/minCircle.cpp",
        "./src/SimpleAnomalyDetector.cpp",
        "./src/timeseries.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}