-- project
set_project("zxjson")
set_xmakever("2.8.9")

-- language
set_warnings("all")
set_languages("c++23")
set_encodings("utf-8")

-- allows
set_allowedplats("windows", "linux")
set_allowedarchs("windows|x86", "windows|x64", "linux|x86_64")
set_allowedmodes("debug", "release", "releasedbg")

-- rules
add_rules("plugin.vsxmake.autoupdate")
add_rules("mode.debug", "mode.release", "mode.releasedbg")

-- lto
if is_mode("releasedbg") or is_mode("release") then
    set_policy("build.optimization.lto", true)
end

-- targets
target("zxjson")
    set_kind("$(kind)")
    if is_plat("windows") then
        if is_kind("shared") then
            add_rules("utils.symbols.export_all", {export_classes = true})
        end
    end
    add_files("src/**.cpp")
    add_includedirs("src", {public = true})
    add_headerfiles("src/(**.h)")

target("zxjson-test")
    set_default(false)
    set_kind("binary")
    add_files("test/main.cpp")
    add_deps("zxjson")
