project "SnowEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    debugdir "%{wks.location}"

    targetdir "%{wks.location}/bin/%{wks.buildcfg}"
    objdir "%{wks.location}/bin/%{wks.buildcfg}/obj"

    files { "Source/**.h", "Source/**.cpp" }

    VULKAN_SDK = os.getenv("VULKAN_SDK")

    links
    {
        "SnowEngine",
        "GLFW",
    }

    includedirs
    {
        "Source/",
        "%{wks.location}/Engine/Source/",
        "%{VULKAN_SDK}/Include/",
        "%{wks.location}/Engine/External/glfw/include/"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
