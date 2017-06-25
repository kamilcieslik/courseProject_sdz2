cmake_minimum_required(VERSION 3.7)
project(sdizo_2_r)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -fno-rtti -O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -fno-rtti -O2")

set(SOURCE_FILES
        Graph.cpp
        Graph.h
        AdjacencyListForGraph.cpp
        AdjacencyListForGraph.h
        NeighborhoodMatrixForGraph.cpp
        NeighborhoodMatrixForGraph.h
        UsefulStructuresForAlgorithms.cpp
        UsefulStructuresForAlgorithms.h
        TimeMeasurement.cpp
        TimeMeasurement.h
        AlgorithmTest.cpp
        AlgorithmTest.h
        main.cpp)

add_executable(sdizo_2_r ${SOURCE_FILES})