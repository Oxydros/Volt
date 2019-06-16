workspace "Volt"
   architecture "x64"
   configurations { "Debug", "Release" }

   -- Compile GLFW static lib
   os.execute("cd Volt/vendor/GLFW && cmake -DBUILD_SHARED_LIBS=off . && make glfw")

   -- Setup GLFW static lib directory
   libdirs {
      "Volt/vendor/GLFW/src"
   }

   outputdir = "%{cfg.buildcfg}-%{cfg.system}"


   -- Sub project dependencies
   include "Volt/vendor/glad"

project "Volt"
   location "Volt"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"

   targetdir("bin/" .. outputdir .. "/%{prj.name}")
   objdir("obj/" .. outputdir .. "/%{prj.name}")

   pchheader "vpch.h"
   pchsource "Volt/src/vpch.cpp"

   files { 
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.hpp",
      "%{prj.name}/src/**.cpp",
   }

   includedirs {
      "%{prj.name}/vendor/spdlog/include",
      "%{prj.name}/vendor/glad/include",
      "%{prj.name}/vendor/GLFW/include",
      "%{prj.name}/src"
   }

   -- Link to third party libraries
   links {
      "glfw3",
      "glad"
   }

   filter "configurations:Debug"
      defines { 
         "VOLT_DEBUG"
      }
      symbols "On"

   filter "configurations:Release"
      defines {
         "VOLT_RELEASE"
      }
      optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"
   objdir "obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"

   files { 
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.hpp",
      "%{prj.name}/src/**.cpp"
   }

   includedirs {
      "Volt/vendor/spdlog/include",
      "Volt/src",
      "%{prj.name}/src"
   }

   links { 
      "Volt",
      "glad",
      "glfw3",
      "X11",
      "pthread",
      "dl"
   }

   filter "configurations:Debug"
      defines { 
         "VOLT_DEBUG"
      }
      symbols "On"

   filter "configurations:Release"
      defines {
         "VOLT_RELEASE"
      }
      optimize "On"