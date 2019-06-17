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

project "ImGui"
   location "Volt/vendor/ImGui"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("obj/" .. outputdir .. "/%{prj.name}")

   includedirs {
      "Volt/vendor/ImGui"
   }

   files {
       "Volt/vendor/ImGui/imconfig.h",
       "Volt/vendor/ImGui/imgui.h",
       "Volt/vendor/ImGui/imgui.cpp",
       "Volt/vendor/ImGui/imgui_draw.cpp",
       "Volt/vendor/ImGui/imgui_internal.h",
       "Volt/vendor/ImGui/imgui_widgets.cpp",
       "Volt/vendor/ImGui/imstb_rectpack.h",
       "Volt/vendor/ImGui/imstb_textedit.h",
       "Volt/vendor/ImGui/imstb_truetype.h",
       "Volt/vendor/ImGui/imgui_demo.cpp"
   }

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
      "Volt/vendor/spdlog/include",
      "Volt/vendor/ImGui",
      "Volt/vendor/glad/include",
      "Volt/vendor/GLFW/include",
      "%{prj.name}/src"
   }

   -- Link to third party libraries
   links {
      "glfw3",
      "ImGui",
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

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("obj/" .. outputdir .. "/%{prj.name}")

   files { 
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.hpp",
      "%{prj.name}/src/**.cpp"
   }

   includedirs {
      "Volt/vendor/spdlog/include",
      "Volt/vendor/ImGui",
      "Volt/vendor/glad/include",
      "Volt/vendor/GLFW/include",
      "Volt/src",
      "%{prj.name}/src",
   }

   links { 
      "Volt",
      "glfw3",
      "glad",
      "ImGui",
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