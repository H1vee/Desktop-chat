cmake_minimum_required(VERSION 3.20)

project(DesktopChat
        VERSION 1.0.0
        DESCRIPTION "Custom Desktop Chat Application"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")

option(USE_OPENGL "Enable OpenGL rendering" ON)

# Qt modules
find_package(Qt6 REQUIRED COMPONENTS
        Core
        Widgets
        Network
        OpenGL
        OpenGLWidgets
)

find_package(OpenGL REQUIRED)

add_compile_definitions(
        QT_NO_KEYWORDS
        QT_DISABLE_DEPRECATED_BEFORE=0x060000
)

if(USE_OPENGL)
    add_compile_definitions(USE_OPENGL)
endif()


add_library(MyChat_UI STATIC
        src/ui/windows/MainWindow.cpp
        src/ui/widgets/common/CustomBox.cpp
)

target_include_directories(MyChat_UI PUBLIC
        src/ui
        src/ui/windows
        src/ui/widgets/common
)

target_link_libraries(MyChat_UI
        Qt6::Core
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        OpenGL::GL
)

add_executable(DesktopChat
        src/main.cpp
)

target_link_libraries(DesktopChat
        MyChat_UI
        Qt6::Core
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        OpenGL::GL
)
