workspace "Volt"
   architecture "x64"
   configurations { "Debug", "Release" }

   includedirs {
      "Volt/vendor/spdlog/include",
      "Volt/vendor/glad/include",
      "Volt/vendor/GLFW/include"
   }

   -- Compile GLFW static lib
   os.execute("cd Volt/vendor/GLFW && cmake -DBUILD_SHARED_LIBS=off . && make glfw")

   -- Setup GLFW static lib directory
   libdirs {
      "Volt/vendor/GLFW/src"
   }

project "Volt"
   location "Volt"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"
   objdir "obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"

   files { 
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",

      -- Include glad
      "%{prj.name}/vendor/glad/**.c",
      "%{prj.name}/vendor/glad/**.h",
   }

   -- Link to third party libraries
   links {
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

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"
   objdir "obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}"

   files { 
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   includedirs {
      "Volt/src"
   }

   links { 
      "Volt",
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