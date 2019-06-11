workspace "Volt"
   architecture "x64"
   configurations { "Debug", "Release" }

   includedirs {
      "Volt/vendor/spdlog/include"
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

   links { "Volt" }

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