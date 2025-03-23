local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Application")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.cpp",
})

includedirs({
    "../App-Core/source",
    "../vendor/glm",
    "../vendor/glad/include",
    "../vendor/SDL/include",
})

links({
    "App-Core",
    "SDL3",
})

postbuildcommands({
    "cp -r assets/ %{cfg.buildtarget.directory}",
    --"cp -r scenes/ %{cfg.buildtarget.directory}",
    --"cp ../imgui.ini %{cfg.buildtarget.directory}",
})

filter("system:linux")
libdirs({
    "../vendor/SDL/lib/linux",
})
defines({
    "PLATFORM_LINUX",
})

filter("system:windows")
defines({
    "PLATFORM_WINDOWS",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")
