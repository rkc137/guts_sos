cmake_minimum_required(VERSION 3.28)
project(sos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(FetchContent)
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
    src/Logger/Logger.cpp
    src/res/res.cpp
    # src/ui/widget/widget.cpp
    src/ui/label/label.cpp
    src/ui/Buttons/LabelButton.cpp
    src/telegraph/Telegraph.cpp
    # src/Scenes/SceneManager.cpp
    src/Scenes/MainMenu.cpp
    src/main.cpp
    # src/res/res.cpp
    # src/pauseble_clock/PausebleClock.cpp
    # src/entitys/entity/Entity.cpp
)
# target_link_options(sos PRIVATE "-mwindows")
target_link_libraries(sos PRIVATE SFML::Graphics SFML::Audio)
target_compile_features(sos PRIVATE cxx_std_17)
# target_compile_definitions(sos PRIVATE SFML_STATIC)
# target_link_options(sos PRIVATE -static)