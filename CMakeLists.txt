cmake_minimum_required(VERSION 3.28)
project(sos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(sos PRIVATE SFML_STATIC)
    target_link_options(sos PRIVATE -mwindows -static)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
if(DEFINED ENV{CMAKE_LIBS_DIR})
    set(FETCHCONTENT_BASE_DIR "$ENV{CMAKE_LIBS_DIR}")
endif()

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

set(SFML_STATIC_LIBRARIES TRUE)

add_executable(sos 
    src/core/WindowWrap.cpp
    src/core/Window.cpp
    src/core/Logger/Logger.cpp
    src/core/pauseble_clock/PausebleClock.cpp
    src/res/res.cpp
    # src/ui/widget/widget.cpp
    src/ui/label/label.cpp
    src/ui/label/StampLabel.cpp
    src/ui/Buttons/BaseButton.cpp
    src/ui/Buttons/LabelButton.cpp
    src/ui/sprite/Sprite.cpp
    src/scenes/local_scenes/Telegraph.cpp
    src/scenes/local_scenes/BasementBackground.cpp
    src/scenes/local_scenes/Shaker.cpp
    # src/scenes/SceneManager.cpp
    src/scenes/local_scenes/Curtain.cpp
    src/scenes/local_scenes/characters/Character.cpp
    src/scenes/Opening.cpp
    src/scenes/MainMenu.cpp
    src/scenes/Intro.cpp
    src/scenes/levels/Level1.cpp
    src/main.cpp
    # src/res/res.cpp
    # src/pauseble_clock/PausebleClock.cpp
    # src/entitys/entity/Entity.cpp
)
target_link_libraries(sos PRIVATE SFML::Graphics SFML::Audio)
target_compile_features(sos PRIVATE cxx_std_17)
