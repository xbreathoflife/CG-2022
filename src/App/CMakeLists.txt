set(SRCS
    main.cpp
        FractalWindow.cpp
        FractalWindow.h

    shaders.qrc
    Shaders/diffuse.fs
    Shaders/diffuse.vs
        FractalWidget.cpp FractalWidget.h)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.6/lib/cmake")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(demo-app ${SRCS})

target_link_libraries(demo-app
    PRIVATE
        Qt5::Widgets
        FGL::Base
)