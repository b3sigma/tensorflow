cc_binary(
    name = "librungraph.so",
    srcs = [
        "librungraph.h",
        "librungraph.cc",
    ],
    deps = [
        "//tensorflow/core:tensorflow",
    ],
    linkopts = ["-shared"],
)

cc_binary(
    name = "librungraph.testmain",
    srcs = [
        "librungraph.h",
        "librungraph.cc",
        "librungraph.testmain.cc",
    ],
    deps = [
        "//tensorflow/core:tensorflow",
    ],
)
