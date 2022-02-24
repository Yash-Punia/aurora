workspace "aurora"
    startproject "auroraeditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "auroraeditor"
    location "auroraeditor"
    kind "ConsoleApp"
    language "C++17"
    cppdialect "C++17"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    flags
    {
        "FatalWarnings"
    }