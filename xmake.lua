add_rules("mode.debug", "mode.release", "mode.coverage")
add_requires("conan::doctest/2.4.8", {alias = "doctest"})

target("console")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("doctest")
    if is_mode("debug") then
        add_defines("DEBUG")
    end
