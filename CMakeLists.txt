cmake_minimum_required(VERSION 3.27)
project(TSP2024)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSP2024 main.cpp
        src/InstanceTSP.cpp
        src/InstanceTSP.h
        src/Solution.cpp
        src/Solution.h
        src/EvalTSP.cpp
        src/EvalTSP.h
        src/Solver.h
        src/Solver.h
        src/Random.cpp
        src/Random.h
        src/Random.h
        src/Greedy.cpp
        src/Greedy.h
)
