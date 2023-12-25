add_rules("mode.debug", "mode.release")

target("zprpc")
    set_kind("static")
    set_targetdir("lib")
    set_objectdir("obj")
    set_languages("c++11")
    add_files("zprpc/src/*.cc", "zprpc/pb/*.cc")
    add_includedirs(".")
    set_optimize("fastest")
    add_syslinks("pthread")
    add_links("protobuf", "zest")

target("calc_callee")
    set_kind("binary")
    set_targetdir("bin")
    set_objectdir("obj")
    set_languages("c++11")
    add_files("example/calc_service_callee.cc", "example/pb/*.cc")
    add_includedirs(".")
    set_optimize("fastest")
    add_deps("zprpc")

target("calc_caller")
    set_kind("binary")
    set_targetdir("bin")
    set_objectdir("obj")
    set_languages("c++11")
    add_files("example/calc_service_caller.cc", "example/pb/*.cc")
    add_includedirs(".")
    set_optimize("fastest")
    add_deps("zprpc")