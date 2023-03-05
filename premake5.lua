include "conanbuildinfo.premake.lua"

workspace "TerminalUI"
    conan_basic_setup()
    architecture "x64"
    startproject "terminal-ui"

    configurations
    {
        "Debug",
        "Release"
    }

    project "terminal-ui"
        location "terminal-ui"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir "build/bin/%{prj.name}-%{cfg.buildcfg}"
        objdir "build/obj/%{prj.name}-%{cfg.buildcfg}"

        files
        {
            "%{prj.name}/includes/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "%{prj.name}/includes",
            "includes/"
        }

        filter "configurations:Debug"
            defines "TUI_DEBUG"
            runtime "Debug"
            symbols "on"
        
        filter "configurations:Release"
            defines "TUI_RELEASE"
            runtime "Release"
            optimize "on"