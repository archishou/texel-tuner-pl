cmake_minimum_required(VERSION 3.24)
project(texel_tuner_pl)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/engines)
include_directories(src/external)

add_executable(texel_tuner_pl
        src/engines/pl_tapered.cpp
        src/engines/pl_tapered.h
        src/external/chess.hpp
        src/external/sliders.hpp
        src/base.h
        src/config.h
        src/main.cpp
        src/threadpool.cpp
        src/threadpool.h
        src/tuner.cpp
        src/tuner.h)
