project "glad"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on" --To link every single library statically
    
    targetdir(tdir)
    objdir(odir)

    --Every single file to use is here!!
    files 
    {
        "include/**.h",
        "src/**.cpp"
    }

    --To build this module, use includes
    sysincludedirs
    {
        "include"
    }

    filter {"system:windows"}
        systemversion "latest"

    --Debug config generates redundant files with more info
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    --Release config generates only relevant files with optimized code
    filter "configurations:Release"
        runtime "Release"
        symbols "off"
        optimize "on"