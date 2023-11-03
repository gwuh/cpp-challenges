set_languages("c++20")

add_requires("catch2") -- Testing framework

target("codingproblems")
    set_kind("binary")

    add_packages("catch2")

    -- runargs should include the names of tests to execute
    set_runargs("SerializeBinaryTree")

    add_files(  
        "src/*.cpp"
    )
    add_includedirs(
        "include"
    )