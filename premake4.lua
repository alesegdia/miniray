

solution "miniraygame"
  configurations { "Debug", "Release" }
  platforms { "x64", "x32" }

project "glrayfw"
  kind "StaticLib"
  language "C++"
  buildoptions {"-std=c++11", "-pg" }
  includedirs {"include64,include", "/usr/include/freetype2"}
  files {
    "lib/glrayfw/glrayfw/**.cpp",
    "lib/glrayfw/glrayfw/**.h",
  }
project "miniray"
  language "C++"
  kind "WindowedApp"
  files		{ "src/game/**.cpp", "src/game/**.h" } -- "../game/src/game/**.h" }
  links		{ "glrayfw", "c", "dl", "m", "rt", "freetype", "SDL2", "Box2D", "GL" }
  buildoptions { "-std=c++11", "-pg" }
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
	includedirs { "lib/glrayfw", "include32", "/usr/include/freetype2" }
	linkoptions { "-pg" }
  configuration { "x64" }
	includedirs { "lib/glrayfw", "include64,include","/usr/include/freetype2" }
	linkoptions { "-pg", "-ftest-coverage", "-fprofile-arcs" }
