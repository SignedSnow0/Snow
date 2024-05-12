project "SnowEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    debugdir "%{wks.location}"

    targetdir "%{wks.location}/bin/%{wks.buildcfg}"
    objdir "%{wks.location}/bin/%{wks.buildcfg}/obj"

    files { "Source/**.h", "Source/**.cpp" }

    links 
    {
        "SnowEngine"
    }

    includedirs
    {
        "Source/",
        "%{wks.location}/Engine/Source/"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
