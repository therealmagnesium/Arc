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
	"../vendor/stb_image/include",
})

links({
	"App-Core",
	"glad",
	"SDL3",
	"stb_image",
})

postbuildcommands({
	"cp -r assets/ %{cfg.buildtarget.directory}",
	--"cp -r scenes/ %{cfg.buildtarget.directory}",
	--"cp ../imgui.ini %{cfg.buildtarget.directory}",
})

filter("system:linux")
postbuildcommands({
	"cp ../vendor/SDL/lib/linux/* %{cfg.buildtarget.directory}",
})
libdirs({
	"../vendor/glad/lib/linux",
	"../vendor/SDL/lib/linux",
	"../vendor/stb_image/lib/linux",
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
