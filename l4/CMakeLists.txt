cmake_minimum_required(VERSION 3.14)
project(l4)

set(CMAKE_CXX_STANDARD 14)


set(PROJECT_HEADERS
        PO.h
        LicPO.h
        CommPO.h
        CLPO.h
        mytools.h
        )
set(PROJECT_SOURCES
        main.cpp
        PO.cpp
        LicPO.cpp
        CommPO.cpp
        CLPO.cpp
        mytools.cpp
        )

add_executable(l4 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
