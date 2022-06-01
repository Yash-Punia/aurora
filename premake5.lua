--Working directory and starting point of program

workspace "aurora"
    startproject "auroraeditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

--Target and object directories

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

--External Dependencies
externals = {}

externals["sdl2"] = "external/sdl2"
externals["spdlog"] = "external/spdlog"
externals["glad"] = "external/glad"

--Process Glad before anything else
include "external/glad"

--Aurora Engine as a linking library
project "Aurora"
    location "Aurora"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on" --To link every single library statically
    
    targetdir(tdir)
    objdir(odir)

    --Every single file to use is here!!
    files 
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.hpp",
        "%{prj.name}/include/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/**.gdb",
    }

    --To build this module, use includes
    sysincludedirs
    {
        "%{prj.name}/include/aurora",
        "%{prj.name}/include/external",
        "%{externals.sdl2}/include",
        "%{externals.spdlog}/include",
        "%{externals.glad}/include"
    }

    flags
    {
        "FatalWarnings"
    }

    defines
    { 
        "GLFW_INCLUDE_NONE" --Ensures that Glad doesn't include GLFW
    }
    

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "AURORA_PLATFORM_WINDOWS"
        }

    --Debug config generates redundant files with more info
    filter "configurations:Debug"
        defines
        {
            "AURORA_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    --Release config generates only relevant files with optimized code
    filter "configurations:Release"
        defines
        {
            "AURORA_CONFIG_RELEASE"
        }
        runtime "Release"

        symbols "off"
        optimize "on"


--Main editor application
project "PongV1"
    location "PongV1"
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
        "%{prj.name}/src",
        "%{externals.spdlog}/include"
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

        --To run application on windows, provides the appropriate library to support the run
        libdirs
        {
            "%{externals.sdl2}/lib"
        }

        --Links the dependencies from external
        links
        {
            "SDL2",
            "glad"
        }

    --Debug config generates redundant files with more info
    filter "configurations:Debug"
        defines
        {
            "AURORA_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    --Release config generates only relevant files with optimized code
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
            "%{prj.name}/src",
            "%{externals.spdlog}/include"
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
    
            --To run application on windows, provides the appropriate library to support the run
            libdirs
            {
                "%{externals.sdl2}/lib"
            }
    
            --Links the dependencies from external
            links
            {
                "SDL2",
                "glad"
            }
    
        --Debug config generates redundant files with more info
        filter "configurations:Debug"
            defines
            {
                "AURORA_CONFIG_DEBUG"
            }
            runtime "Debug"
            symbols "on"
    
        --Release config generates only relevant files with optimized code
        filter "configurations:Release"
            defines
            {
                "AURORA_CONFIG_RELEASE"
            }
            runtime "Release"
            symbols "off"
            optimize "on"