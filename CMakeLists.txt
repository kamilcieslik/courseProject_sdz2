cmake_minimum_required(VERSION 3.7)
project(sdizo_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Graph.cpp
        Graph.h
        AdjacencyListForGraph.cpp
        AdjacencyListForGraph.h
        NeighborhoodMatrixForGraph.cpp
        NeighborhoodMatrixForGraph.h
        UsefulStructuresForAlgorithms.cpp
        UsefulStructuresForAlgorithms.h
        main.cpp)

add_executable(sdizo_2 ${SOURCE_FILES})