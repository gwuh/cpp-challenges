set_languages("c++20")

add_requires("catch2") -- Testing framework

target("codingproblems")
    set_kind("binary")

    add_packages("catch2")

    -- Run only tests tagged as current (i.e. challenges currently being worked on)
    set_runargs("[current]")

    add_files(  
        "src/*.cpp"
    )
    add_includedirs(
        "include"
    )