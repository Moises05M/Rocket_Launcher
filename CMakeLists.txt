cmake_minimum_required(VERSION 3.20)
project(Rocket_Launcher)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(sfml)

add_executable(Rocket_Launcher main.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h)

target_link_libraries(Rocket_Launcher PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    add_custom_command(
            TARGET Rocket_Launcher POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:Rocket_Launcher>
    )
endif()
