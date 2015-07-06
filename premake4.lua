

solution "miniraygame"
  configurations { "Debug", "Release" }
  platforms { "x64", "x32" }

project "glrayfw"
  kind "StaticLib"
  language "C++"
  buildoptions {"-std=c++11"}
  files {
    "src/lib/**.cpp",
    "src/lib/**.h"
  }
project "miniray"
  language "C++"
  kind "WindowedApp"
  files		{ "src/game/**.cpp", "src/game/**.h" } -- "../game/src/game/**.h" }
  links		{ "glrayfw", "c", "dl", "m", "rt", "freetype", "SDL2", "Box2D", "GL" }
  buildoptions { "-std=c++11" }
  includedirs { "~/Libs/cml-1_0_3/" }
  configuration { "Debug*" }
	defines	{ "_DEBUG", "DEBUG" }
	flags	{ "Symbols" }
	targetdir "bin/debug64"
  configuration { "not Debug*" }
	defines { "NDEBUG" }
	flags	{ "Optimize" }
	targetdir "bin/release64"
  configuration { "x32" }
	includedirs { "src/lib", "include32", "/usr/include/freetype2" }
	linkoptions {  }
  configuration { "x64" }
	includedirs { "src/lib", "include64,include","/usr/include/freetype2" }
	linkoptions { "-ftest-coverage", "-fprofile-arcs" }
