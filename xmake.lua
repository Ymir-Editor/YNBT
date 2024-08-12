add_rules("mode.debug", "mode.release")
set_languages("c++23")

add_requires("abseil")

target("YNBT")
    set_kind("static")
    add_files("ynbt/**.cpp")
    add_headerfiles("ynbt/**.hpp", {public=true})
    add_includedirs("ynbt/", {public=true})
    add_packages("abseil", {public=true})
    set_symbols("debug")

for _, file in ipairs(os.files("tests/*.cpp")) do 
    local name = path.basename(file)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("YNBT")
        set_symbols("debug")
        add_files("tests/" .. name .. ".cpp")
        add_tests(name)
end
target("playground")
    set_kind("binary")
    add_files("playground/**.cpp")
    add_deps("YNBT")
    set_symbols("debug")
    add_headerfiles("playground/**.hpp")