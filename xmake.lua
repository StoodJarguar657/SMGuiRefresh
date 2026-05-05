set_project("SM-GuiRefresh")
set_version("1.2.0")

add_rules("mode.release")

target("SM-GuiRefresh")
    add_syslinks("User32")
    set_kind("shared")
    set_languages("c++20")
    add_files("./dllmain.cpp")
