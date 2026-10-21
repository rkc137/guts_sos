cmake_minimum_required(VERSION 3.28)
project(sos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
if(DEFINED ENV{CMAKE_LIBS_DIR})
    set(FETCHCONTENT_BASE_DIR "$ENV{CMAKE_LIBS_DIR}")
endif()

option(USE_FETCHCONTENT "fetching libs" FALSE)
if(USE_FETCHCONTENT)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
    )
    FetchContent_MakeAvailable(SFML)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
else()
    find_package(SFML REQUIRED COMPONENTS Graphics Audio Window System)
    find_package(nlohmann_json CONFIG REQUIRED)
endif()


add_executable(sos
    src/core/WindowWrap.cpp
    src/core/Window.cpp
    src/core/Logger/Logger.cpp
    src/core/pauseble_clock/PausebleClock.cpp
    src/res/res.cpp
    src/ui/label/label.cpp
    src/ui/label/StampLabel.cpp
    src/ui/Buttons/BaseButton.cpp
    src/ui/Buttons/LabelButton.cpp
    src/ui/sprite/Sprite.cpp
    src/ui/sprite/SpriteWithLabel.cpp
    src/ui/character/Character.cpp
    src/scenes/local_scenes/Telegraph.cpp
    src/scenes/local_scenes/BasementBackground.cpp
    src/scenes/local_scenes/Shaker.cpp
    src/scenes/local_scenes/Curtain.cpp
    src/scenes/Opening.cpp
    src/scenes/MainMenu.cpp
    src/scenes/Intro.cpp
    src/scenes/levels/Level1.cpp
    src/main.cpp
)
target_link_libraries(sos PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)
target_compile_features(sos PRIVATE cxx_std_17)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2)
    target_link_options(sos PRIVATE -mwindows)
    set_target_properties(sos PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )
    add_custom_command(TARGET sos POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:sos>
            $<TARGET_FILE_DIR:sos>
        COMMAND_EXPAND_LISTS
    )
endif()