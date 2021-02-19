workspace "roots-of-knowledge"
    configurations {"Debug", "Release"}

project "roots-of-knowledge"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"
    targetname "rok"
    cppdialect "C++17"
    toolset "gcc"

    files { "./src/**.h", "./src/**.cpp" }
    defines { "ROK_VERSION=\"1.0\"", "ASIO_SEPARATE_COMPILATION" }
    includedirs { 
        "/usr/local/include/",
        "/usr/include/",
        "./src/"
    }
    links {
        "pthread",
        "ssl:static",
        "crypto",
        "spdlog:static"
    }

    filter "configurations:Debug"
        buildoptions { "-rdynamic" }
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"