find_package(Qt5Core)
find_package(Qt5Charts)

add_executable(RoboAuto_geometry main.cpp Vector.h Line.h Polygon.h Drawer.h Drawable.h Circle.h)

target_link_libraries(RoboAuto_geometry Qt5::Widgets Qt5::Charts)