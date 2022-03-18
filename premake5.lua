workspace "aurora"
    startproject "auroraeditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }


tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

--External Dependencies
externals = {}

externals["sdl2"] = "external/sdl2"


project "Aurora"
    location "Aurora"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir(tdir)
    objdir(odir)

    files 
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    sysincludedirs
    {
        "%{prj.name}/include/aurora",
        "%{externals.sdl2}/include"
    }

    flags
    {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "AURORA_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines
        {
            "AURORA_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "AURORA_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"



project "AuroraEditor"
    location "AuroraEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    links "Aurora"

    targetdir(tdir)
    objdir(odir)

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    sysincludedirs
    {
        "Aurora/include",
        "%{prj.name}/src"
    }

    flags
    {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "AURORA_PLATFORM_WINDOWS"
        }

        libdirs
        {
            "%{externals.sdl2}/lib"
        }

        links
        {
            "SDL2"
        }

    filter "configurations:Debug"
        defines
        {
            "AURORA_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "AURORA_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"