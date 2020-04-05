workspace "Weasel"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Weasel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Weasel/vendor/GLAD/include"
IncludeDir["ImGui"] = "Weasel/vendor/ImGui"
IncludeDir["glm"] = "Weasel/vendor/glm"
IncludeDir["stb_image"] = "Weasel/vendor/stb_image"
include "Weasel/vendor/GLFW"
include "Weasel/vendor/GLAD"
include "Weasel/vendor/ImGui"

    project "Weasel"
    location "Weasel"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "wspch.h"
    pchsource "Weasel/src/wspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/glm/glm/**.h",
        "%{prj.name}/vendor/glm/glm/**.hpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "Weasel/vendor",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "opengl32.lib",
        "ImGui"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GLFW_INCLUDE_NONE",
            "WS_PLATFORM_WINDOWS",
            "WS_BUILD_DLL"
        }


    filter "configurations:Debug"
        defines
        {
            "WS_DEBUG",
            "WS_ENABLE_ASSERTS"
        }
        buildoptions "/MDd"
        symbols "on"
    filter "configurations:Release"
        defines "WS_RELEASE"
        buildoptions "/MD"
        optimize "on"
    filter "configurations:Dist"
        defines "WS_DIST"
        buildoptions "/MD"
        optimize "on"

project "Sanbox"
        location "Sanbox"
        kind "ConsoleApp"
        language "C++"
        staticruntime "on"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Weasel/vendor/spdlog/include",
        "Weasel/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "Weasel",
        "GLFW",
        "GLAD",
        "opengl32.lib",
        "ImGui"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "WS_DEBUG"
        buildoptions "/MDd"
        symbols "on"
    filter "configurations:Release"
        defines "WS_RELEASE"
        buildoptions "/MD"
        optimize "on"
    filter "configurations:Dist"
        defines "WS_DIST"
        buildoptions "/MD"
        optimize "on"
    
