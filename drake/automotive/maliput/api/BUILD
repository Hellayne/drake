# -*- python -*-
# This file contains rules for Bazel; see drake/doc/bazel.rst.

load("//tools:cpplint.bzl", "cpplint")
load("//tools:drake.bzl", "drake_cc_library")

package(default_visibility = ["//visibility:public"])

drake_cc_library(
    name = "api",
    srcs = [
        "road_geometry.cc",
    ],
    hdrs = [
        "branch_point.h",
        "junction.h",
        "lane.h",
        "lane_data.h",
        "road_geometry.h",
        "segment.h",
    ],
    linkstatic = 1,
    deps = [
        "//drake/common",
    ],
)

cpplint()
