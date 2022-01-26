find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_library(ass01_lib
    ../include/game.hpp
    ../include/Entity.hpp
    ../include/NameComponent.hpp
    ../include/ShapeComponent.hpp
    ../include/TransformComponent.hpp
    game.cpp
    Entity.cpp)
add_library(ass01::lib ALIAS ass01_lib)

target_link_libraries(ass01_lib
        PUBLIC ass01::compiler_options sfml-graphics sfml-audio)
target_include_directories(ass01_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(${BP_BUILD_TESTS_COVERAGE})
    target_compile_options(ass01_lib PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_libraries(ass01_lib PUBLIC gcov)
endif()

add_executable(ass01_app "main.cpp")
target_link_libraries(ass01_app PRIVATE ass01::lib)
add_dependencies(ass01_app ass01_assets)