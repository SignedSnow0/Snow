require "ecc/ecc"

workspace "SnowEngine"
    architecture "x64"
    configurations { "Debug", "Release" }

include "Engine"
include "Editor"
