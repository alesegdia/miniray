

solution "programita"
  configurations { "Debug", "Release" }
  platforms { "x64", "x32" }
project "miniray"
  language "C++"
  kind "WindowedApp"
  files		{ "src/**.cpp" } -- "../game/src/**.h" }
  links		{ "c", "dl", "m", "rt", "freetype", "SDL2", "Box2D", "GL" }
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
	includedirs { "include32", "/usr/include/freetype2" }
	linkoptions {  }
  configuration { "x64" }
	includedirs { "include64,include","/usr/include/freetype2" }
	linkoptions { "-ftest-coverage", "-fprofile-arcs" }
