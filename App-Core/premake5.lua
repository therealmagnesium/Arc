local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("App-Core")
kind("StaticLib")
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
	"source",
	"../vendor/glm",
	"../vendor/glad/include",
	"../vendor/SDL/include",
	"../vendor/stb_image/include",
})

links({
	"glad",
	"SDL3",
	"stb_image",
})

filter("system:linux")
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

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
