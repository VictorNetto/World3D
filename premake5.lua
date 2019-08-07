workspace "World3D"
    configurations
	{ 
		"Debug",
		"Release"
	}
	--platforms { "Windows" }

	--filter "platforms:Windows"
	systemversion "latest"  --  Specify the version of the SDK

project "World3D"
	location "World3D"
	kind "StaticLib"
	architecture "x64"
    language "C++"

	targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
	objdir "bin-int/%{prj.name}/%{cfg.buildcfg}"

	libdirs
	{
		"%{wks.location}/Dependencies/glew-2.1.0/lib/Release/x64",
		"%{wks.location}/Dependencies/glfw-3.3.bin.WIN64/lib-vc2019"
	}
	links { "glfw3", "glew32s", "opengl32" }

	files 
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{wks.location}/Dependencies/glew-2.1.0/include",
		"%{wks.location}/Dependencies/glfw-3.3.bin.WIN64/include",
		"%{wks.location}/Dependencies/"
	}

	defines { "GLEW_STATIC" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"

project "Demo"
	location "Demo"
	kind "ConsoleApp"
	architecture "x64"
    language "C++"

	targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
	objdir "bin-int/%{ prj.name}/%{cfg.buildcfg}"

	libdirs { "%{wks.location}/bin/World3D/%{cfg.buildcfg}" }
	links { "World3D" }

	files 
	{
		"%{prj.name}/**.cpp",
		"%{wks.location}/DearImGui/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/World3D/include",
		"%{wks.location}/Dependencies/glew-2.1.0/include",
		"%{wks.location}/Dependencies/glfw-3.3.bin.WIN64/include",
		"%{wks.location}/Dependencies",
		"%{wks.location}/DearImGui"
	}


	postbuildcommands
	{
		"mkdir .\\..\\bin\\%{prj.name}\\%{cfg.buildcfg}\\res",
		"copy .\\res .\\..\\bin\\%{prj.name}\\%{cfg.buildcfg}\\res\\"
	}

	defines { "IMGUI_IMPL_OPENGL_LOADER_GLEW" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"