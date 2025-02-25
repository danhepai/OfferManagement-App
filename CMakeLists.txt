cmake_minimum_required(VERSION 3.27)
project(LaboratorQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/bin/qmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(LaboratorQT main.cpp
        headers/actUndo.h
        headers/console.h
        headers/dynamicvector.h
        headers/FileRepository.h
        headers/offer.h
        headers/repository.h
        headers/service.h
        headers/tests.h
        headers/validator.h
        headers/vector.h
        sources/actUndo.cpp
        sources/console.cpp
        sources/dynamicvector.cpp
        sources/FileRepository.cpp
        sources/offer.cpp
        sources/repository.cpp
        sources/service.cpp
        sources/tests.cpp
        sources/validator.cpp
        sources/vector.cpp
        sources/GUI.cpp
        headers/GUI.h
        headers/observer.h
        sources/Wishlist.cpp
        headers/Wishlist.h
        sources/WishlistGui.cpp
        headers/WishlistGui.h)
target_link_libraries(LaboratorQT
        Qt::Core
        Qt::Gui
        Qt::Widgets

)

